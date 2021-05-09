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

void ShowInt(void* a) {
	printf("%d, ", (int)a);
}

int CmpInt(void* va, void* vb) {
	int a = (int) va;
	int b = (int) vb;
	if (a < b) return -1;
	if (a == b) return 0;
	else return 1;
}

int main(void) {
	ListElem lista = NULL;

	lista = ReadData("PP1.txt");
	showListIterative(lista, &showPlayer);

	ListElem main = NULL;

	printf("\n\n");
	/*showListIterative(main, &ShowGuns);*/

	main = InserirTudo(lista, main);
	//main = Filter(main, &FilterGuns);
	main = SortMainList(main);
	
	Atribuir(main);
	showListIterative(main, &ShowGuns);
	SortMain2Table(main);
	showListIterative(main, &ShowGuns);



	//ListElem l1 = Cons(10, Cons(5, Cons(25, Cons(42, Cons(4, NULL)))));



	//showListIterative(MergeSort(l1, &CmpInt), &ShowInt);




	
}