#include "cpu/exec/template-start.h"
#define instr popa

make_helper(concat(popa_wl_, SUFFIX)) 
	{
	  if(DATA_BYTE==2)
  		{
			REG(R_DI)=swaddr_read(cpu.esp,2,1);
		    cpu.esp=cpu.esp+2;
			REG(R_SI)=swaddr_read(cpu.esp,2,1);
			cpu.esp=cpu.esp+2;
			REG(R_BP)=swaddr_read(cpu.esp,2,1);
			cpu.esp=cpu.esp+4;
			REG(R_BX)=swaddr_read(cpu.esp,2,1);
			cpu.esp=cpu.esp+2;
		    REG(R_DX)=swaddr_read(cpu.esp,2,1);		
			cpu.esp=cpu.esp+2;
	        REG(R_CX)=swaddr_read(cpu.esp,2,1);
		  	cpu.esp=cpu.esp+2;	
			REG(R_AX)=swaddr_read(cpu.esp,2,1);
			cpu.esp=cpu.esp+2;
		}
	else if(DATA_BYTE==4)
		{
		    REG(R_EDI)=swaddr_read(cpu.esp,4,1);
			cpu.esp=cpu.esp+4;
			REG(R_ESI)=swaddr_read(cpu.esp,4,1);
			cpu.esp=cpu.esp+4;
			REG(R_EBP)=swaddr_read(cpu.esp,4,1);
			cpu.esp=cpu.esp+8;
			REG(R_EBX)=swaddr_read(cpu.esp,4,1);
			cpu.esp=cpu.esp+4;
			REG(R_EDX)=swaddr_read(cpu.esp,4,1);
		    cpu.esp=cpu.esp+4;
		    REG(R_ECX)=swaddr_read(cpu.esp,4,1);
			cpu.esp+=4;
			REG(R_EAX)=swaddr_read(cpu.esp,4,1);
			cpu.esp+=4;	
		}	
   	print_asm_template1();
	return 1;
	}
#include "cpu/exec/template-end.h"
