#include "cpu/exec/template-start.h"

#include "cpu/decode/modrm.h"

#define decode_r_internal concat3(decode_r_, SUFFIX, _internal)
#define decode_rm_internal concat3(decode_rm_, SUFFIX, _internal)
#define decode_i concat(decode_i_, SUFFIX)
#define decode_a concat(decode_a_, SUFFIX)
#define decode_r2rm concat(decode_r2rm_, SUFFIX)

/* Ib, Iv */
make_helper(concat(decode_i_, SUFFIX)) {
	/* eip here is pointing to the immediate */
	op_src->type = OP_TYPE_IMM;
	op_src->imm = instr_fetch(eip, DATA_BYTE);
	op_src->val = op_src->imm;

#ifdef DEBUG
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", op_src->imm);
#endif
	return DATA_BYTE;
}

#if DATA_BYTE == 1||DATA_BYTE==2 ||DATA_BYTE == 4
/* sign immediate */
make_helper(concat(decode_si_, SUFFIX)) {
	op_src->type = OP_TYPE_IMM;

	/* TODO: Use instr_fetch() to read `DATA_BYTE' bytes of memory pointed
	 * by `eip'. Interpret the result as an signed immediate, and assign
	 * it to op_src->simm.
	 *
	op_src->simm = ???
	 */
	int n=(DATA_BYTE==1)?24:0;
   int n1=(DATA_BYTE==2)?16:0;
//panic("please implement me");
  if(DATA_BYTE==1 || DATA_BYTE==4)
  {
    op_src->simm=instr_fetch(eip,DATA_BYTE);
    op_src->simm=(op_src->simm<<n)>>n;
	op_src->val = op_src->simm;
  }
  else if(DATA_BYTE==2)
  {
		  op_src->simm=instr_fetch(eip,DATA_BYTE);
		  op_src->simm=(op_src->simm<<n1)>>n1;
		  op_src->val=op_src->simm;
  }

#ifdef DEBUG
	snprintf(op_src->str, OP_STR_SIZE, "$0x%x", op_src->val);
#endif
	return DATA_BYTE;
}
#endif

/* eAX */
static int concat(decode_a_, SUFFIX) (swaddr_t eip, Operand *op) {
	op->type = OP_TYPE_REG;
	op->reg = R_EAX;
	op->val = REG(R_EAX);

#ifdef DEBUG
	snprintf(op->str, OP_STR_SIZE, "%%%s", REG_NAME(R_EAX));
#endif
	return 0;
}

/* eXX: eAX, eCX, eDX, eBX, eSP, eBP, eSI, eDI */
static int concat3(decode_r_, SUFFIX, _internal) (swaddr_t eip, Operand *op) {
	op->type = OP_TYPE_REG;
	op->reg = ops_decoded.opcode & 0x7;
	op->val = REG(op->reg);

#ifdef DEBUG
	snprintf(op->str, OP_STR_SIZE, "%%%s", REG_NAME(op->reg));
#endif
	return 0;
}

static int concat3(decode_rm_, SUFFIX, _internal) (swaddr_t eip, Operand *rm, Operand *reg) {
	rm->size = DATA_BYTE;
	int len = read_ModR_M(eip, rm, reg);
	reg->val = REG(reg->reg);

#ifdef DEBUG
	snprintf(reg->str, OP_STR_SIZE, "%%%s", REG_NAME(reg->reg));
#endif
	return len;
}

/* Eb <- Gb
 * Ev <- Gv
 */
make_helper(concat(decode_r2rm_, SUFFIX)) {
	return decode_rm_internal(eip, op_dest, op_src);
}

/* Gb <- Eb
 * Gv <- Ev
 */
make_helper(concat(decode_rm2r_, SUFFIX)) {
	return decode_rm_internal(eip, op_src, op_dest);
}


/* AL <- Ib
 * eAX <- Iv
 */
make_helper(concat(decode_i2a_, SUFFIX)) {
	decode_a(eip, op_dest);
	return decode_i(eip);
}

/* Gv <- EvIb
 * Gv <- EvIv
 * use for imul */
make_helper(concat(decode_i_rm2r_, SUFFIX)) {
	int len = decode_rm_internal(eip, op_src2, op_dest);
	len += decode_i(eip + len);
	return len;
}

/* Eb <- Ib
 * Ev <- Iv
 */
make_helper(concat(decode_i2rm_, SUFFIX)) {
	int len = decode_rm_internal(eip, op_dest, op_src2);		/* op_src2 not use here */
	len += decode_i(eip + len);
	return len;
}

/* XX <- Ib 
 * eXX <- Iv 
 */
make_helper(concat(decode_i2r_, SUFFIX)) {
	decode_r_internal(eip, op_dest);
	return decode_i(eip);
}

/* used by unary operations */
make_helper(concat(decode_rm_, SUFFIX)) {
	return decode_rm_internal(eip, op_src, op_src2);		/* op_src2 not use here */
}

make_helper(concat(decode_r_, SUFFIX)) {
	return decode_r_internal(eip, op_src);
}

#if DATA_BYTE == 2 || DATA_BYTE == 4
make_helper(concat(decode_si2rm_, SUFFIX)) {
	int len = decode_rm_internal(eip, op_dest, op_src2);	/* op_src2 not use here */
	len += decode_si_b(eip + len);
	return len;
}

make_helper(concat(decode_si_rm2r_, SUFFIX)) {
	int len = decode_rm_internal(eip, op_src2, op_dest);
	len += decode_si_b(eip + len);
	return len;
}
#endif

/* used by shift instructions */
make_helper(concat(decode_rm_1_, SUFFIX)) {
	int len = decode_r2rm(eip);
	op_src->type = OP_TYPE_IMM;
	op_src->imm = 1;
	op_src->val = 1;
#ifdef DEBUG
	sprintf(op_src->str, "$1");
#endif
	return len;
}

make_helper(concat(decode_rm_cl_, SUFFIX)) {
	int len = decode_r2rm(eip);
	op_src->type = OP_TYPE_REG;
	op_src->reg = R_CL;
	op_src->val = reg_b(R_CL);
#ifdef DEBUG
	sprintf(op_src->str, "%%cl");
#endif
	return len;
}

make_helper(concat(decode_rm_imm_, SUFFIX)) {
	int len = decode_r2rm(eip);
	len += decode_i_b(eip + len);
	return len;
}

void concat(write_operand_, SUFFIX) (Operand *op, DATA_TYPE src) {
	if(op->type == OP_TYPE_REG) { REG(op->reg) = src; }
	else if(op->type == OP_TYPE_MEM) { swaddr_write(op->addr, op->size, src,3); }
	else { assert(0); }
}


#if DATA_BYTE==2 || DATA_BYTE==4
make_helper(concat(decode_jm2r_, SUFFIX))
{
  decode_rm_internal(eip,op_src,op_src2);
if (DATA_BYTE==2)
		return -2;
else if(DATA_BYTE==4)
		return -1; 

}
#endif
/*make_helper(concat(decode_call2r_, SUFFIX))
{
#if DATA_BYTE==2		
  int len=decode_rm_w(eip+1);
  uint32_t result=(eip+len+1)&0x0000ffff;
  swaddr_write(cpu.esp,2,result);
  return len+1;
#elif DATA_BYTE==4  
  int len=decode_rm_l(eip+1);
  uint32_t result=eip+len+1;
  swaddr_write(cpu.esp,4,result);
  return len+1;
#endif
}*/
make_helper(concat(decode_rmd2r_, SUFFIX)) {
		op_src->size=1;			
		   int len = read_ModR_M(eip, op_src, op_dest);
		//   printf("%d\n",op_dest->reg);
			op_dest-> val = REG(op_dest -> reg);
			return len;
}
make_helper(concat(decode_rmzd2r_, SUFFIX))
{
		op_src->size=2;
		int len = read_ModR_M(eip,op_src,op_dest);
		op_dest->val=REG(op_dest->reg);
		return len;
}

#include "cpu/exec/template-end.h"
