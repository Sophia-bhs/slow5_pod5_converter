#ifndef SLOW5_WRITER_H
#define SLOW5_WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pod5_reader.h"
#include <slow5/slow5.h>

typedef struct info_dict info_dict_t;

int slow5_writer(char *output_path, rec_t *pod5_data_records, size_t batch_row_count, file_status_t file_status);
void set_header_attr(slow5_file_t *sp, rec_t *pod5_data_records);
void set_header_aux(slow5_file_t *sp);

#endif