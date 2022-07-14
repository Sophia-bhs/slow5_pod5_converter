/**
 * @file slow5_writer.c
 * @brief slow5 file writing program
 * @author Sixiao Li (z5262083), Nidhi Paalpare (z5257492)
 * @date 14/07/2022
 */

#include "slow5_writer.h"
#define FILE_PATH "test.blow5"

int slow5_writer(char *output_path, rec_t *pod5_data_records) {
    slow5_file_t *sp = slow5_open(FILE_PATH, "w");
    printf("in slow5 writer %s\n", output_path);
    if(sp==NULL){
        fprintf(stderr,"Error opening file!\n");
        exit(EXIT_FAILURE);
    }
    int batch_row_count = 1000;
    //process and print (time not measured as we want to compare to the time it takes to read the file)
    double *sums = (double*)malloc(batch_row_count * sizeof(double));
    // #pragma omp parallel for
    for(int i=0;i<batch_row_count;i++){
        uint64_t sum = 0;
        //looking through records 
        for(int j=0; (unsigned)j<pod5_data_records[i].len_raw_signal; j++){
            sum +=  ((pod5_data_records[i].raw_signal[j] + pod5_data_records[i].offset) * pod5_data_records[i].scale);
        }
        sums[i] = sum;
    }
    //printing in row format to stdout -- this is possiblly where we want to output our struct
    for(int i=0;i<batch_row_count;i++){
        fprintf(stdout,"%s\t%f\n",pod5_data_records[i].read_id,sums[i]); 
    }
    free(sums);
    fprintf(stderr,"batch printed with %d reads\n",batch_row_count);

    return 0;
}