/**
 * @file slow5_writer.c
 * @brief slow5 file writing program
 * @author Sixiao Li (z5262083), Nidhi Paalpare (z5257492)
 * @date 14/07/2022
 */

#include "slow5_writer.h"

int slow5_writer(char *output_path, rec_t *pod5_data_records, size_t batch_row_count, file_status_t file_status) {

    printf("in slow5 writer %s\n", output_path);
	// if file already exists
	slow5_file_t *sp = NULL;
	if (file_status == FILE_INIT) {
		sp = slow5_open(output_path, "w");
		if(sp==NULL){
			fprintf(stderr,"Error opening file to write!\n");
			exit(EXIT_FAILURE);
		}

		/*********************** Header ******************/

		set_header_attr(sp, pod5_data_records);

		set_header_aux(sp);

		if (slow5_hdr_write(sp) < 0) {
			fprintf(stderr,"Error writing header!");
			exit(EXIT_FAILURE);
		}

	} else {
		sp = slow5_open(output_path, "a");
		if(sp==NULL){
			fprintf(stderr,"Error opening file to append!\n");
			exit(EXIT_FAILURE);
		}
	}

    /******************* A SLOW5 record ************************/

	for (int i = 0; i < (int) batch_row_count; i++) {
		slow5_rec_t* slow5_record = slow5_rec_init();
		if(slow5_record == NULL){
			fprintf(stderr,"Could not allocate space for a slow5 record.");
			exit(EXIT_FAILURE);
		}
		set_record_primary_fields(slow5_record, sp, pod5_data_records[i]);
		set_record_aux_fields(slow5_record, sp, pod5_data_records[i]);
		slow5_write(slow5_record, sp);
		slow5_rec_free(slow5_record);
	}

	slow5_close(sp);
    return 0;
}

void set_header_attr(slow5_file_t *sp, rec_t *pod5_data_records) {
	slow5_hdr_t* header = sp->header;
	for (int i = 0; i < (int)pod5_data_records[0].info_dic->size; i++) {
		if(slow5_hdr_add(pod5_data_records[0].info_dic->keys[i], header) < 0) {
			fprintf(stderr,"Error adding %s attribute\n", pod5_data_records[0].info_dic->keys[i]);
    		exit(EXIT_FAILURE);
		}
		if(slow5_hdr_set(pod5_data_records[0].info_dic->keys[i], pod5_data_records[0].info_dic->values[i], 0, header) < 0) {
			fprintf(stderr,"Error setting %s attribute\n", pod5_data_records[0].info_dic->keys[i]);
    		exit(EXIT_FAILURE);
		}
	} 
}

void set_header_aux(slow5_file_t *sp) {
	slow5_hdr_t* header = sp->header;
	if(slow5_aux_add("channel_number", SLOW5_UINT16_T, header) < 0) {
		fprintf(stderr,"Error adding channel_number auxillary field\n");
		exit(EXIT_FAILURE);		
	}
	if(slow5_aux_add("median_before", SLOW5_DOUBLE, header) < 0) {
		fprintf(stderr,"Error adding median_before auxillary field\n");
		exit(EXIT_FAILURE);	
	}
	if(slow5_aux_add("read_number", SLOW5_UINT32_T, header) < 0) {
		fprintf(stderr,"Error adding read_number auxillary field\n");
		exit(EXIT_FAILURE);	
	}
	if(slow5_aux_add("start_mux", SLOW5_UINT8_T, header) < 0) {
		fprintf(stderr,"Error adding start_mux auxillary field\n");
		exit(EXIT_FAILURE);	
	}
	if(slow5_aux_add("start_time", SLOW5_UINT64_T, header) < 0) {
		fprintf(stderr,"Error adding start_time auxillary field\n");
		exit(EXIT_FAILURE);	
	}
}

void set_record_primary_fields(slow5_rec_t *slow5_record, slow5_file_t *sp, rec_t pod5_data_record) {
	slow5_record->read_id = pod5_data_record.read_id;
	slow5_record->read_id_len = strlen(slow5_record->read_id);
	slow5_record->read_group = pod5_data_record.read_group;
	slow5_record->digitisation = pod5_data_record.digitisation;
	slow5_record->offset = pod5_data_record.offset;
 	slow5_record->range = pod5_data_record.range;
	for (int i = 0; i < (int)pod5_data_record.info_dic->size; i++) {
    	if (strcmp(pod5_data_record.info_dic->keys[i], "sample_frequency") == 0) {
			// slow5_record->sampling_rate = atof(pod5_data_record.info_dic->values[i]);
			// Debug!!!!!!!!
			slow5_record->sampling_rate = 4000;
		}
	}
    slow5_record->len_raw_signal = pod5_data_record.len_raw_signal;
	slow5_record->raw_signal = (int16_t *)malloc(sizeof(int16_t) * slow5_record->len_raw_signal);
    if(slow5_record->raw_signal == NULL){
        fprintf(stderr,"Could not allocate space for raw signal.");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<(int)slow5_record->len_raw_signal; i++){
        slow5_record->raw_signal[i] = i;
    }	
}

void set_record_aux_fields(slow5_rec_t *slow5_record, slow5_file_t *sp, rec_t pod5_data_record) {

    if(slow5_aux_set(slow5_record, "channel_number", &pod5_data_record.channel, sp->header) < 0){
        fprintf(stderr,"Error setting channel_number auxilliary field\n");
        exit(EXIT_FAILURE);
    }
    if(slow5_aux_set(slow5_record, "median_before", &pod5_data_record.median_before, sp->header) < 0){
        fprintf(stderr,"Error setting median_before auxilliary field\n");
        exit(EXIT_FAILURE);
    }
    if(slow5_aux_set(slow5_record, "read_number", &pod5_data_record.read_number, sp->header) < 0){
        fprintf(stderr,"Error setting read_number auxilliary field\n");
        exit(EXIT_FAILURE);
    }
    if(slow5_aux_set(slow5_record, "start_mux", &pod5_data_record.well, sp->header) < 0){
        fprintf(stderr,"Error setting start_mux auxilliary field\n");
        exit(EXIT_FAILURE);
    }
    if(slow5_aux_set(slow5_record, "start_time", &pod5_data_record.start_sample, sp->header) < 0){
        fprintf(stderr,"Error setting start_time auxilliary field\n");
        exit(EXIT_FAILURE);
    }
}
