#include <stdio.h>
#include <string.h>
#include "bof.h"
#include "instruction.h"
#include "machine_types.h"

void read_and_printBOF(const char *filename) {
    // Construct the output filename
    char output_filename[256];
    strncpy(output_filename, filename, sizeof(output_filename) - 1);
    char *dot = strrchr(output_filename, '.');
    if (dot) {
        *dot = '\0'; // Terminate string at the dot
    }
    strcat(output_filename, ".myp");

    // Open the output file for writing
    FILE *out_file = fopen(output_filename, "w");
    if (!out_file) {
        fprintf(stderr, "Error opening output file: %s\n", output_filename);
        return;
    }

    // Open the BOF using bof_read_open
    BOFFILE bf = bof_read_open(filename);

    // Read and return the header from the BOF using bof_read_header
    BOFHeader bh = bof_read_header(bf);

    // Read and print each of the instructions using instruction_read
    fprintf(out_file, "Addr Instruction\n");
    printf("Addr Instruction\n");
    for (int i = 0; i < bh.text_length / BYTES_PER_WORD; i++) {
        bin_instr_t instruction = instruction_read(bf);
        fprintf(out_file, "%4d %s\n", i * BYTES_PER_WORD, instruction_assembly_form(instruction));
        printf("%4d %s\n", i * BYTES_PER_WORD, instruction_assembly_form(instruction));
    }

    // Flag to determine if all data values are zero
    int all_zero = 1;

    // Buffer to hold data values
    word_type data_values[bh.data_length / BYTES_PER_WORD];

    // Read words in the data section of the BOF using bof_read_word and check if all are zero
    for (int i = 0; i < bh.data_length / BYTES_PER_WORD; i++) {
        data_values[i] = bof_read_word(bf);
        if (data_values[i] != 0) {
            all_zero = 0;
        }
    }

    // If all data values are not zero, print them
    if (!all_zero) {
        for (int i = 0; i < bh.data_length / BYTES_PER_WORD; i++) {
            fprintf(out_file, "%8d: %d ", bh.data_start_address + i * BYTES_PER_WORD, data_values[i]);
            printf("%8d: %d ", bh.data_start_address + i * BYTES_PER_WORD, data_values[i]);
            if ((i + 1) % 5 == 0) {
                fprintf(out_file, "\n");
                printf("\n");
            }
        }
    }

    // Print the last data value
    if (!all_zero) {
        fprintf(out_file, "%8d: 0 ...\n", bh.data_start_address + bh.data_length);
        printf("%8d: 0 ...\n", bh.data_start_address + bh.data_length);
    } else {
        fprintf(out_file, "%8d: 0 ...\n", bh.data_start_address);
        printf("%8d: 0 ...\n", bh.data_start_address);
    }

    // Close the BOF and output file
    bof_close(bf);
    fclose(out_file);
}

void future_function(const char *filename) {
    // Placeholder for future functionality
    printf("Running future functionality for file: %s\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [-p] <filename>\n", argv[0]);
        return 1;
    }

    // Check if -p flag is provided
    if (argc == 3 && strcmp(argv[1], "-p") == 0) {
        read_and_printBOF(argv[2]);
    } else if (argc == 2) {
        future_function(argv[1]);
    } else {
        printf("Invalid arguments. Usage: %s [-p] <filename>\n", argv[0]);
        return 1;
    }

    return 0;
}

// #include <stdio.h>
// #include <string.h>
// #include "bof.h"
// #include "instruction.h"
// #include "machine_types.h"

// void read_and_printBOF(const char *filename) {
//     // Open the BOF using bof_read_open
//     BOFFILE bf = bof_read_open(filename);

//     // Read and return the header from the BOF using bof_read_header
//     BOFHeader bh = bof_read_header(bf);

//     // Read and print each of the instructions using instruction_read
//     printf("Addr Instruction\n");
//     for (int i = 0; i < bh.text_length / BYTES_PER_WORD; i++) {
//         bin_instr_t instruction = instruction_read(bf);
//         printf("%4d %s\n", i * BYTES_PER_WORD, instruction_assembly_form(instruction));
//     }

//     // Flag to determine if all data values are zero
//     int all_zero = 1;

//     // Buffer to hold data values
//     word_type data_values[bh.data_length / BYTES_PER_WORD];

//     // Read words in the data section of the BOF using bof_read_word and check if all are zero
//     for (int i = 0; i < bh.data_length / BYTES_PER_WORD; i++) {
//         data_values[i] = bof_read_word(bf);
//         if (data_values[i] != 0) {
//             all_zero = 0;
//         }
//     }

//     // If all data values are not zero, print them
//     if (!all_zero) {
//         for (int i = 0; i < bh.data_length / BYTES_PER_WORD; i++) {
//             printf("%8d: %d ", bh.data_start_address + i * BYTES_PER_WORD, data_values[i]);
//             if ((i + 1) % 5 == 0) {
//                 printf("\n");
//             }
//         }
//     }

//     // Print the last data value
// 	if (!all_zero) {
//     	printf("%8d: 0 ...\n", bh.data_start_address + bh.data_length);
// 	} else {
// 		printf("%8d: 0 ...\n", bh.data_start_address);
// 	}

//     // Close the BOF
//     bof_close(bf);
// }

// void future_function(const char *filename) {
//     // Placeholder for future functionality
//     printf("Running future functionality for file: %s\n", filename);
// }

// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         printf("Usage: %s [-p] <filename>\n", argv[0]);
//         return 1;
//     }

//     // Check if -p flag is provided
//     if (argc == 3 && strcmp(argv[1], "-p") == 0) {
//         read_and_printBOF(argv[2]);
//     } else if (argc == 2) {
//         future_function(argv[1]);
//     } else {
//         printf("Invalid arguments. Usage: %s [-p] <filename>\n", argv[0]);
//         return 1;
//     }

//     return 0;
// }


