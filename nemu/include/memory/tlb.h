#include "common.h"
typedef struct
{
 uint32_t tag:20;
 uint32_t physical:20;
 uint32_t validbit:1;
}TLB;

TLB tlb[64];
