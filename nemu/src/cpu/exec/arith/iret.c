#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"
#include "common.h"
#include "macro.h"
#include "../../../../../lib-common/x86-inc/mmu.h"
make_helper(iret){
		cpu.eip=swaddr_read(cpu.esp,4,1);
		cpu.esp=cpu.esp+4;
		cpu.CS.Selector=swaddr_read(cpu.esp,2,1);
		cpu.esp=cpu.esp+2;
		cpu.EFLAGS.ef=swaddr_read(cpu.esp,4,1);
		cpu.esp=cpu.esp+4;
		uint32_t addr=cpu.GDTR.basement+(cpu.CS.SELECTOR.INDEX<<3);
		SD sd;
		sd.low=lnaddr_read(addr,4);
		sd.high=lnaddr_read(addr+4,4);
uint32_t base=sd.val.base_15_0+(sd.val.base_23_16<<16)+(sd.val.base_31_24<<24);
	uint32_t limit=sd.val.limit_15_0+(sd.val.limit_19_16<<16);
cpu.CS.CACHE.base=base;
cpu.CS.CACHE.limit=limit;
print_asm("iret");
return 0;	
}
