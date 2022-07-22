/**
 * @file main.c
 * @brief main program for the POD5 -> SLOW5 converter
 * @author Sixiao Li (z5262083), Nidhi Paalpare (z5257492)
 * @date 20/06/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pod5_reader.h"
#include "pod5_format/c_api.h"

int main (int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s in_file.pod5 out_file.slow5\n", argv[0]);
        return EXIT_FAILURE;
    }

    int ret = pod5_reader(argc, argv);
    if (ret == 1) {
        fprintf(stderr,"Error in reading POD5 file\n");
        perror("perr: ");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}