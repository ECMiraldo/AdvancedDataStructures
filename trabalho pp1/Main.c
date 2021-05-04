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
	ListElem lista = NULL;

	lista = ReadData("PP1.txt", lista);
	showListIterative(lista, &showPlayer);

	ListElem main = NULL;
	main = InsereArma(main, "espingarda", 1, "pedro", 79);
	main = InsereArma(main, "rifle", 2, "joao", 79);


	printf("\n\n");
	showListIterative(main, &ShowGuns);




	
}