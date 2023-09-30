# MiniVM
COP3402 HW1

# Overview
.asm -> ASSEMBLER -> .bof -> VM -> .myo and .myp

# our job is to create VM 

The gist of this assignment
- we are given .bof(binary object file) files
- we need to make an executable called vm by compiling .c (in this case machine.c)
  
1. we need to read .bof file and load the data into
- Text section -> 32 Registers(0 to 31), the data structure for Register might be an array GPR[32] (from what I understand)
- Data section -> // I'm not too sure about the details, something about Global and static variables
- Stack section -> // Something about runtime stack
   
- there will be 2 modes (tracing and listing)
- the output of listing is .myp file (expected to be the same as given .lst file), compile with -p
- the output of tracing is .myo file (expected to be the same as given .out file)

2. "listing" will show all the instructions
   Addr Instruction
   0 STRA 
   4 ADDI $0, $t0, 1
   8 EXIT 
    1024: 0	...
   
3. "tracing" will show Text Section(all 32 registers for each instruction), Data Section, and Stack Section 
         PC: 0
GPR[$0 ]: 0   	GPR[$at]: 0   	GPR[$v0]: 0   	GPR[$v1]: 0   	GPR[$a0]: 0   	GPR[$a1]: 0   
GPR[$a2]: 0   	GPR[$a3]: 0   	GPR[$t0]: 0   	GPR[$t1]: 0   	GPR[$t2]: 0   	GPR[$t3]: 0   
GPR[$t4]: 0   	GPR[$t5]: 0   	GPR[$t6]: 0   	GPR[$t7]: 0   	GPR[$s0]: 0   	GPR[$s1]: 0   
GPR[$s2]: 0   	GPR[$s3]: 0   	GPR[$s4]: 0   	GPR[$s5]: 0   	GPR[$s6]: 0   	GPR[$s7]: 0   
GPR[$t8]: 0   	GPR[$t9]: 0   	GPR[$k0]: 0   	GPR[$k1]: 0   	GPR[$gp]: 1024	GPR[$sp]: 4096
GPR[$fp]: 4096	GPR[$ra]: 0   
    1024: 0	...
    4096: 0	...
==> addr:    0 STRA 
      PC: 4
GPR[$0 ]: 0   	GPR[$at]: 0   	GPR[$v0]: 0   	GPR[$v1]: 0   	GPR[$a0]: 0   	GPR[$a1]: 0   
GPR[$a2]: 0   	GPR[$a3]: 0   	GPR[$t0]: 0   	GPR[$t1]: 0   	GPR[$t2]: 0   	GPR[$t3]: 0   
GPR[$t4]: 0   	GPR[$t5]: 0   	GPR[$t6]: 0   	GPR[$t7]: 0   	GPR[$s0]: 0   	GPR[$s1]: 0   
GPR[$s2]: 0   	GPR[$s3]: 0   	GPR[$s4]: 0   	GPR[$s5]: 0   	GPR[$s6]: 0   	GPR[$s7]: 0   
GPR[$t8]: 0   	GPR[$t9]: 0   	GPR[$k0]: 0   	GPR[$k1]: 0   	GPR[$gp]: 1024	GPR[$sp]: 4096
GPR[$fp]: 4096	GPR[$ra]: 0   
    1024: 0	...
    4096: 0	...
==> addr:    4 ADDI $0, $t0, 1
      PC: 8
GPR[$0 ]: 0   	GPR[$at]: 0   	GPR[$v0]: 0   	GPR[$v1]: 0   	GPR[$a0]: 0   	GPR[$a1]: 0   
GPR[$a2]: 0   	GPR[$a3]: 0   	GPR[$t0]: 1   	GPR[$t1]: 0   	GPR[$t2]: 0   	GPR[$t3]: 0   
GPR[$t4]: 0   	GPR[$t5]: 0   	GPR[$t6]: 0   	GPR[$t7]: 0   	GPR[$s0]: 0   	GPR[$s1]: 0   
GPR[$s2]: 0   	GPR[$s3]: 0   	GPR[$s4]: 0   	GPR[$s5]: 0   	GPR[$s6]: 0   	GPR[$s7]: 0   
GPR[$t8]: 0   	GPR[$t9]: 0   	GPR[$k0]: 0   	GPR[$k1]: 0   	GPR[$gp]: 1024	GPR[$sp]: 4096
GPR[$fp]: 4096	GPR[$ra]: 0   
    1024: 0	...
    4096: 0	...
==> addr:    8 EXIT 
