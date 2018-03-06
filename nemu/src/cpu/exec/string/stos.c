#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "stos-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "stos-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "stos-template.h"
#undef DATA_BYTE

make_helper_v(stos_t);
/*
 uint32_t optemp=instr_fetch(cpu.eip,1);
  if(optemp==0xaa)
  {
  swaddr_write(cpu.edi,4,cpu.eax);
  if(cpu.EFLAGS.DF==0)
		cpu.edi=cpu.edi+1;
  else
		cpu.edi=cpu.edi-1; 
  }
  else if(optemp==0xab)
  {
		 #if DATA_BYTE==2
				swaddr_write(cpu.edi,4,cpu.eax);
				if(cpu.EFLAGS.DF==0)
						cpu.edi=cpu.edi+2;
				else
						cpu.edi=cpu.edi-2;
		 #elif DATA_BYTE==4
				  swaddr_write(cpu.edi,4,cpu.eax);
				  if(cpu.EFLAGS.DF==0)
						  cpu.edi=cpu.edi+4;
				  else
						  cpu.edi=cpu.edi-4;
	//			  cpu.esi=cpu.esi+IncDec;
           #endif
}
 print_asm("stos");
 return 1;
}*/
