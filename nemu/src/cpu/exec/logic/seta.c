#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "seta-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "seta-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "seta-template.h"
#undef DATA_BYTE

make_helper(seta_rm_b);
