#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "setl-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "setl-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "setl-template.h"
#undef DATA_BYTE

make_helper(setl_rm_b);
