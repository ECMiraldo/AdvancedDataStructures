#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ll.h"
#include "Logica.h"
#include "Examples.h"
#include "File.h"

int main(void) {
	ListElem lista1 = (ListElem)malloc(sizeof(ListElem));
	playerPref* pref = NULL;
	lista1->data = pref;
	ReadData("PP1.txt", lista1);
	return 0;
}