#ifndef SLOW5_WRITER_H
#define SLOW5_WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pod5_reader.h"
#include <slow5/slow5.h>

/*
	slow5_writer() - writes pod5 data to a slow5 file
*/
int slow5_writer(char *output_path, rec_t *pod5_data_records, size_t batch_row_count, file_status_t file_status);

/*
	set_header_aux() - stores pod5 header attributes to be written to a slow5 file
*/
void set_header_attr(slow5_file_t *sp, rec_t *pod5_data_records);

/*
	set_header_aux() - sets auxillary header fields from pod5 file to a slow5 file
*/
void set_header_aux(slow5_file_t *sp);

/*
	set_record_primary_fields() - stores primary pod5 data in corresponding fields of slow5 record
*/
void set_record_primary_fields(slow5_rec_t *slow5_record, slow5_file_t *sp, rec_t pod5_data_record);

/*
	set_record_aux_fields() - stores auxillary pod5 data in corresponding fields of slow5 record
*/
void set_record_aux_fields(slow5_rec_t *slow5_record, slow5_file_t *sp, rec_t pod5_data_record);

#endif