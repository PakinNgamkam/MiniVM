// #include "asm.tab.h"
// #include "asm_unparser.h"
// #include "assemble.h"
// #include "ast.h"
// #include "disasm.h"
// #include "file_location.h"
// #include "id_attrs.h"
// #include "lexer.h"
// #include "parser_types.h"
// #include "pass1.h"
// #include "symtab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "machine_types.h"
#include "instruction.h"
#include "bof.h"
#include "regname.h"
#include "utilities.h"

// - reads binary object files
// - loads the program in the bof

// - with -p option:
//      prints the loaded program and exits
//          ./vm -p vm_test0.bof

// - with no options:
//      - executes the program
//      - produces tracing output
//          ./vm vm_test0.bof

// Structure for binary object files (this is just an example, you'd need to define based on actual BOF structure)
typedef struct {
    // some fields to represent the program in the BOF
} BinaryObjectFile;

// Function to read the binary object file
BinaryObjectFile* readBOF(const char* filename) {
    // some code here
}

// Function to print the loaded program
void printProgram(BinaryObjectFile* program) {
    // some code here
}

// Function to execute the program
void executeProgram(BinaryObjectFile* program) {
    // some code here
}

int main(int argc, char* argv[]) {
    // Check if at least one argument is provided (the BOF filename)
    if(argc < 2) {
        fprintf(stderr, "Usage: %s [-p] <bof_file>\n", argv[0]);
        exit(1);
    }

    BinaryObjectFile* program;

    // Check for -p option
    if (strcmp(argv[1], "-p") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s [-p] <bof_file>\n", argv[0]);
            exit(1);
        }
        program = readBOF(argv[2]);
        printProgram(program);
    } else {
        program = readBOF(argv[1]);
        executeProgram(program);
    }

    // Clean up resources, if needed
    // some code here

    return 0;
}