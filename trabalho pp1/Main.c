#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

#define TAMANHO 512
#define tamanho 64

//sub-list
typedef struct Pref {
	char   wPref[tamanho]; //Tipo de arma de preferencia
	int    spec;
} SPref;

//main list
typedef struct player {
	char   nickname[tamanho];
	ListElem  Pref;
} SPlayer;

int main(void) {
	ListElem listPref = NULL;
	void* data;
	addItemHead(listPref, (SPref*)data);



	return 0;
}