#include "common.h"

typedef struct{
		uint8_t dataspace[64];
		bool validbit;
		uint32_t tag;
}cache_slot;

typedef struct{
		cache_slot cache_block[8];
}cache1;

extern cache1 cache[128];
