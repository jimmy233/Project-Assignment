#include "cpu/exec/helper.h"

make_helper(movsb)
{
		uint16_t result=swaddr_read(cpu.esi,2,3);
		swaddr_write(cpu.edi,2,result,3);

		int IncDec;
		if(cpu.EFLAGS.DF==0)
				IncDec=1;
		else
				IncDec=-1;
		cpu.esi=cpu.esi+IncDec;
		cpu.edi=cpu.edi+IncDec;
		print_asm("movsb");
		return 1;
}
