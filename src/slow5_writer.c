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
	//if (access(output_path, F_OK) == -1) {
	slow5_file_t *sp = slow5_open(output_path, "w");
	if(sp==NULL){
		fprintf(stderr,"Error opening file!\n");
		exit(EXIT_FAILURE);
	}
	
    slow5_hdr_t* header = sp->header;
	//example header add
	
	slow5_hdr_add("run_id", header);

	slow5_hdr_set("run_id", "0", 0, header);

	slow5_hdr_write(sp);
    printf("Info dict ready: key = %s; value = %s\n", pod5_data_records[0].info_dic->keys[0], pod5_data_records[0].info_dic->values[0]);
    // //process and print (time not measured as we want to compare to the time it takes to read the file)
    // double *sums = (double*)malloc(batch_row_count * sizeof(double));
    // // #pragma omp parallel for
    // for(int i=0;i<batch_row_count;i++){
    //     uint64_t sum = 0;
    //     //looking through records 
    //     for(int j=0; (unsigned)j<pod5_data_records[i].len_raw_signal; j++){
    //         sum +=  ((pod5_data_records[i].raw_signal[j] + pod5_data_records[i].offset) * pod5_data_records[i].scale);
    //     }
    //     sums[i] = sum;
    // }
    // //printing in row format to stdout -- this is possiblly where we want to output our struct
    // for(int i=0;i<batch_row_count;i++){
    //     fprintf(stdout,"%s\t%f\n",pod5_data_records[i].read_id,sums[i]); 
    // }
    // free(sums);
    // fprintf(stderr,"batch printed with %d reads\n",batch_row_count);

    return 0;
}