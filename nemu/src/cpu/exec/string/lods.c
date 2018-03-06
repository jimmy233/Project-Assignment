#include "cpu/exec/helper.h"
/*make_helper(lods)	
{
int32_t optemp=instr_fetch(cpu.eip,1);
  if(optemp==0xac)
  {
    uint8_t result=swaddr_read(cpu.esi,1);
	printf("%u\n",result);
  cpu.eax=result;
 // swaddr_write(cpu.eax,1,result);
  int IncDec;
  if(cpu.EFLAGS.DF==0)
		IncDec=1;
  else
		IncDec=-1;

  cpu.esi=cpu.esi+IncDec;  
  }
  else if(optemp==0xad)
  {
#if DATA_BYTE==2
		  
                uint16_t result=swaddr_read(cpu.esi,2);
		cpu.eax=result;
  // swaddr_write(cpu.eax,2,result);
				int IncDec;
				if(cpu.EFLAGS.DF==0)
						IncDec=2;
				else
						IncDec=-2;
				cpu.esi=cpu.esi+IncDec;
		  
#elif DATA_BYTE==4
		  
				  uint32_t result=swaddr_read(cpu.esi,4);
				  cpu.eax=result;
          //   swaddr_write(cpu.eax,4,result);   
				  int IncDec;
				  if(cpu.EFLAGS.DF==0)
						  IncDec=4;
				  else
						  IncDec=-4;
				  cpu.esi=cpu.esi+IncDec;
#endif		  
}
print_asm("lods");
return 1;
}*/

#define DATA_BYTE 1
#include "lods-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "lods-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "lods-template.h"
#undef DATA_BYTE

make_helper_v(lods_t)
