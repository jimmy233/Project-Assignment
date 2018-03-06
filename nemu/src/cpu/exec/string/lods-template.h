#include "cpu/exec/template-start.h"
#define instr lods
static void do_execute()
{
   
   DATA_TYPE result=MEM_R(cpu.esi);
 cpu.eax=result; 
  int IncDec;
  if(cpu.EFLAGS.DF==0)
		IncDec=DATA_BYTE;
  else
		IncDec=-DATA_BYTE;

  cpu.esi=cpu.esi+IncDec;  
  print_asm_template2();
}
make_helper(concat(lods_t_, SUFFIX))
{
		do_execute();
		return 1;
}
#include "cpu/exec/template-end.h"
