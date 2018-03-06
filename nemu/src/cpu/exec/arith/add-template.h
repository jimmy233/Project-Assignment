#include "cpu/exec/template-start.h"

#define instr add

static void do_execute()
{
			
		 DATA_TYPE result1=op_dest->val+op_src->val;
		   OPERAND_W(op_dest,result1);
		     
			  cpu.EFLAGS.SF=(result1>>(DATA_BYTE*8-1))&0x1;
			   if(result1==0)
					   		   cpu.EFLAGS.ZF=1;
			    else
								    cpu.EFLAGS.ZF=0;
              uint64_t result=(uint64_t)op_dest->val+(uint64_t)op_src->val;
                 cpu.EFLAGS.CF=(result>>(DATA_BYTE*8))&0x1;
				   uint64_t a=0x1;
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
		   					
DATA_TYPE t1=(((DATA_TYPE)(op_dest->val^op_src->val))>>(DATA_BYTE*8-1)) & 0x1;
 DATA_TYPE t2=(((DATA_TYPE)(result^op_src->val))>>(DATA_BYTE*8-1)) & 0x1;
								 if(t1==0 && t2==1)
										 		     cpu.EFLAGS.OF=1;
								  else
										  		     cpu.EFLAGS.OF=0;     
								 print_asm_template2(); 
								    
}

make_instr_helper(i2a);
make_instr_helper(i2rm);
#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(si2rm);
#endif
make_instr_helper(r2rm);
make_instr_helper(rm2r);
#include "cpu/exec/template-end.h"
