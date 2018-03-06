#include "cpu/exec/template-start.h"
#define instr push

static void do_execute()
{
 if(DATA_BYTE==4)
 {
   cpu.esp=cpu.esp-4;
   swaddr_write(cpu.esp,4,op_src->val,1);
 }
 else if(DATA_BYTE==2)
 {
   cpu.esp=cpu.esp-2;
   swaddr_write(cpu.esp,2,op_src->val,1);
 }
 else if(DATA_BYTE==1)
 {
	//	 uint32_t result=op_src->val;
          // op_src->val=(op_src->val<<24)>>24;
     int result=(int)op_src->val;	
	   result=(result<<24)>>24;
		 cpu.esp=cpu.esp-4;
		 swaddr_write(cpu.esp,4,result,1);
 }
 print_asm_template1();
}
make_instr_helper(rm);
make_instr_helper(r);
make_instr_helper(i);
#include "cpu/exec/template-end.h"
