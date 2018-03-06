#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
   long long int a1=(long long int)a;
  long long int b1=(long long int)b;
  long long int result=a1*b1;
  
  if(result>=0)
	result=result>>16;
  else  
	result=-((-result)>>16);
	//nemu_assert(0);
	FLOAT re=(FLOAT)result;
	return re;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	/* Dividing two 64-bit integers needs the support of another library
	 * `libgcc', other than newlib. It is a dirty work to port `libgcc'
	 * to NEMU. In fact, it is unnecessary to perform a "64/64" division
	 * here. A "64/32" division is enough.
	 *
	 * To perform a "64/32" division, you can use the x86 instruction
	 * `div' or `idiv' by inline assembly. We provide a template for you
	 * to prevent you from uncessary details.
	 *
	 *     asm volatile ("??? %2" : "=a"(???), "=d"(???) : "r"(???), "a"(???), "d"(???));
	 *
	 * If you want to use the template above, you should fill the "???"
	 * correctly. For more information, please read the i386 manual for
	 * division instructions, and search the Internet about "inline assembly".
	 * It is OK not to use the template above, but you should figure
	 * out another way to perform the division.
	 */
     
	int result=a/b;
	if(result<0)
			result--;
	int r3=a%b;
	int r2=(int)b;
	int r4=r3<<16;
	int result1;
	int result2;
	int c=r3>>16;
 asm volatile("idivl %2" : "=a"(result1), "=d"(result2) : "r"(r2), "a"(r4), "d"(c));  
   int r5=result1&0x0000ffff;
   result=(result<<16)|r5;
   
   return result;
//nemu_assert(0);

}

FLOAT f2F(float a) {
	/* You should figure out how to convert `a' into FLOAT without
	 * introducing x87 floating point instructions. Else you can
	 * not run this code in NEMU before implementing x87 floating
	 * point instructions, which is contrary to our expectation.
	 *
	 * Hint: The bit representation of `a' is already on the
	 * stack. How do you retrieve it to another variable without
	 * performing arithmetic operations on it directly?
	 */
/*
	int ival=*((int*)&a);
	int mantissa=(ival&0x7fffff)|0x800000;
	int exponent=150-((ival>>23)&0xff);
	if(exponent<0)
	{
			ival=((mantissa<<-exponent)<<16);
	}
	else
			ival=((mantissa>>exponent)<<16);
	if((*(int *)&a)&0x80000000)
			ival=-ival;

	return ival;
 */
int ival=*((int*)&a);
	int r1=(ival>>23)&0xff;
    int r2=(ival&0x7fffff)|0x800000;
	int ex=r1-127;
	int bias=23-ex;
	int m=((r2>>bias)<<16)&0x7fff0000;
	r2=((r2<<(32-bias))>>16)&0x0000ffff;
	int result=m+r2;
	if(((ival>>31)&0x1)==1)
		return -result;
	else
		return result;
//nemu_assert(0);
     
//	return 0
}

FLOAT Fabs(FLOAT a) {
		FLOAT result;
	if(a>=0)
			result=a;
	else
			result=-a;
//	nemu_assert(0);
	return result;
}

/* Functions below are already implemented */

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}
