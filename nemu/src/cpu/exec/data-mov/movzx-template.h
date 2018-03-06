#include "cpu/exec/template-start.h"
#define instr movzx
static void do_execute() {
			
			DATA_TYPE result = op_src -> val;
/*			if(DATA_BYTE==2)
					result=(uint16_t)result;
			else if(DATA_BYTE==4)
					result=(uint32_t)result;*/
				OPERAND_W(op_dest, result);
					print_asm_template2();
}

make_instr_helper(rmd2r)
make_instr_helper(rmzd2r)
#include "cpu/exec/template-end.h"

