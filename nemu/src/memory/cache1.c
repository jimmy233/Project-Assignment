#include "nemu.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

cache1 cache[128];
//uint32_t dram_read(hwaddr_t,size_t);
//void dram_write(hwaddr_t,size_t,uint32_t);
uint8_t cache2_read(hwaddr_t);
void cache2_write(hwaddr_t,uint8_t);
uint32_t cache1_read(hwaddr_t addr,size_t len)
{
		uint32_t data=0;
		uint8_t block_data;
		uint32_t linenum,num;
		uint32_t tag;
	//	int tag1=0
		uint32_t tempaddr;
		int i,j;
	//	int k;
		uint32_t temp;
		for(i=0;i<len;i++)
		{
//	 i=0;
				tempaddr=addr+i;
				num=tempaddr&0x0000003f;
				linenum=(tempaddr>>6)&0x0000007f;	
				tag=(tempaddr>>13)&0x0007ffff;
		for(j=0;j<8;j++)
		{
	if(cache[linenum].cache_block[j].validbit==true && cache[linenum].cache_block[j].tag==tag)break;
		}
	if(j<8)
	{
	  block_data=cache[linenum].cache_block[j].dataspace[num];
      temp=block_data;
	  data=data+(temp<<(i*8));
	/*  for(k=0;k<4;k++)
	  {
	     num=(addr+k)&0x0000003f;
	     block_data =cache[linenum].cache_block[j].dataspace[num+k];
		 temp=block_data;
		 data=data+(temp<<(k*8));
	  }
	  i=4;
	 */ 
	}
	else
	{
	 int new;
	 
	 int p;
	 for(p=0;p<8;p++)
	 {
	   if(cache[linenum].cache_block[p].validbit==false)break;	   
	 }
	 if(p==8)
	 {
			 srand(time(0));
			 new=rand()%8;
	 }
     else
			 new=p;
    cache[linenum].cache_block[new].tag=tag;
	cache[linenum].cache_block[new].validbit=true;
     int fa;
	 uint32_t blockaddr=tempaddr&0xffffffc0;
	 for(fa=0;fa<64;fa++)
	 {
 uint8_t result=cache2_read(blockaddr+fa);//uint8_t result=dram_read(blockaddr+fa,1);
			 cache[linenum].cache_block[new].dataspace[fa]=result;
	 }
	//read in 
   int fb;
   for(fb=0;fb<8;fb++)
	{
 if(cache[linenum].cache_block[fb].tag==tag&&cache[linenum].cache_block[fb].validbit==true)break;
	}
   block_data=cache[linenum].cache_block[fb].dataspace[num];
   temp=block_data;
   data=data+(temp<<(i*8));
	}
}
	return data;	
}

void cache1_write(hwaddr_t addr,size_t len,uint32_t data)
{
		uint32_t linenum,tag,num;
        int i,j;
		for(i=0;i<len;i++)
		{
           uint8_t result=(data>>(i*8))&0x000000ff;
		   uint32_t tempaddr=addr+i;
		   num=tempaddr&0x0000003f;
		   linenum=(tempaddr>>6)&0x0000007f;
         tag=(tempaddr>>13)&0x0007ffff; 
	     for(j=0;j<8;j++)
		 {
if(cache[linenum].cache_block[j].tag==tag&&cache[linenum].cache_block[j].validbit==true)break;
		 }
    if(j<8)
     cache[linenum].cache_block[j].dataspace[num]=result;
  //not write allocate 
	cache2_write(tempaddr,result);
//     dram_write(tempaddr,1,result);
		}
}
