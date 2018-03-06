#include "cpu/exec/template-start.h"

#define instr test
static void do_execute()
{
		cpu.EFLAGS.CF=0;
		cpu.EFLAGS.OF=0;
		
		DATA_TYPE result=op_src->val & op_dest->val;
        uint32_t t1=(result>>(DATA_BYTE*8-1));
		if(t1==1)
				cpu.EFLAGS.SF=1;
		else
				cpu.EFLAGS.SF=0;
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
	   if(b%2==0)
			     cpu.EFLAGS.PF=1;
	   else
			     cpu.EFLAGS.PF=0;         		        
		if(result==0)
         cpu.EFLAGS.ZF=1;
		else
		 cpu.EFLAGS.ZF=0;

		print_asm_template2();
}

make_instr_helper(r2rm);
make_instr_helper(i2rm);
make_instr_helper(i2a);
#include "cpu/exec/template-end.h"
