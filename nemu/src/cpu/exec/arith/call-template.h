#include "cpu/exec/template-start.h"

#define instr call
static void do_execute()
{
 uint32_t optemp=instr_fetch(cpu.eip,1);

  if(optemp==0xff)
  {
     if(DATA_BYTE==2)
	 {
			 cpu.esp=cpu.esp-2;     
           int len=decode_rm_w(cpu.eip+1);
			uint32_t result=(cpu.eip+len)&0x0000ffff;
			swaddr_write(cpu.esp,2,result,1);			
			 cpu.eip=op_src->val&0xffff;
			 cpu.eip=cpu.eip-len-1;
	 }
	 else if(DATA_BYTE==4)
	 {
           cpu.esp=cpu.esp-4;
		   int len=decode_rm_l(cpu.eip+1);
		   uint32_t result=cpu.eip+len;
		   swaddr_write(cpu.esp,4,result,1);
		   cpu.eip=op_src->val;
		   cpu.eip=cpu.eip-len-1;
	 }
  }
  else{
 if(DATA_BYTE==4)
  {
    cpu.esp=cpu.esp-4;
	swaddr_write(cpu.esp,4,cpu.eip+4,1);
    cpu.eip=cpu.eip+op_src->val;
  }
  else if(DATA_BYTE==2)
  {
	cpu.esp=cpu.esp-2;
	swaddr_write(cpu.esp,2,cpu.eip+2,1);
	cpu.eip=(cpu.eip+op_src->val)&0x0000ffff;
  }
  }
  print_asm_template1();
}

//#if DATA_BYTE==1 || DATA_BYTE==4
make_instr_helper(si);
//#endif
#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(rm);
#endif

#include "cpu/exec/template-end.h"
