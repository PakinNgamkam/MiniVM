#include <stdio.h>
#include <string.h>
#include "bof.h"
#include "instruction.h"
#include "machine_types.h"
#include "regname.h"
#include "utilities.h"

// a size for the memory (2^16 bytes = 64K)
#define MEMORY_SIZE_IN_BYTES (65536 - BYTES_PER_WORD) // 65,532
#define MEMORY_SIZE_IN_WORDS (MEMORY_SIZE_IN_BYTES / BYTES_PER_WORD) // 16,383 which is 4096 * 4

int PC = 0;
int data_count = 0;
int TRACING = 1;
int EXIT = 0;
int JUMP = 0;
int PCH = 0;

static union mem_u {
	byte_type bytes[MEMORY_SIZE_IN_BYTES];
	word_type words[MEMORY_SIZE_IN_WORDS];
	bin_instr_t instrs[MEMORY_SIZE_IN_WORDS];
} memory;

word_type registers[32] = {0}; // Initialize all registers to 0


void execute_instruction(word_type *registers) {
	instr_type it = instruction_type(memory.instrs[PC]);
	int rs, rt, rd, shift, immed;
    switch (it) {
		case syscall_instr_type:
			//printf("%d ,syscall\n", PC);
			switch (memory.instrs[PC].syscall.code) {
			case exit_sc:
				printf("exit works\n");
				EXIT = 1;
				break;
			case print_str_sc:
				// TODO
				break;
			case print_char_sc:
				PCH = 1;
				break;
			case read_char_sc:
				// TODO
				break;
			case start_tracing_sc:
				TRACING = 1;
				break;
			case stop_tracing_sc:
				TRACING = 0;
				break;
			default:
				bail_with_error("Unknown register instruction code (%d)!",
						memory.instrs[PC].syscall.code);
				break;
			}
		break;
		case reg_instr_type:
			printf("%d ,reg\n", PC);
			rs = memory.instrs[PC].reg.rs;
			rd = memory.instrs[PC].reg.rd;
			rt = memory.instrs[PC].reg.rt;
			shift = memory.instrs[PC].reg.shift;

			switch (memory.instrs[PC].reg.func) {
			case ADD_F:
				registers[rd] = registers[rs] + registers[rt];
				break;
			case SUB_F: 
				registers[rd] = registers[rs] - registers[rt];
				break;
			case AND_F: 
				registers[rd] = registers[rs] & registers[rt];
				break;
			case BOR_F: 
				registers[rd] = registers[rs] | registers[rt];
				break;
			case NOR_F: 
				registers[rd] = ~(registers[rs] | registers[rt]);
				break;
			case XOR_F:
				registers[rd] = registers[rs] ^ registers[rt];
				break;
			case MUL_F: 
				registers[rd] = registers[rs] * registers[rt];
				break;
			case DIV_F:
				registers[rd] = registers[rs] / registers[rt]; // Should I add something if it divides by 0?
				break;
			case MFHI_F:
				// TODO 
				break;
			case MFLO_F:
				// TODO 
				break;
			case SLL_F:
				// TODO 
				break;
			case SRL_F:
				// TODO 
				break;
			case JR_F:
				// TODO 
				break;
			default:
				bail_with_error("Unknown register instruction function (%d)!",
						memory.instrs[PC].reg.func);
				break;
			}
		break;

		case immed_instr_type:
			printf("%d ,immed\n", PC);
			rs = memory.instrs[PC].immed.rs;
			rt = memory.instrs[PC].immed.rt;
			immed = memory.instrs[PC].immed.immed;
			// for o use machine_types_formOffset(o)
			switch (memory.instrs[PC].immed.op) {
			case ADDI_O:
				registers[rt] = registers[rs] + (short int) memory.instrs[PC].immed.immed;
				break;
			case ANDI_O: 
				// TODO
				break;
			case BORI_O:
				// TODO 
				break;
			case XORI_O:
				// TODO
				break;
			case BEQ_O:
				// TODO 
				break;
			case BNE_O:
				// TODO
				break;
			case BGEZ_O: 
				// TODO 
				break;
			case BGTZ_O: 
				// TODO 
				break;
			case BLEZ_O: 
				// TODO 
				break;
			case BLTZ_O:
				// TODO 
				break;
			case LBU_O: 
				// TODO 
				break;
			case LW_O: 
				// TODO 
				break;
			case SB_O: 
				// TODO 
				break;
			case SW_O:
				// TODO 
				break;
			default:
				bail_with_error("Unknown immediate instruction opcode (%d)!",
						memory.instrs[PC].immed.op);
				break;
			}
		break;

		// TODO: Need test Might need to fix
		case jump_instr_type:
			printf("jump\n");
			switch (memory.instrs[PC].jump.op) {
			case JMP_O:
				PC = memory.instrs[PC].jump.addr;
				JUMP = 1;
				break;
			case JAL_O:
				registers[RA] = PC;
				PC = memory.instrs[PC].jump.addr;
				JUMP = 1;
				break;
			default:
				bail_with_error("Unknown jump instruction opcode (%d)!",
						memory.instrs[PC].jump.op);
				break;
			}
		break;

		default:
			bail_with_error("Unknown instruction type (%d) in instruction_assembly_form!",
					it);
		break;
    }
	// TO DO: skip this if instruction is Jump Type
	//PC = PC+4;
}

void print_tracing(word_type *registers) {
	printf("      PC: %d\t", PC);
	printf("\n");
	//execute_instruction(PC, registers);
	for (int i = 0; i < 32; i++) {
		printf("GPR[%-3s]: %d\t", regname_get(i), registers[i]);
		if ((i + 1) % 6 == 0) {
			printf("\n");
		}
	}
	printf("\n");

	for(int i = 0; i <= data_count; i++) {
		printf("%8d: %d\t ", registers[GP] + i * BYTES_PER_WORD, memory.words[registers[GP] + i * BYTES_PER_WORD]);
	}
	printf("\n");

	for(int i = 0; i <= (registers[FP] - registers[SP]) / BYTES_PER_WORD; i++) {
		printf("%8d: %d\t ", registers[SP] + i * BYTES_PER_WORD, memory.words[registers[SP] + i * BYTES_PER_WORD]);
	}
	printf("\n");

	printf("==> addr:%5d %s\n", PC, instruction_assembly_form(memory.instrs[PC]));
}

void read_and_loadBOF(const char *filename) {
    // Open the BOF using bof_read_open
    BOFFILE bf = bof_read_open(filename);

    // Read and return the header from the BOF using bof_read_header
    BOFHeader bh = bof_read_header(bf);

	// Loading the instructions
	for (int i = 0; i < bh.text_length / BYTES_PER_WORD; i++) {
        bin_instr_t instruction = instruction_read(bf);
		memory.instrs[i*BYTES_PER_WORD] = instruction;
	}

	// Loading the data(global data)
	int word_address = bh.data_start_address;
	data_count = bh.data_length / BYTES_PER_WORD;
	for (int i = 0; i < bh.data_length / BYTES_PER_WORD; i++) {
		memory.words[word_address] = bof_read_word(bf);
		word_address = word_address + 4;
	}

	registers[GP] = bh.data_start_address;
	registers[SP] = 4096;
	registers[FP] = 4096;
	registers[RA] = 0;

	// Close the BOF
    bof_close(bf);
}

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
	read_and_loadBOF(filename);

	// TO DO: need to change to while loop 
	while (EXIT == 0) {

		if (TRACING == 1) // when instruction is STRA, TRACING = 1/ NOTR TRACING = 0 
			print_tracing(registers);

		execute_instruction(registers);
		
		if (JUMP == 0)
			PC = PC+4;
		else 
			JUMP = 0;
		
		if (PCH == 1) {
			// Output the character from $a0 to stdout
			int result = fputc(registers[4], stdout);
			printf("\n");
			// Store the result in $v0
			registers[2] = result;
			PCH = 0;
		}
		
	}
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
