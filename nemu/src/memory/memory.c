#include "common.h"
#include "nemu.h"
#include <time.h>
#include <stdlib.h>
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
uint32_t cache1_read(uint32_t addr,size_t len);
void cache1_write(hwaddr_t addr,size_t len, uint32_t data);
uint32_t hwaddr_read(hwaddr_t,size_t);
void hwaddr_write(hwaddr_t,size_t,uint32_t);
hwaddr_t page_translate(lnaddr_t );
/* Memory accessing interfaces */
uint32_t tlb_cache(lnaddr_t addr)
{
  uint32_t tag=(addr>>12)&0xfffff;
 //int32_t physic=(page_translate>>12)&0xfffff;
 int i,j;
  for(i=0;i<64;i++)
  {
     if(tlb[i].validbit==1&&tlb[i].tag==tag)
       return (tlb[i].physical<<12)+(addr&0xfff);
  }
  uint32_t physical_addr=page_translate(addr);
 // uint32_t physical=(addr1>>12)&0xfffff;
 for(j=0;j<64;j++)
 {
	if(tlb[j].validbit==0)break;
 }
 if(j<64)
 {
     tlb[j].tag=tag;
	 tlb[j].physical=(physical_addr>>12)&0xfffff;
	 tlb[j].validbit=1;
 }
 else
 {
    srand(time(0));
	int block=rand()%64;
	tlb[block].tag=tag;
	tlb[block].physical=(physical_addr>>12)&0xfffff;
	tlb[block].validbit=1;
 }
  return physical_addr;
}
hwaddr_t page_translate(lnaddr_t addr)
{
if(cpu.CR0.protect_enable==0 || cpu.CR0.paging==0)
		return addr;
  uint32_t offset=addr&0xfff;
  uint32_t page=(addr>>12)&0x3ff;
  uint32_t dir=(addr>>22)&0x3ff;
  uint32_t page_base=cpu.CR3.page_directory_base<<12;
  PDE temp;
  uint32_t addr_page1=page_base+(dir<<2);
  temp.val=hwaddr_read(addr_page1,4);
  if(temp.present==0)
		  return addr;
  
  uint32_t addr_page2=(temp.page_frame<<12)+(page<<2);
  PTE temp1;
  temp1.val=hwaddr_read(addr_page2,4);
 if(temp1.present==0)
		  return addr;
  uint32_t physicaladdr=(temp1.page_frame<<12)+offset;
//  Log("pde:0x%x\tpte:0x%x",temp.val,temp1.val);
 // Log("dir_addr:0x%x\tpag_addr:0x%x",addr_page1,addr_page2);
 // asm volatile("int3");

  return physicaladdr;
}
lnaddr_t seg_translate(swaddr_t addr, size_t len,uint8_t sreg)
{
		//uint32_t offset;
//	uint32_t result;
		if(cpu.CR0.protect_enable==1)
		{
		uint32_t index=0;
          if(sreg==0)
			index= cpu.ES.CACHE.base;
	      else if(sreg==1)
			index=cpu.CS.CACHE.base;
	      else if(sreg==2)
			index=cpu.SS.CACHE.base;
	     else if(sreg==3)
		    index=cpu.DS.CACHE.base;
	   	uint32_t result=index+addr;
		 return result;
		}
		else
		{
		return (lnaddr_t)addr;
		}
}
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
		return cache1_read(addr,len); 
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
   cache1_write(addr,len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
		assert(len==1||len==2||len==4);		
		if(cpu.CR0.protect_enable==1&&cpu.CR0.paging==1)
		{
             uint32_t result=tlb_cache(addr);//page_translate(addr);
			 return hwaddr_read(result,len);
		}
       else
			return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
   assert(len==1||len==2||len==4);
	   if(cpu.CR0.protect_enable==1&&cpu.CR0.paging==1)
	   {
			   uint32_t result=tlb_cache(addr);//page_translate(addr);
			   hwaddr_write(result,len,data);
	   }
	   else   
		hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len,uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr = seg_translate(addr, len, sreg);
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data,uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
//	lnaddr_write(addr, len, data);
	lnaddr_t lnaddr=seg_translate(addr,len,sreg);
	lnaddr_write(lnaddr, len, data);
}

