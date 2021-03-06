#include "nemu.h"

#define ENTRY_START 0x100000

extern uint8_t entry [];
extern uint32_t entry_len;
extern char *exec_file;

void load_elf_tables(int, char *[]);
void init_regex();
void init_wp_pool();
void init_ddr3();

FILE *log_fp = NULL;

static void init_log() {
	log_fp = fopen("log.txt", "w");
	Assert(log_fp, "Can not open 'log.txt'");
}

static void welcome() {
	printf("Welcome to NEMU!\nThe executable is %s.\nFor help, type \"help\"\n",
			exec_file);
}

void init_monitor(int argc, char *argv[]) {
	/* Perform some global initialization */

	/* Open the log file. */
	init_log();

	/* Load the string table and symbol table from the ELF file for future use. */
	load_elf_tables(argc, argv);

	/* Compile the regular expressions. */
	init_regex();

	/* Initialize the watchpoint pool. */
	init_wp_pool();

	/* Display welcome message. */
	welcome();
}

#ifdef USE_RAMDISK
static void init_ramdisk() {
	int ret;
	const int ramdisk_max_size = 0xa0000;
	FILE *fp = fopen(exec_file, "rb");
	Assert(fp, "Can not open '%s'", exec_file);

	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);
	Assert(file_size < ramdisk_max_size, "file size(%zd) too large", file_size);

	fseek(fp, 0, SEEK_SET);
	ret = fread(hwa_to_va(0), file_size, 1, fp);
	assert(ret == 1);
	fclose(fp);
}
#endif

static void load_entry() {
	int ret;
	FILE *fp = fopen("entry", "rb");
	Assert(fp, "Can not open 'entry'");

	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	ret = fread(hwa_to_va(ENTRY_START), file_size, 1, fp);
	assert(ret == 1);
	fclose(fp);
}

void restart() {
	/* Perform some initialization to restart a program */
#ifdef USE_RAMDISK
	/* Read the file with name `argv[1]' into ramdisk. */
	init_ramdisk();
#endif

	/* Read the entry code into memory. */
	load_entry();

	/* Set the initial instruction pointer. */
	cpu.eip = ENTRY_START;
	cpu.EFLAGS.CF=0;
	cpu.EFLAGS.PF=0;
	cpu.EFLAGS.ZF=0;
	cpu.EFLAGS.SF=0;
	cpu.EFLAGS.IF=0;
	cpu.EFLAGS.DF=0;
	cpu.EFLAGS.OF=0;

	/* Initialize DRAM. */
	init_ddr3();
	/* Initialize Cache1*/
	int i,j;
	for(i=0;i<128;i++)
	{
			for(j=0;j<8;j++)
					cache[i].cache_block[j].validbit=false;
	}
    int m,n;
	for(m=0;m<4096;m++)
	{
			for(n=0;n<16;n++)
			{
		//		cacheL2[m].cache2_block[n].dirtybit=false;
					cacheL2[m].cache2_block[n].validbit=false;
			}
	}
	/* Initialize CR0 */
    cpu.CR0.protect_enable=0;
    cpu.CR0.paging=0;
   	cpu.CS.CACHE.base=0;
	cpu.CS.CACHE.limit=0xffffffff;	
       
	int p;
	for(p=0;p<64;p++)
			tlb[p].validbit=0;

}
