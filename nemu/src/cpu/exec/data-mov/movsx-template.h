#include "cpu/exec/template-start.h"
#define instr movsx
static void do_execute()
{
  DATA_TYPE result=op_src->val;
  if(DATA_BYTE==2)
  {
		  uint16_t result1=(uint8_t) result;
   if(((result>>7)&0x1)==1)
   {
		   result1=result1|0xff00;
   
   }   
      OPERAND_W(op_dest,result1);
  		   
  }
  else if(DATA_BYTE==4)
  { 
		  uint32_t optemp=instr_fetch(cpu.eip+1,1);

          

		  if(optemp==0xbe)
		  {
		    uint32_t result1=(uint8_t)result;
		  //swaddr_t addr= instr_fetch(cpu.eip+1,4);
		  if(((result>>7)&0x1)==1)
		  {
			
				  result1=result1|0xffffff00;
		   //      OPERAND_W(op_dest,result1);		  
		  }
		  
		   OPERAND_W(op_dest,result1);
		  }
		  else if(optemp==0xbf)
		  {
				  uint32_t result1=(uint16_t)result;
				  if(((result>>15)&0x1)==1)
				  {
						  result1=result1|0xffff0000;
				  }
				  OPERAND_W(op_dest,result1);
		  }
/*		  else
		  OPERAND_W(op_dest,result);
		  } 
		  else if(op_src->val==(uint16_t)op_src->val)
		{
			uint32_t result1=(uint16_t)result;
			if(((result>>15)&0x1)==1)
			{
					result1=result1|0xffff0000;
					OPERAND_W(op_dest,result1);
			}
			else
			OPERAND_W(op_dest,result);
		}*/
  }  
  
  print_asm_template2();
}
make_instr_helper(rmd2r);
make_instr_helper(rmzd2r);
#include "cpu/exec/template-end.h"
