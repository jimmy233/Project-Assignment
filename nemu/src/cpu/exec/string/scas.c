#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "scas-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "scas-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "scas-template.h"
#undef DATA_BYTE

make_helper_v(scas_t)
/*
{
uint32_t optemp=instr_fetch(cpu.eip,1);
  if(optemp==0xae)
  {
   // uint8_t result=swaddr_read(cpu.edi,2);
 // swaddr_write(cpu.eax,2,result);
   uint8_t r1=swaddr_read(cpu.edi,4);
    uint32_t r2=cpu.eax;
   uint8_t result= r2 - r1; 
   printf("%u\n",result);
		cpu.EFLAGS.SF=(result>>7)&0x1;
        if(result==0)
	     cpu.EFLAGS.ZF=1;
        else
		 cpu.EFLAGS.ZF=0;
        
        if(r2<r1)
		  cpu.EFLAGS.CF=1;
        else
		  cpu.EFLAGS.CF=0;	

	   uint32_t a=0x1;
	   int b=0;
	   if((result&a)==1)
			   b=b+1;
	   if(((result>>1)&a)==1)
			   b=b+1;
	   if(((result>>2)&a)==1)
			   b=b+1;
	   if(((result>>3)&a)==1)
			   b=b+1;
	   if(((result>>4)&a)==1)
			   b=b+1;
	   if(((result>>5)&a)==1)
			   b=b+1;
	   if(((result>>6)&a)==1)
			   b=b+1;
	   if(((result>>7)&a)==1)
			   b=b+1;

	   if(b%2==0)
			   cpu.EFLAGS.PF=1;
	   else
			   cpu.EFLAGS.PF=0;
       	   
         uint8_t t1=(((uint8_t)(r2^r1))>>7) & 0x1;
		 uint8_t t2=(((uint8_t)(result^r1))>>7)&0x1;
         if(t1==1&&t2==0)
				 cpu.EFLAGS.OF=1;
		 else
				 cpu.EFLAGS.OF=0;
  int IncDec;
  if(cpu.EFLAGS.DF==0)
		IncDec=1;
  else
		IncDec=-1;

  cpu.edi=cpu.edi+IncDec;  
  }
  else if(optemp==0xaf)
  {
		 #if DATA_BYTE==2
		  
         //       uint16_t result=swaddr_read(cpu.edi,2);
		//		swaddr_write(cpu.eax,2,result);
uint16_t r1=swaddr_read(cpu.edi,4);
uint16_t r2=(uint16_t)cpu.eax;
   uint16_t result= r2- r1; 
		cpu.EFLAGS.SF=(result>>15)&0x1;
        if(result==0)
	     cpu.EFLAGS.ZF=1;
        else
		 cpu.EFLAGS.ZF=0;
        
        if(r2<r1)
		  cpu.EFLAGS.CF=1;
        else
		  cpu.EFLAGS.CF=0;	

	   uint32_t a=0x1;
	   int b=0;
	   if((result&a)==1)
			   b=b+1;
	   if(((result>>1)&a)==1)
			   b=b+1;
	   if(((result>>2)&a)==1)
			   b=b+1;
	   if(((result>>3)&a)==1)
			   b=b+1;
	   if(((result>>4)&a)==1)
			   b=b+1;
	   if(((result>>5)&a)==1)
			   b=b+1;
	   if(((result>>6)&a)==1)
			   b=b+1;
	   if(((result>>7)&a)==1)
			   b=b+1;

	   if(b%2==0)
			   cpu.EFLAGS.PF=1;
	   else
			   cpu.EFLAGS.PF=0;
       	   
         uint16_t t1=(((uint16_t)(r2^r1))>>15) & 0x1;
		 uint16_t t2=(((uint16_t)(result^r1))>>15)&0x1;
         if(t1==1&&t2==0)
				 cpu.EFLAGS.OF=1;
		 else
				 cpu.EFLAGS.OF=0;

				int IncDec;
				if(cpu.EFLAGS.DF==0)
						IncDec=2;
				else
						IncDec=-2;
				cpu.edi=cpu.edi+IncDec;
		  
		  #elif DATA_BYTE==4
		  
//				  uint32_t result=swaddr_read(cpu.edi,4);
//				  swaddr_write(cpu.eax,4,result);
              uint32_t r1=swaddr_read(cpu.edi,4);
               uint32_t r2=cpu.eax
   uint32_t result= r2 - r1; 
		cpu.EFLAGS.SF=(result>>31)&0x1;
        if(result==0)
	     cpu.EFLAGS.ZF=1;
        else
		 cpu.EFLAGS.ZF=0;
        
        if(cpu.eax<r1)
		  cpu.EFLAGS.CF=1;
        else
		  cpu.EFLAGS.CF=0;	

	   uint32_t a=0x1;
	   int b=0;
	   if((result&a)==1)
			   b=b+1;
	   if(((result>>1)&a)==1)
			   b=b+1;
	   if(((result>>2)&a)==1)
			   b=b+1;
	   if(((result>>3)&a)==1)
			   b=b+1;
	   if(((result>>4)&a)==1)
			   b=b+1;
	   if(((result>>5)&a)==1)
			   b=b+1;
	   if(((result>>6)&a)==1)
			   b=b+1;
	   if(((result>>7)&a)==1)
			   b=b+1;

	   if(b%2==0)
			   cpu.EFLAGS.PF=1;
	   else
			   cpu.EFLAGS.PF=0;
       	   
         uint32_t t1=(((uint32_t)(r2^r1))>>31) & 0x1;
		 uint32_t t2=(((uint32_t)(result^r1))>>31)&0x1;
         if(t1==1&&t2==0)
				 cpu.EFLAGS.OF=1;
		 else
				 cpu.EFLAGS.OF=0;
				  int IncDec;
				  if(cpu.EFLAGS.DF==0)
						  IncDec=4;
				  else
						  IncDec=-4;
				  cpu.edi=cpu.edi+IncDec;
           #endif		  
   }
  print_asm("scas");
  return 1;
}*/
