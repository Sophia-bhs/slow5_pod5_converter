/**
 * @file pod5_reader.c
 * @brief pod5 reader
 * @author Sixiao Li (z5262083), Nidhi Paalpare (z5257492)
 * g++ src/pod5_reader.c -o p2s  -I src/pod5-format/include/ src/pod5-format/lib64/libpod5_format.a src/pod5-format/lib64/libarrow.a src/pod5-format/lib64/libzstd.a -lz -lpthread
 * @date 26/06/2022
 */
#include "pod5_reader.h"

int pod5_reader(int argc, char *argv[]){

    double tot_time = 0;
    double t0 = 0 ;

    /**** Initialisation and opening of the file ***/
    t0 = realtime();

    pod5_init();

    // Open the file
    Pod5FileReader_t* file = pod5_open_combined_file(argv[1]);

    if (!file) {
       fprintf(stderr,"Error in opening file\n");
       perror("perr: ");
       exit(EXIT_FAILURE);
    }

    size_t batch_count = 0;
    if (pod5_get_read_batch_count(&batch_count, file) != POD5_OK) {
        fprintf(stderr, "Failed to query batch count: %s\n", pod5_get_error_string());
    }
    tot_time += realtime() - t0;
    /**** End of init ***/

    int read_count = 0;
    file_status_t file_status = FILE_INIT;
    run_info_data_t *info_dic = NULL;
    //iterate through batches in the file
    for (size_t batch_index = 0; batch_index < batch_count; ++batch_index) {
        /**** Fetching a batch (disk loading, decompression, parsing in to memory arrays) ***/
        double t0 = realtime();

        Pod5ReadRecordBatch_t* batch = NULL;
        if (pod5_get_read_batch(&batch, file, batch_index) != POD5_OK) {
           fprintf(stderr,"Failed to get batch: %s\n", pod5_get_error_string());
        }

        size_t batch_row_count = 0;
        if (pod5_get_read_batch_row_count(&batch_row_count, batch) != POD5_OK) {
            fprintf(stderr,"Failed to get batch row count\n");
        }

        rec_t *rec = (rec_t*)malloc(batch_row_count * sizeof(rec_t));
        for (size_t row = 0; row < batch_row_count; ++row) {
            uint8_t read_id[16];
            int16_t pore = 0;
            int16_t calibration_idx = 0;
            uint32_t read_number = 0;
            uint64_t start_sample = 0;
            float median_before = 0.0f;
            int16_t end_reason = 0;
            int16_t run_info = 0;
            int64_t signal_row_count = 0;
            if (pod5_get_read_batch_row_info(batch, row, read_id, &pore, &calibration_idx,
                                            &read_number, &start_sample, &median_before,
                                            &end_reason, &run_info, &signal_row_count) != POD5_OK) {
                fprintf(stderr,"Failed to get read %ld\n", row );
            }
            read_count += 1;

            char read_id_tmp[37];

            if (pod5_format_read_id(read_id, read_id_tmp) != POD5_OK) {
                fprintf(stderr, "Failed to get read %ld as a readable read id string: %s\n", row,  pod5_get_error_string());
            }

            // Now read out the calibration params:
            CalibrationDictData_t *calib_data = NULL;
            if (pod5_get_calibration(batch, calibration_idx, &calib_data) != POD5_OK) {
                fprintf(stderr, "Failed to get read %ld calibration_idx data: %s\n", row,  pod5_get_error_string());
            }

			CalibrationExtraData_t calib_extra_data;
			if (pod5_get_calibration_extra_info(batch, calibration_idx, run_info, &calib_extra_data) != POD5_OK) {
                fprintf(stderr, "Failed to get read %ld calibration_idx extra data: %s\n", row,  pod5_get_error_string());
            } 

            // Find the absolute indices of the signal rows in the signal table
            uint64_t *signal_rows_indices= (uint64_t*) malloc(signal_row_count * sizeof(uint64_t));

            if (pod5_get_signal_row_indices(batch, row, signal_row_count,
                                           signal_rows_indices) != POD5_OK) {
                fprintf(stderr,"Failed to get read %ld; signal row indices: %s\n", row, pod5_get_error_string());
            }

            // cannot get to work this in C, So using C++
            // Find the locations of each row in signal batches:
            //SignalRowInfo_t *signal_rows = (SignalRowInfo_t *)malloc(sizeof(SignalRowInfo_t)*signal_row_count);
            std::vector<SignalRowInfo_t *> signal_rows(signal_row_count);

            //if (pod5_get_signal_row_info(file, signal_row_count, signal_rows_indices,
                                        //&signal_rows) != POD5_OK) {
            if (pod5_get_signal_row_info(file, signal_row_count, signal_rows_indices,
                                        signal_rows.data()) != POD5_OK) {
                fprintf(stderr,"Failed to get read %ld signal row locations: %s\n", row, pod5_get_error_string());
            }
            // Read out the pore params:
            PoreDictData_t *pore_data = NULL;
            if (pod5_get_pore(batch, pore, &pore_data) != POD5_OK) {
                fprintf(stderr, "Failed to get read %ld pore_idx data: %s\n", row,  pod5_get_error_string());
            }

            // Find the calibration info for a row in a read batch.
            RunInfoDictData_t *run_info_data = NULL;
            if (pod5_get_run_info(batch, run_info, &run_info_data) != POD5_OK) {
                fprintf(stderr, "Failed to get read %ld run_info data: %s\n", row,  pod5_get_error_string());
            }

            size_t total_sample_count = 0;
            for (size_t i = 0; (unsigned)i < signal_row_count; ++i) {
                total_sample_count += signal_rows[i]->stored_sample_count;
            }

            int16_t *samples = (int16_t*)malloc(sizeof(int16_t)*total_sample_count);
            size_t samples_read_so_far = 0;
            for (size_t i = 0; (unsigned)i < signal_row_count; ++i) {
                if (pod5_get_signal(file, signal_rows[i], signal_rows[i]->stored_sample_count,
                                   samples + samples_read_so_far) != POD5_OK) {
                    fprintf(stderr,"Failed to get read  %ld; signal: %s\n", row, pod5_get_error_string());
                    fprintf(stderr,"Failed to get read  %ld; signal: %s\n", row, pod5_get_error_string());
                }

                samples_read_so_far += signal_rows[i]->stored_sample_count;
            }
            // Info dict is used for header writing, therefore only need to be read once
            if (row == 0 && batch_index == 0) {
                info_dic = run_info_to_flat_dic(run_info_data);
            }
            int length = snprintf(NULL, 0, "%d", pore_data->channel);
            char* channel_buffer = (char *)malloc( length + 1 );
            snprintf(channel_buffer, 40,"%d",pore_data->channel);
            
            rec[row].len_raw_signal = samples_read_so_far;
            rec[row].raw_signal = samples;
            rec[row].scale = calib_data->scale;
            rec[row].offset = calib_data->offset;
            rec[row].read_id = strdup(read_id_tmp);
            rec[row].channel = channel_buffer;
            rec[row].well = pore_data->well;
            rec[row].read_number = (int32_t)read_number;
            rec[row].median_before = (double)median_before;
            rec[row].start_sample = start_sample;
            rec[row].digitisation = calib_extra_data.digitisation;
            rec[row].range = calib_extra_data.range;
            rec[row].read_group = 0;
            rec[row].info_dic = info_dic;

            pod5_release_calibration(calib_data);
            pod5_release_pore(pore_data);
            pod5_release_run_info(run_info_data);
            pod5_free_signal_row_info(signal_row_count, signal_rows.data());

            free(signal_rows_indices);
        }

        tot_time += realtime() - t0;
        t0 = realtime();
        /**** Write Batch ***/
        slow5_writer(argv[2], rec, batch_row_count, file_status);
        fprintf(stderr, "Converting, please wait %ld/%ld.\n", batch_index + 1, batch_count);
        
        /**** Deinit ***/
        if (pod5_free_read_batch(batch) != POD5_OK) {
            fprintf(stderr,"Failed to release batch\n");
        }
        for (size_t row = 0; row < batch_row_count; ++row) {
            free(rec[row].raw_signal);
        }
        free(rec);
        tot_time += realtime() - t0;
        /**** End of Deinit***/

		file_status = FILE_MID;
    }
    
    for (size_t info_dict_count = 0; info_dict_count < info_dic->size; ++info_dict_count) {
        free((void*)info_dic->keys[info_dict_count]);
        free((void*)info_dic->values[info_dict_count]);
    }
    free(info_dic->keys);
    free(info_dic->values);
    free(info_dic);

    pod5_close_and_free_reader(file);

    fprintf(stderr, "Reads: %d\n", read_count);
    fprintf(stderr, "Time for getting samples %f\n", tot_time);
    return 0;
}

run_info_data_t* run_info_to_flat_dic(RunInfoDictData_t *run_info_data) {
    size_t context_tags_size = run_info_data->context_tags.size;
    size_t tracking_id_size = run_info_data->tracking_id.size;
    run_info_data_t *info_dic = (run_info_data_t *)malloc(sizeof(run_info_data_t));
    if (info_dic == NULL) {
        fprintf(stderr, "Failed to malloc info dict\n");
        return info_dic;
    }
    info_dic->keys = (const char**)malloc((context_tags_size + tracking_id_size) * sizeof (char*));
    if (info_dic->keys == NULL) {
        fprintf(stderr, "Failed to malloc info keys\n");
        free(info_dic);
        return info_dic;
    }
    info_dic->values = (const char**)malloc((context_tags_size + tracking_id_size) * sizeof (char*));
    if (info_dic->values == NULL) {
        fprintf(stderr, "Failed to malloc info values\n");
        free(info_dic);
        free(info_dic->keys);
        return info_dic;
    }

    for (size_t context_tags_count = 0; context_tags_count < context_tags_size; ++context_tags_count) {
        char* key_i = strdup(run_info_data->context_tags.keys[context_tags_count]);
        char* value_i = strdup(run_info_data->context_tags.values[context_tags_count]);
        info_dic->keys[context_tags_count] = key_i;
        info_dic->values[context_tags_count] = value_i;
    }
    for (size_t tracking_id_count = 0; tracking_id_count < tracking_id_size; ++tracking_id_count) {
        char* key_i = strdup(run_info_data->tracking_id.keys[tracking_id_count]);
        char* value_i = strdup(run_info_data->tracking_id.values[tracking_id_count]);
        info_dic->keys[tracking_id_count + context_tags_size] = key_i;
        info_dic->values[tracking_id_count + context_tags_size] = value_i;
    }
    info_dic->size = context_tags_size + tracking_id_size;
    
    return info_dic;
}
