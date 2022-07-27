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
		if (strcmp(argv[1], "--help") || strcmp(argv[1], "-h")) {
			printf("\n************************************************************\n");
			printf("\tWelcome to the Pod5->Slow5 converter 1.0.0!!\t\n");
			printf("************************************************************\n\n");
			printf("Usage:\t./p2s [OPTION] [INPUT FILE] [OUTPUT FILE]\n\n");
			printf("OPTIONS:\n\t-h, --help\tDisplay this message and exit.\n\n");
			printf("INPUT FILE:\n\tPath to user's existing pod5 file.\n\n");
			printf("OUTPUT FILE:\n\tPath to a slow5 or blow5 file named by\n");
			printf("\tthe user which is created via the converter.\n\n");
			exit(0);
		} else {
			fprintf(stderr, "Usage: %s in_file.pod5 out_file.slow5\n", argv[0]);
			return EXIT_FAILURE;
		}
    }

    int ret = pod5_reader(argc, argv);
    if (ret == 1) {
        fprintf(stderr,"Error in reading POD5 file\n");
        perror("perr: ");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}