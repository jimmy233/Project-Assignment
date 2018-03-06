#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
uint32_t get_object(char *name);
enum {
	NOTYPE = 256, EQ, ADD, SUB, LEAL, DIV, LEFT, RIGHT, OR, HNUM, NUM, REG, NEQ, NOT, AND, DEREF, NEG, OBJECT

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"\\+", '+'},					// plus
	{"\\=\\=", EQ},						// equal
	{"\\-", '-'},                   // sub
	{"\\*", '*'},	                // leal
    {"\\/", '/'},                   // div
	{"\\(", '('},                   // left
	{"\\)", ')'},                   // right
	{"\\|\\|", OR},                  // or
	{"0[xX][0-9a-fA-F]+", HNUM},    // hnum
	{"[0-9]+", NUM},               //num
	{"\\$[a-z]+", REG},            // reg
	{"\\!\\=", NEQ},                 // neq
	{"\\!", NOT},                   // not
	{"\\&\\&", AND},                // and
    {"[a-zA-Z][0-9a-zA-Z_]+", OBJECT},//object
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex(){             
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret == 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

		 //		Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array `tokens'. For certain types
				 * of tokens, some extra actions should be performed.
				 */

				switch(rules[i].token_type) {
					    case '+':{
								  tokens[nr_token].type='+';
						          strcpy(tokens[nr_token].str,"+");
								  nr_token++;
						 		  break;		  
								 };
						case '-':{
								  tokens[nr_token].type='-';
								  strcpy(tokens[nr_token].str,"-");
								  nr_token++;
								  break;
								 };
						case EQ:{
			   					  tokens[nr_token].type=EQ;
					  			  strcpy(tokens[nr_token].str,"==");
								  nr_token++;
								  break;
								};
						case '*':{
								  tokens[nr_token].type='*';
						  		  strcpy(tokens[nr_token].str,"*");
                                  nr_token++;
								  break;
								 };
                        case '/':{
								   tokens[nr_token].type='/';
								   strcpy(tokens[nr_token].str,"/");
								   nr_token++;
								   break;
								 };
						case '(':{
			   					   tokens[nr_token].type='(';
					   			   strcpy(tokens[nr_token].str,"(");
									nr_token++;
					 				break;
								 };				
  						case ')':{
								    tokens[nr_token].type=')';
									strcpy(tokens[nr_token].str,")");
									nr_token++;
									break;
								 };
						case NUM:{
									tokens[nr_token].type=NUM;
								strcpy(tokens[nr_token].str,substr_start);
							//	printf("%s\n",substr_start);
								    nr_token++;
									break;
								 };
						case OR:{
									tokens[nr_token].type=OR;
									strcpy(tokens[nr_token].str,"||");
									nr_token++;
									break;
							    };
					    case HNUM:{
							   		tokens[nr_token].type=HNUM;
					  				strcpy(tokens[nr_token].str,substr_start);
									nr_token++;
									break;
					 			  };	
					    case NEQ:{
						   			tokens[nr_token].type=NEQ;
				   					strcpy(tokens[nr_token].str,"!=");
						            nr_token++;
									break;
								 };
						case NOT:{
									tokens[nr_token].type=NOT;
				   					strcpy(tokens[nr_token].str,"!");
									nr_token++;
									break;
								 };
						case AND:{
									tokens[nr_token].type=AND;
			   						strcpy(tokens[nr_token].str,"&&");
									nr_token++;
									break;
								 };
		 				case REG:{
									tokens[nr_token].type=REG;
		   						//	strcpy(tokens[nr_token].str,substr_start);
							int m;
									for(m=0;m<4;m++)
								tokens[nr_token].str[m]=substr_start[m];
									tokens[nr_token].str[4]='\0';

								//printf("%s\n",substr_start);
									//don't need $
									nr_token++;
									break;
								 };
                        case OBJECT:
								 {
								    tokens[nr_token].type=OBJECT;
									char s[40];
									int i=0;
									while(substr_start[i]!='+'&&substr_start[i]!='-'&&substr_start[i]!='*'&&substr_start[i]!='/'&&substr_start[i]!='='&&substr_start[i]!='!'&&substr_start[i]!='$'&&substr_start[i]!='('&&substr_start[i]!=')'&&substr_start[i]!='&')
									{
											s[i]=substr_start[i];
											i++;
											if(substr_start[i]=='\0')break;
									}
									s[i]='\0';
									strcpy(tokens[nr_token].str,s);
					//				printf("%s\n",s);
									nr_token++;
									break;
								 }
	                    case NOTYPE: break;							 
					default: panic("please implement me");
				}

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

bool check_parentheses(int begin, int end)
{ 
 // Stack s;	
  if(begin>end)
    return false;
  if((tokens[begin].type!='(') || (tokens[end].type!=')'))
	return false;
 
  int i;
  int left=0;
  int right=0;
  int f=0;
  int CF=0;
  for(i=begin+1;i<=end-1;i++)
  {
    if(tokens[i].type=='(')
	{ left++;
	  f++;
	}
    if(tokens[i].type==')')
	{
			right++;
			f--;
	}
	
	if(f<0)
		CF=1;
  }
  if((left!=right)||(CF==1)||(f!=0)) 
   		  return false;
  else
		  return true;
}
uint32_t eval(int p,int q)
{
  if(p>q)
  {
   return 0;
  }		 
  else if(p==q)
  {
		  uint32_t num=0;
 	if(tokens[p].type==REG)
	{
	  if(strcmp(tokens[p].str,"$eax")==0)		
	  {
			  num=cpu.eax;
	//	  	  return num;
	  }
	  else if(strcmp(tokens[p].str,"$ebx")==0)
	  {
			  num=cpu.ebx;
	//		  return num;
	  }
	  else if(strcmp(tokens[p].str,"$ecx")==0)
	  {
			  num=cpu.ecx;
	//		  return num;
	  }
	  else if(strcmp(tokens[p].str,"$edx")==0)
	  {	
			num=cpu.edx;
	//	  	return num;
	  }
	  else if(strcmp(tokens[p].str,"$esp")==0)
	  {
			  num=cpu.esp;
	//		  return num;
	  }
	  else if(strcmp(tokens[p].str,"$ebp")==0)
	  {
			 num=cpu.ebp;
  // 			 return num;
	  }
	  else if(strcmp(tokens[p].str,"$esi")==0)
	  {
			  num=cpu.esi;
//			  return num;
	  }
	  else if(strcmp(tokens[p].str,"$eip")==0)
	  {
			  num=cpu.eip;
//	  printf("%x",cpu.eip);
			  //return num;
	  }
			   
  // num=strtoul(tokens[p].str,0,0);  
	}
 else if(tokens[p].type==OBJECT)
 {
  num=get_object(tokens[p].str);
 }
	else
			num=strtoul(tokens[p].str,0,0);
//	printf("%x\n",num);
  return num; 
  }
  else if(check_parentheses(p,q)==true)
  {
    return eval(p+1,q-1);
  }  
  else
  {
 /*find op*/
   int op;
   int bracket=0;
   int opt[8];//0 OR 1 AND (2 != and ==) (3 + -) (4 * /) (5 !)
   int j;
   for(j=0;j<8;j++)
     opt[j]=-1;
   
   int i;
   for(i=q;i>=p;i--)
   {
		   if(tokens[i].type=='(')
				   bracket++;
		   else if(tokens[i].type==')')
				   bracket--;
		   else
		   {
             if(bracket==0)
			 {
					 if(tokens[i].type=='+' && opt[3]==-1)
							 opt[3]=i;
					 else if(tokens[i].type=='-' && opt[3]==-1)
							 opt[3]=i;
					 else if(tokens[i].type==OR && opt[0]==-1)
							 opt[0]=i;
					 else if(tokens[i].type==AND && opt[1]==-1)
							 opt[1]=i;
					 else if(tokens[i].type=='*' && opt[4]==-1)
							 opt[4]=i;
					 else if(tokens[i].type=='/' && opt[4]==-1)
							 opt[4]=i;
	                 else if(tokens[i].type==NOT && opt[5]==-1)
							 opt[5]=i;	
					 else if(tokens[i].type==NEG && opt[5]==-1)
							 opt[5]=i;
					 else if(tokens[i].type==DEREF && opt[5]==-1)
							 opt[5]=i;
		             else if(tokens[i].type==NEQ && opt[2]==-1)
							 opt[2]=i;
		             else if(tokens[i].type==EQ && opt[2]==-1)
						     opt[2]=i;			 
							 
			 }	 
		   }			   
   }
   int m;
   for(m=0;m<8;m++)
   {
		   if(opt[m]!=-1)break;
   } 
   op=opt[m];
  
 			  
   /*calculate*/
   uint32_t val1,val2;
   
   	val1=eval(p,op-1);
   val2=eval(op+1,q);
   int ty1=tokens[op].type;
// printf("%d\n",opt[3]);
 
// printf("%d\n",val1);
   switch(ty1) 
	 {
			 case '+': return val1+val2;
			 case '-': return val1-val2;
			 case '*': return val1*val2;
			 case '/': return val1/val2;
			 case DEREF: return swaddr_read(val2,4,3);			 
			 case NEG: return -val2;
					   
			 case NOT:{  
						
							  if(val2==0)
									  return 1;
							  else
									  return 0;

					  };

			 case AND:{
							  if(val1==0 || val2==0)
									  return 0;
							  else
									  return 1;
					  };
			 case OR:{
							if(val1==0 && val2==0)
								      return 0;
						    else 
								     return 1;
					 };
			 case NEQ:{
							  if(val1!=val2)
									  return 1;
							  else
									  return 0;
					  };
			 case EQ:{
							 if(val1==val2)
									 return 1;
							  else
									 return 0;
					 };
	 
			default: assert(0);
						    	 
	 }
  } 
}
/*checkexpression*/
bool checkex(int a)
{
  int bracket=0;
  int t=0;
  int i;
  for(i=0;i<a;i++)
  {
		  if(tokens[i].type=='(')
		  {
				  bracket++;
                  if(tokens[i+1].type=='+' || tokens[i+1].type=='/' || tokens[i+1].type==')'||tokens[i+1].type == AND|| tokens[i+1].type==OR || tokens[i+1].type==NEQ|| tokens[i+1].type==EQ)
						  return false;
		  }
		  else if(tokens[i].type==')')
		  {
		      bracket--;
			  if(tokens[i+1].type==NUM||tokens[i+1].type==REG||tokens[i+1].type==HNUM)
			  return false;
		  }
		  if(bracket<0)
				  t=-1;
  }
  if(t==-1||bracket!=0)
		  return false;		  
  return true;

}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	int i;
  for(i=0;i<nr_token;i++) 
  {
		 
		  if(tokens[i].type=='*')
		  {
				  if(i==0||tokens[i-1].type=='+'||tokens[i-1].type=='-'||tokens[i-1].type=='*'||tokens[i-1].type=='/'||tokens[i-1].type=='('||tokens[i-1].type==NOT||tokens[i-1].type==OR||tokens[i-1].type==AND||tokens[i-1].type==EQ||tokens[i-1].type==NEQ||tokens[i+1].type==OBJECT)
						  tokens[i].type=DEREF;
		  }
		  if(tokens[i].type=='-')
		  {
				  if(i==0||tokens[i-1].type=='+'||tokens[i-1].type=='-'||tokens[i-1].type=='*'||tokens[i-1].type=='/'||tokens[i-1].type=='('||tokens[i-1].type==NOT||tokens[i-1].type==OR||tokens[i-1].type==AND||tokens[i-1].type==EQ||tokens[i-1].type==NEQ)
						  tokens[i].type=NEG;
		  }
  }
     
	/* TODO: Insert codes to evaluate the expression. */
  /*	panic("please implement me");
	return 0;*/
		  /*check the expression before eval */
	if(checkex(nr_token)==true)
	{
	uint32_t result;
	result=eval(0,nr_token-1);
	return result;
	}
	else
	{
			printf("The expression has errors\n");
			return 0;
	}
}

