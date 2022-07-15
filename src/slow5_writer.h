#ifndef SLOW5_WRITER_H
#define SLOW5_WRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pod5_reader.h"
#include <slow5/slow5.h>

/*struct info_dict {
    size_t size;
    char const** keys;
    char const** values;
};*/

typedef struct info_dict info_dict_t;

int slow5_writer(char *output_path, rec_t *pod5_data_records);


#endif