#include "cpu/exec/template-start.h"
#define instr ret
static void do_execute()
{
             /*  if(DATA_BYTE==2)
			 {	
				  uint32_t result=swaddr_read(cpu.esp,2);
				  OPERAND_W(op_src,(uint16_t)result);
				  cpu.esp=cpu.esp+2;
				  cpu.eip=result;
				  cpu.esp=cpu.esp+op_src->val;
				  cpu.eip=cpu.eip&0x0000ffff;
				 } 
				   
				   else if(DATA_BYTE==4)
				   {

                          uint32_t result=swaddr_read(cpu.esp,4);
						   OPERAND_W(op_src,result);
						   cpu.esp=cpu.esp+4;
						   cpu.eip=result;
				   }
			*/	 
	  
	  	  if(DATA_BYTE==2)
		  {
				 uint32_t result1=swaddr_read(cpu.esp,op_src->val,1);
				cpu.esp=cpu.esp+result1;
			//	cpu.esp=cpu.esp+op_src->val;
			//cpu.eip=result1;
			//	cpu.eip=cpu.eip & 0x0000ffff;
				cpu.eip=result1-2;
			//	printf("xxxxxxx\n");
	 	// uint32_t result=swaddr_read(cpu.eip,2);
        // cpu.esp=cpu.esp+result;
		  }
		  else if(DATA_BYTE==4)
		  {
				  uint32_t result=swaddr_read(cpu.esp,4,1);
				  OPERAND_W(op_src,result);
				  cpu.esp=cpu.esp+4;
				  cpu.eip=result;
		  }
     				 print_asm_template1(); 
				 
}
make_instr_helper(i);
#include "cpu/exec/template-end.h"
