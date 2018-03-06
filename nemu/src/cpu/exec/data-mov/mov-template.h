#include "cpu/exec/template-start.h"
#include "../../../../../lib-common/x86-inc/mmu.h"
#include "cpu/decode/modrm.h"
#include "nemu.h"
#define instr mov

static void do_execute() {
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}

make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = swaddr_read(eip+1,4,3);//instr_fetch(eip + 1, 4);
	MEM_W(addr, REG(R_EAX));

	print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = swaddr_read(eip+1,4,3);//instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr);
	print_asm("mov" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}

make_helper(concat(mov_cr02r_, SUFFIX))
{

swaddr_t addr=instr_fetch(eip+1,1);
ModR_M temp;
temp.val=addr;
if(temp.reg==0)
{		
REG(addr&0x7)=cpu.CR0.val;
print_asm("mov CR0,%%%s",  REG_NAME(addr&0x7));
}
else
{
  REG(addr&0x7)=cpu.CR3.val;
  print_asm("mov CR3,%%%s", REG_NAME(addr&0x7));
}
return 2;
}

make_helper(concat(mov_r2cr0_, SUFFIX))
{
swaddr_t addr=instr_fetch(eip+1,1);
ModR_M temp;
temp.val=addr;
if(temp.reg==0)
{
 cpu.CR0.val=REG(addr&0x7);
 print_asm("mov %%%s,CR0", REG_NAME(addr&0x7));
}
else
{
 int i;
 for(i=0;i<64;i++)
		 tlb[i].validbit=0;
 cpu.CR3.val=REG(addr&0x7);
  print_asm("mov %%%s,CR3", REG_NAME(addr&0x7));
}
 return 2;
}

make_helper(concat(mov_rm2serg_, SUFFIX))
{
 Segtable table;
 uint32_t high,low;
 swaddr_t addr=instr_fetch(eip+1,1);
 uint8_t modrm=(uint8_t)(addr);
 //uint8_t mod=(modrm>>6)&0x3;
 uint8_t reg=(modrm>>3)&0x7;
 uint8_t rm=modrm&0x7;

 if(reg==0)
 {
   cpu.ES.SELECTOR.RPL=(REG(rm))&0x3;
   cpu.ES.SELECTOR.TL=((REG(rm))>>2)&0x1;
   cpu.ES.SELECTOR.INDEX=((REG(rm))>>3)&0x1fff;
   uint32_t startaddr=cpu.GDTR.basement+cpu.ES.SELECTOR.INDEX*8;
   low=lnaddr_read(startaddr,4);
   high=lnaddr_read(startaddr+4,4);
   table.high=high;
   table.low=low;
 //  table=(table<<32)|low;
   cpu.ES.CACHE.base=table.execle.base_15_0+(table.execle.base_23_16<<16)+(table.execle.base_31_24<<24);
   cpu.ES.CACHE.limit=table.execle.limit_15_0+(table.execle.limit_19_16<<16);
   
 }
 else if(reg==2)
 {
   cpu.SS.SELECTOR.RPL=(REG(rm))&0x3;
   cpu.SS.SELECTOR.TL=((REG(rm))>>2)&0x1;
   cpu.SS.SELECTOR.INDEX=((REG(rm))>>3)&0x1fff;
  uint32_t startaddr=cpu.GDTR.basement+cpu.SS.SELECTOR.INDEX*8;
  low=lnaddr_read(startaddr,4);
  high=lnaddr_read(startaddr+4,4);
  table.high=high;
  table.low=low;
  cpu.SS.CACHE.base=table.execle.base_15_0+(table.execle.base_23_16<<16)+(table.execle.base_31_24<<24);
  cpu.SS.CACHE.limit=table.execle.limit_15_0+(table.execle.limit_19_16<<16);
 }
 else if(reg==3)
 {
     cpu.DS.SELECTOR.RPL=(REG(rm))&0x3;
	 cpu.DS.SELECTOR.TL=((REG(rm))>>2)&0x1;
	 cpu.DS.SELECTOR.INDEX=((REG(rm))>>3)&0x1fff;
    uint32_t startaddr=cpu.GDTR.basement+cpu.DS.SELECTOR.INDEX*8;
	low=lnaddr_read(startaddr,4);
	high=lnaddr_read(startaddr+4,4);
	table.high=high;
	table.low=low;
	cpu.DS.CACHE.base=table.execle.base_15_0+(table.execle.base_23_16<<16)+(table.execle.base_31_24<<24);
	cpu.DS.CACHE.limit=table.execle.limit_15_0+(table.execle.limit_19_16<<16);
 }
 //Segdesc table;
print_asm("mov %%%s,ds/es/ss",REG_NAME(rm));
return 2;
}
#include "cpu/exec/template-end.h"
