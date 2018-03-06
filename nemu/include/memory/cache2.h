#include "common.h"

typedef struct 
{
	uint32_t tag;
	bool validbit;
	bool dirtybit;
	uint8_t dataspace[64];
}cache2_slot;

typedef struct
{
 cache2_slot cache2_block[16]; 
}cache2;

extern cache2 cacheL2[4096];
