#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
void Create(char *);
void pinfo();
void delete(int);
void cpu_exec(uint32_t);
void bt_use();
/* We use the `readline' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args) {
        int number;
		if(args == NULL)
  {
     cpu_exec(1);
  }
  else
  {
	sscanf(args, "%d" , &number);
		  cpu_exec(number);
  }
 return 0;  
}
static int cmd_info(char *args){
 if(strcmp(args,"r")==0) 
 {
		 printf("eax       %#010x   %d\n",cpu.eax,cpu.eax);
		 printf("ecx       %#010x   %d\n",cpu.ecx,cpu.ecx);
		 printf("edx       %#010x   %d\n",cpu.edx,cpu.edx);
		 printf("ebx       %#010x   %d\n",cpu.ebx,cpu.ebx);
		 printf("esp       %#010x   %d\n",cpu.esp,cpu.esp);
		 printf("ebp       %#010x   %d\n",cpu.ebp,cpu.ebp);
		 printf("esi       %#010x   %d\n",cpu.esi,cpu.esi);
		 printf("edi       %#010x   %d\n",cpu.edi,cpu.edi);
		 printf("eip       %#010x   %d\n",cpu.eip,cpu.eip);
		 return 0;
 }
 else if(strcmp(args,"w")==0)
 {
   pinfo();
   return 0;
 }
 else
 {
		 return 0;
 }
}
static int cmd_x(char *args){
 char *s1=strtok(NULL," ");
 char *s2=strtok(NULL,"\n");
 if((s1!=NULL)&&(s2!=NULL))
 {
     int a;
	 sscanf(s1,"%d",&a);
	 swaddr_t b;
	 sscanf(s2,"%x",&b);
	 int j;
	 for(j=0;j<a;j++)
	 {  	
		 	 
         printf("%#010x:         %#010x\n",b,swaddr_read(b,4,3));
	 	 b=b+4;	 
	 }
 }
 return 0;
}
static int cmd_p(char *args){
		uint32_t result;
		bool a=true;
		result=expr(args,&a);
		
		printf("%s=%#010x\n",args,result);
		return 0;
}
static int cmd_w(char *args){
		Create(args);        
		return 0;
}
static int cmd_d(char *args){
        int i;
	    sscanf(args,"%d",&i);
		delete(i);
		return 0;
}
static int cmd_bt()
{
  bt_use();
  return 0;
}
static int cmd_cache(char *args)
{
		uint32_t result;
		bool a=true;
		result=expr(args,&a);
 uint32_t tag=(result>>13)&0x0007ffff;
 uint32_t num=result&0x0000003f;
 int i,j;
 int s=0;
 for(i=0;i<128;i++)
 {
   for(j=0;j<7;j++)
   {
     if(tag==cache[i].cache_block[j].tag)
         s=-1;
   }
   if(s==-1)break;
 }
 if(s==-1)
 {
	 	 printf("%d\n",cache[i].cache_block[j].validbit);
		 printf("%u\n",cache[i].cache_block[j].dataspace[num]);
 }
 else
   printf("Not fount!\n");

  return 0;
}
static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
	/* TODO: Add more commands */
	{ "si", "Run single step", cmd_si },
	{ "info", "Show imformation about all registers", cmd_info },
	{ "x", " Scan memory", cmd_x },
	{ "p", "Print the value of expression", cmd_p },
	{ "w", "Set a watchpoint", cmd_w },
	{ "d", "delete a watchpoint", cmd_d},
	{ "bt","printf the information of stack", cmd_bt},
	{ "cache", "printf the information of cache", cmd_cache},
};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}

void ui_mainloop() {
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
