#include "cpu/exec/helper.h"

make_helper(movsd)
{
		uint32_t result=swaddr_read(cpu.esi,4,3);
		swaddr_write(cpu.edi,4,result,3);

		int IncDec;
		if(cpu.EFLAGS.DF==0)
		IncDec=4;
		else
		IncDec=-4;
		cpu.esi=cpu.esi+IncDec;
		cpu.edi=cpu.edi+IncDec;
		print_asm("movsd");
		return 1;
}


