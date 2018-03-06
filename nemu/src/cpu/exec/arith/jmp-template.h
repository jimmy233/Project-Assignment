#include "cpu/exec/template-start.h"
#define instr jmp
static void do_execute()
{
  uint32_t optemp=instr_fetch(cpu.eip,1);
  if(optemp==0x66)
		  optemp=instr_fetch(cpu.eip+1,1);
  if(optemp==0xeb || optemp==0xe9)
  {
		  cpu.eip=cpu.eip+op_src->val;
		  if(DATA_BYTE==2)
				  cpu.eip=cpu.eip & 0x0000ffff;
  }

  else if(optemp==0xff)
  {
		  cpu.eip=op_src->val;
		  if(DATA_BYTE==2)
		  {
				  cpu.eip=cpu.eip & 0x0000ffff;
		  }
		  
  }
  print_asm_template1();
}

make_instr_helper(i);
#if DATA_BYTE==1 || DATA_BYTE==4
make_instr_helper(si);
#endif
make_instr_helper(rm);
#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(jm2r);
#endif
#include "cpu/exec/template-end.h"
