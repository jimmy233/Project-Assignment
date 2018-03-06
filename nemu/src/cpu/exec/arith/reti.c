#include "cpu/exec/helper.h"
	make_helper(ret){
				if(ops_decoded.is_operand_size_16)
					{
									cpu.eip=swaddr_read(cpu.esp,2,1);
									cpu.esp+=2;
									cpu.eip=cpu.eip&0x0000ffff;
					}
				else
				{	cpu.eip=swaddr_read(cpu.esp,4,1);
                      cpu.esp=cpu.esp+4;
				}
  					print_asm("ret");
                      return 1;					
   
                     }											    
