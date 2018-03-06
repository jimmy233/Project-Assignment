#include "cpu/exec/template-start.h"
#define instr lidt
static void do_execute()
{
  if(DATA_BYTE==2)
  {
		 cpu.IDTR.limit=swaddr_read(op_src->addr,2,1);
		 cpu.IDTR.basement=swaddr_read(op_src->addr+2,4,1)&0xffffff00;
  }	  
  else
  {
		  cpu.IDTR.basement=swaddr_read(op_src->addr+2,4,1);
		  cpu.IDTR.limit=swaddr_read(op_src->addr,2,1);
  }
  
  print_asm_template1();
}
make_instr_helper(rm);
#include "cpu/exec/template-end.h"
