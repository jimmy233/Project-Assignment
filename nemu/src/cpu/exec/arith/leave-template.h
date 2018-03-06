#include "cpu/exec/template-start.h"
#define instr leave

static void do_execute()
{ 
		cpu.esp=cpu.ebp;
		if(DATA_BYTE==2)
		{
		  cpu.ebp=MEM_R(cpu.esp);
  		  cpu.esp=cpu.esp+2;		  
		}
		else if(DATA_BYTE==4)
		{
		  cpu.ebp=MEM_R(cpu.esp);
		  cpu.esp=cpu.esp+4;
		}
		print_asm_template1();
}

make_instr_helper(i);
#include "cpu/exec/template-start.h"
