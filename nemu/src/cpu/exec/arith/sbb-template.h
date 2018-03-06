#include "cpu/exec/template-start.h"

#define instr sbb

static void do_execute()
{
  DATA_TYPE result=op_src->val;
 if((uint8_t)result==result &&(DATA_BYTE==2 || DATA_BYTE==4))
{
 if(((result>>7)&0x1)==1) 
{
  if(DATA_BYTE==2)
   result=result|0xff00;
  else
   result=result|0xffffff00;
}
}
DATA_TYPE end=op_dest->val - (result+cpu.EFLAGS.CF);
OPERAND_W(op_dest,end); 	
DATA_TYPE old=op_dest->val;
  print_asm_template2();
 cpu.EFLAGS.SF=(result>>(DATA_BYTE*8-1))&0x1;
 if(result==0)
		   cpu.EFLAGS.ZF=1;
 else
		    cpu.EFLAGS.ZF=0;

 if(old<(result+cpu.EFLAGS.CF))
		 cpu.EFLAGS.CF=1;
 else
		 cpu.EFLAGS.CF=0;
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
 DATA_TYPE t1=(((DATA_TYPE)(old^op_src->val))>>(DATA_BYTE*8-1)) & 0x1;
 DATA_TYPE t2=(((DATA_TYPE)(result^op_src->val))>>(DATA_BYTE*8-1)) & 0x1;
 if(t1==1 && t2==0)
		     cpu.EFLAGS.OF=1;
 else
		     cpu.EFLAGS.OF=0;      
  
}

make_instr_helper(i2a);
make_instr_helper(i2rm);
#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(si2rm);
#endif
make_instr_helper(r2rm);
make_instr_helper(rm2r);
#include "cpu/exec/template-end.h"

