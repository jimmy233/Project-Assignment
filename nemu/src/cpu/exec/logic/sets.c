#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "sets-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "sets-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "sets-template.h"
#undef DATA_BYTE

make_helper(sets_rm_b);
