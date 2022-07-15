#ifndef SLOW5_WRITER_H
#define SLOW5_WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pod5_reader.h"
#include <slow5/slow5.h>


int slow5_writer(char *output_path, rec_t *pod5_data_records, size_t batch_row_count, file_status_t file_status);


#endif