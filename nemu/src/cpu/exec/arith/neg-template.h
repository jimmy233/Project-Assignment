#include "cpu/exec/template-start.h"

#define instr neg

static void do_execute() {
	DATA_TYPE result = -op_src->val;
// uint32_t result1=swaddr_read(op_src->val,4);
//	OPERAND_W(op_src, result);
   if(op_src->val==0)
	cpu.EFLAGS.CF=0;
   else
	cpu.EFLAGS.CF=1;
   OPERAND_W(op_src, result);
	/* There is no need to update EFLAGS, since no other instructions 
	 * in PA will test the flags updated by this instruction.
	 */
   cpu.EFLAGS.SF=(result>>(DATA_BYTE*8-1))&0x1;
			  if(result==0)
					  		   cpu.EFLAGS.ZF=1;
			   else
					   		    cpu.EFLAGS.ZF=0;  
uint32_t a=0x1;
 int b=0;
 if((result&a)==1)
		   b=b+1;
 if(((result>>1)&a)==1)
		   b=b+1;
 if(((result>>2)&a)==1)
		   b=b+1;
 if(((result>>3)&a)==1)
		   b=b+1;
 if(((result>>4)&a)==1)
		   b=b+1;
 if(((result>>5)&a)==1)
		   b=b+1;
 if(((result>>6)&a)==1)
		   b=b+1;
 if(((result>>7)&a)==1)
		   b=b+1;
 if((b%2)==0)
		   cpu.EFLAGS.PF=1;
 else
		   cpu.EFLAGS.PF=0; 	
DATA_TYPE t1=(((DATA_TYPE)(0^op_src->val))>>(DATA_BYTE*8-1)) & 0x1;
 DATA_TYPE t2=(((DATA_TYPE)(result^op_src->val))>>(DATA_BYTE*8-1)) & 0x1;
 if(t1==1 && t2==0)
		     cpu.EFLAGS.OF=1;
 else
		     cpu.EFLAGS.OF=0; 		   
	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"
