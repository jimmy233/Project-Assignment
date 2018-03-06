#include "cpu/exec/template-start.h"
#define instr scas
static void do_execute()
{
		DATA_TYPE r1=MEM_R(cpu.edi);
	  // uint32_t r1=swaddr_read(cpu.edi,4);
		DATA_TYPE result=cpu.eax-r1;
//		printf("%d  %d  %d\n",result,cpu.eax,r1);
       if(cpu.EFLAGS.DF==0)
			   cpu.edi=cpu.edi+DATA_BYTE;
	   else
			   cpu.edi=cpu.edi-DATA_BYTE;
 cpu.EFLAGS.SF=(result>>(DATA_BYTE*8-1))&0x1;
 if(result==0)
		   cpu.EFLAGS.ZF=1;
 else
		    cpu.EFLAGS.ZF=0;

 if(cpu.eax<r1)
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
 DATA_TYPE t1=(((DATA_TYPE)(cpu.eax^r1))>>(DATA_BYTE*8-1)) & 0x1;
 DATA_TYPE t2=(((DATA_TYPE)(result^r1))>>(DATA_BYTE*8-1)) & 0x1;
 if(t1==1 && t2==0)
		     cpu.EFLAGS.OF=1;
 else
		     cpu.EFLAGS.OF=0; 

 print_asm_template2(); 
}
make_helper(concat(scas_t_, SUFFIX))
{
  do_execute();
  return 1;
}
#include "cpu/exec/template-end.h"
