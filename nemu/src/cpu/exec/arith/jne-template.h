#include "cpu/exec/template-start.h"
#define instr jne
static void do_execute()
{  if(cpu.EFLAGS.ZF==0)
		{
		DATA_TYPE result2=op_src->val;
		uint32_t result=(uint32_t)result2;
	    uint32_t result1=(result>>(DATA_BYTE*8-1));
		 if(result1==1)
			 {
				 			 if(DATA_BYTE==1)
									 result=result | 0xffffff00;
							 else if(DATA_BYTE==2)
									 result=result | 0xffff0000;

			 }
		
							
					cpu.eip=cpu.eip+result;			
					if(DATA_BYTE==2)							
							cpu.eip=cpu.eip & 0x0000ffff;
		}	
								 print_asm_template1();
}

make_instr_helper(i2r);
#include "cpu/exec/template-end.h"

