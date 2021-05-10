#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "ll.h"
#include "Logica.h"
#include "File.h"

int main(void) {
	ListElem lista = NULL;
	ListElem main = NULL;
	lista = ReadData("PP1.txt");
	main = InserirTudo(lista, main);
	main = SortMainList(main);
	Atribuir(main);
	main = SortMainList(main);
	main = SortMain2Table(main);
	showListIterative(main, &ShowGuns);
	ExportData("PP1_result.txt", main);
}