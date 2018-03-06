#include "nemu.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


uint32_t dram_read(hwaddr_t,size_t);
void dram_write(hwaddr_t,size_t,uint32_t);

cache2 cacheL2[4096];

uint8_t cache2_read(hwaddr_t addr)
{
   uint32_t linenum,num,tag;
   num=addr&0x0000003f;
   linenum=(addr>>6)&0x00000fff;
   tag=(addr>>18)&0x00003fff;
   int j;
   for(j=0;j<16;j++)
   {
if(cacheL2[linenum].cache2_block[j].validbit==true && cacheL2[linenum].cache2_block[j].tag==tag)break;
   }

  if(j<16)
  return cacheL2[linenum].cache2_block[j].dataspace[num];
  else  //replace
  {
   int new;
  int p;
for(p=0;p<16;p++)
{
if(cacheL2[linenum].cache2_block[p].validbit==false)break;
}
//all useful then replace
if(p==16)
{
   srand(time(0));
   new=rand()%16;
}
else
  new=p;

cacheL2[linenum].cache2_block[new].tag=tag;
cacheL2[linenum].cache2_block[new].validbit=true;
uint32_t blockaddr=addr&0xffffffc0;
/*int fc;
for(fc=0;fc<64;fc++)
{
		uint8_t result=dram_read(blockaddr+fc,1);
		cacheL2[linenum].cache2_block[new].dataspace[fc]=result;
}*/
 int fc;
 for(fc=0;fc<64;fc++)
{
  uint8_t result=dram_read(blockaddr+fc,1);
  cacheL2[linenum].cache2_block[new].dataspace[fc]=result;
}
cacheL2[linenum].cache2_block[new].dirtybit=false;
 int fb;
//after replace find the block, then return. 
for(fb=0;fb<16;fb++)
{
if(cacheL2[linenum].cache2_block[fb].tag==tag&&cacheL2[linenum].cache2_block[fb].validbit==true)break;		
}
return cacheL2[linenum].cache2_block[fb].dataspace[num];//after replace
  }
}




void cache2_write(hwaddr_t addr,uint8_t data)
{
  uint32_t linenum,tag,num;
  int j;
  num=addr&0x0000003f;
  linenum=(addr>>6)&0x00000fff;
  tag=(addr>>18)&0x00003fff;
  for(j=0;j<16;j++)
  {
if(cacheL2[linenum].cache2_block[j].tag==tag&&cacheL2[linenum].cache2_block[j].validbit==true)break;
  }		  
if(j<16) 
{
cacheL2[linenum].cache2_block[j].dataspace[num]=data;

cacheL2[linenum].cache2_block[j].dirtybit=true;
}
else //write allocate
{
 int new;
 int p;
 for(p=0;p<16;p++)
{ if(cacheL2[linenum].cache2_block[p].validbit==false)break;}

		if(p==16)
	{
  	srand(time(0));
 	 new=rand()%16;
	}
	else
   	new=p;
   cacheL2[linenum].cache2_block[new].validbit=true;
   cacheL2[linenum].cache2_block[new].tag=tag;
   uint32_t blockaddr=addr&0xffffffc0;
  if(cacheL2[linenum].cache2_block[new].dirtybit==true)
	{
      int fa;
    //uint32_t blockaddr=addr&0xffffffc0;
   for(fa=0;fa<64;fa++)
   {
   uint8_t temp=cacheL2[linenum].cache2_block[new].dataspace[fa];	 
   dram_write(blockaddr+fa,1,temp);   
   }
    cacheL2[linenum].cache2_block[new].dirtybit=false;   
	}
int fc;
 for(fc=0;fc<64;fc++)
 { 
   uint8_t result=dram_read(blockaddr+fc,1);
  cacheL2[linenum].cache2_block[new].dataspace[fc]=result;
 }
int fd;
 for(fd=0;fd<16;fd++)
{ if(cacheL2[linenum].cache2_block[fd].validbit==true&&cacheL2[linenum].cache2_block[fd].tag==tag)break;}
cacheL2[linenum].cache2_block[fd].dataspace[num]=data;
//after changes change the dirtybit

cacheL2[linenum].cache2_block[fd].dirtybit=true;
  
}
}




