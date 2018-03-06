#include "cpu/exec/template-start.h"
#define instr stos
static void do_execute()
{
  swaddr_write(cpu.edi,DATA_BYTE,cpu.eax,0);
  if(cpu.EFLAGS.DF==0)
		  cpu.edi=cpu.edi+DATA_BYTE;
  else
		   cpu.edi=cpu.edi-DATA_BYTE;

  print_asm_template2();
}
make_helper(concat(stos_t_,SUFFIX))
{
		do_execute();
		return 1;
}
#include "cpu/exec/template-end.h"
