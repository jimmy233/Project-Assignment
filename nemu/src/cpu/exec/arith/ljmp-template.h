#include "cpu/exec/template-start.h"

make_helper(concat(ljmp_, SUFFIX))
{
    uint32_t addr=instr_fetch(eip+1,4);
    uint32_t CS=instr_fetch(eip+5,2);
    cpu.eip=addr;
   cpu.CS.SELECTOR.RPL=CS&0x3;
  cpu.CS.SELECTOR.TL=(CS>>2)&0x1;   
  cpu.CS.SELECTOR.INDEX=(CS>>3)&0x1fff;
  print_asm_template1();
  return 0;
}
#include "cpu/exec/template-end.h"
