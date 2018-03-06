#include "cpu/exec/helper.h"
#if DATA_BYTE==2
make_helper(cwdcdq)
{
   uint16_t AX=cpu.eax & 0x0000ffff;
   uint16_t sign=(AX>>15)&0x1;
   if(sign==1)
   {
		   cpu.edx=(cpu.eax&0xffff0000) | 0x0000ffff;
   }
   else
		   cpu.edx=cpu.eax&0xffff0000;
   print_asm("cwd");
   return 1;
}

#else 
make_helper(cwdcdq)
{
		uint32_t EAX=cpu.eax;
		uint32_t sign=(EAX>>31)&0x1;
		if(sign==1)
				cpu.edx=0xffffffff;
		else
				cpu.edx=0;

	print_asm("cdq");
		return 1;
}
#endif
