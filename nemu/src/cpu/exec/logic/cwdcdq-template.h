#include "cpu/exec/template-start.h"
#define instr cwdcdq
make_helper(concat(cwdcdq_a_,SUFFIX)){
		if(DATA_BYTE==2)
		{
            uint16_t AX=cpu.eax &&0x0000ffff;
			uint16_t sign=(AX>>15)&0x1;
			if(sign==1)
			{
					cpu.edx=(cpu.eax&0xffff0000)|0x0000ffff;
			}
			else
					cpu.edx=cpu.eax&0xffff0000;

		}
		else if(DATA_BYTE==4)
		{
			uint32_t EAX=cpu.eax;
			uint32_t sign=(EAX>>31)&0x1;
			if(sign==1)
					cpu.edx=0xffffffff;
			else
					cpu.edx=0;
		}
		print_asm_("cwd/cdq");
}
#include "cpu/exec/template-end.h"
