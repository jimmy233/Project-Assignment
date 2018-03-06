#include "cpu/exec/template-start.h"
#define instr pop
static void do_execute()
{
  if(DATA_BYTE==2)
  {
     uint32_t result=swaddr_read(cpu.esp,2,1);
	 OPERAND_W(op_src,(uint16_t)result);
	 cpu.esp=cpu.esp+2;
  }
  else if(DATA_BYTE==4)
  {
    uint32_t result=swaddr_read(cpu.esp,4,1);
	OPERAND_W(op_src,result);
	cpu.esp=cpu.esp+4;
  }
  print_asm_template1();
}
make_instr_helper(r);
make_instr_helper(rm);
#include "cpu/exec/template-end.h"
