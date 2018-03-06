#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "common.h"

typedef struct watchpoint {
	int NO;
	int identifier;
	uint32_t num;
	char expr[100];
	struct watchpoint *next;

	/* TODO: Add more members if necessary */


} WP;

#endif
