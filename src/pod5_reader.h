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

int pod5_reader_main (int argc, char *argv[]);

static inline double realtime(void) {
    struct timeval tp;
    struct timezone tzp;
    gettimeofday(&tp, &tzp);
    return tp.tv_sec + tp.tv_usec * 1e-6;
}

// Need more entries
typedef struct {
    char* read_id;
    double digitisation;
    double offset;
    double scale;
    float median_before;
    uint16_t channel;
    uint8_t well;
    uint64_t len_raw_signal;
    int16_t* raw_signal;
    uint32_t read_number;
    uint64_t start_sample;
} rec_t;


#endif