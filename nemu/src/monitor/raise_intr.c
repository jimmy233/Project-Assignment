#include "nemu.h"
#include <setjmp.h>
#include "../../../lib-common/x86-inc/mmu.h"
extern jmp_buf jbuf;
void raise_intr(uint8_t No,uint32_t len)
{
		uint32_t add=cpu.IDTR.basement+(No<<3);
		GD gd;
		gd.low=lnaddr_read(add,4);
		gd.high=lnaddr_read(add+4,4);
		cpu.esp=cpu.esp-4;
		swaddr_write(cpu.esp,4,cpu.EFLAGS.ef,1);
		cpu.esp=cpu.esp-2;
		swaddr_write(cpu.esp,2,cpu.CS.Selector,1);
		cpu.esp=cpu.esp-4;
		swaddr_write(cpu.esp,4,cpu.eip+len,1);
		cpu.CS.Selector=(uint16_t)gd.val.segment;
		uint32_t addr=cpu.GDTR.basement+(cpu.CS.SELECTOR.INDEX<<3);
		SD sd;
		sd.low=lnaddr_read(addr,4);
		sd.high=lnaddr_read(addr+4,4);
	uint32_t base=sd.val.base_15_0+(sd.val.base_23_16<<16)+(sd.val.base_31_24<<24);
	uint32_t limit=sd.val.limit_15_0+(sd.val.limit_19_16<<16);
	cpu.CS.CACHE.base=base;
	cpu.CS.CACHE.limit=limit;
	cpu.eip=(gd.val.offset_31_16<<16)+gd.val.offset_15_0+cpu.CS.CACHE.base;
	longjmp(jbuf,1);	
}
