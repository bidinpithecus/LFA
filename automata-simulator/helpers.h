#ifndef _HELPERS_H
#define _HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void systemPause(void) {
  printf("Pressione enter para continuar...");
  getchar();
}

#ifdef WIN32
	void clearScreen(void) {
	  system("cls");
	}
#else
	void clearScreen(void) {
	  system("clear");
	}
#endif

#endif