#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "setg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "setg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "setg-template.h"
#undef DATA_BYTE

make_helper(setg_rm_b);
