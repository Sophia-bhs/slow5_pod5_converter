#ifndef POD5_READER_H
#define POD5_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <sys/time.h>
#include "pod5-format/include/pod5_format/c_api.h"
#include <vector>
#include <stdint.h>

int pod5_reader(int argc, char *argv[]);

static inline double realtime(void) {
    struct timeval tp;
    struct timezone tzp;
    gettimeofday(&tp, &tzp);
    return tp.tv_sec + tp.tv_usec * 1e-6;
}

typedef struct {
    size_t size;
    char const** keys;
    char const** values;
} run_info_data_t;

typedef struct {
    char* read_id;
    float offset;
    float scale;
    float median_before;
    float range;
    uint16_t channel;
    uint8_t well;
    uint64_t len_raw_signal;
    int16_t* raw_signal;
    uint32_t read_number;
    uint64_t start_sample;
    int16_t digitisation;
    uint32_t read_group;
    run_info_data_t *info_dic;
} rec_t;

typedef enum {
    FILE_INIT = 0,
    FILE_MID = 1,
    FILE_END = 2,
} file_status_t;

run_info_data_t* run_info_to_flat_dic(RunInfoDictData_t *run_info_data);

#include "slow5_writer.h"

#endif