#include "cpu/exec/template-start.h"
#define instr setg
static void do_execute () {
				if(cpu.EFLAGS.ZF==0 || (cpu.EFLAGS.SF==cpu.EFLAGS.OF))
								OPERAND_W(op_src,1);
					else
									OPERAND_W(op_src,0);
						print_asm_template1();
}

make_instr_helper(rm)
#include "cpu/exec/template-end.h"
