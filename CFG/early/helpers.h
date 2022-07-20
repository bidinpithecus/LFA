#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"

void printGroup(Group group) {
	printf("{ ");
	for (int i = 0; i < group.size; i++) {
		if (i == group.size - 1) {
			printf("%c }\n", group.group[i]);
		} else {
			printf("%c, ", group.group[i]);
		}
	}
}

#endif