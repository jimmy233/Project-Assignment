#include "cpu/exec/template-start.h"
#define instr pusha
make_helper(concat(pusha_wl_,SUFFIX))
{
		if(DATA_BYTE==2)
		{
				uint16_t temp=REG(R_SP);
				cpu.esp-=2;
				swaddr_write(cpu.esp,2,REG(R_AX),1);
				cpu.esp-=2;
				swaddr_write(cpu.esp,2,REG(R_CX),1);
				cpu.esp-=2;
				swaddr_write(cpu.esp,2,REG(R_DX),1);
				cpu.esp-=2;
				swaddr_write(cpu.esp,2,REG(R_BX),1);
				cpu.esp-=2;
				swaddr_write(cpu.esp,2,temp,1);
				cpu.esp-=2;
				swaddr_write(cpu.esp,2,REG(R_BP),1);
				cpu.esp-=2;
				swaddr_write(cpu.esp,2,REG(R_SI),1);
				cpu.esp-=2;
				swaddr_write(cpu.esp,2,REG(R_DI),1);
		}
		else if(DATA_BYTE==4)
		{
       uint32_t temp=REG(R_ESP);
	   	cpu.esp-=4;
		swaddr_write(cpu.esp,4,REG(R_EAX),1);
		cpu.esp-=4;
		swaddr_write(cpu.esp,4,REG(R_ECX),1);
		cpu.esp-=4; 
		swaddr_write(cpu.esp,4,REG(R_EDX),1);
		cpu.esp-=4;
		swaddr_write(cpu.esp,4,REG(R_EBX),1);
		cpu.esp-=4;
		swaddr_write(cpu.esp,4,temp,1);
		cpu.esp-=4;
		swaddr_write(cpu.esp,4,REG(R_EBP),1);
		cpu.esp-=4;
		swaddr_write(cpu.esp,4,REG(R_ESI),1);
		cpu.esp-=4;
		swaddr_write(cpu.esp,4,REG(R_EDI),1);
		}
		print_asm_template1();
		return 1;
}
#include "cpu/exec/template-end.h"
