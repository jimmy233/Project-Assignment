#include "cpu/exec/helper.h"
#if DATA_BYTE==2
make_helper(leave)
{
 cpu.esp=cpu.ebp;
		 cpu.ebp=swaddr_read(cpu.esp,2,3);
		 cpu.esp=cpu.esp+2;
 print_asm("leave");
 return 1;
}

#else 
make_helper(leave)
{
		cpu.esp=cpu.ebp;
		cpu.ebp=swaddr_read(cpu.esp,4,3);
		cpu.esp=cpu.esp+4;
		print_asm("leave");
		return 1;
}

#endif
