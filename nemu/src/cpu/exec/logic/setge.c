#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "setge-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "setge-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "setge-template.h"
#undef DATA_BYTE

make_helper(setge_rm_b);
