/**
 * @file main.c
 * @brief main program
 * @author Sixiao Li (z5262083), Nidhi Paalpare (z5257492)
 * @date 20/06/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p2s_converter.h"

int main (int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Example Usage: %s p2s in_file.pod5 out_file.blow5\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "p2s") == 0) {
        printf("%s\n",argv[1]);
    }

    
    return 0;
}