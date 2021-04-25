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
	player* j;

	//j = Constructor(1, "Sara", "Sniper", 87, "pistola", 67, "metralhadora", 57, "-", 0, "-", 0);
	//lista = addItemHead(lista, j);
	//
	//
	//j = Constructor(2, "Bruno", "metralhadora", 77, "sniper", 79, "-", 0, "-", 0, "-", 0);
	//lista = addItemLastIterative(lista, j);


	lista = ReadData("PP1.txt", lista);
	//showListIterative(lista, &showPlayer);



	//j = (Jogador)malloc(sizeof(struct dados));
	//j->numero = 2;
	//strcpy(j->nome, "Jose");
	//strcpy(j->preferencias[0].arma, "sniper");
	//j->preferencias[0].pontuacao = 87;
	//strcpy(j->preferencias[1].arma, "pistola");
	//j->preferencias[1].pontuacao = 67;
	//strcpy(j->preferencias[2].arma, "metralhadora");
	//j->preferencias[2].pontuacao = 57;
	//strcpy(j->preferencias[3].arma, "-");
	//j->preferencias[3].pontuacao = 0;
	//strcpy(j->preferencias[4].arma, "-");
	//j->preferencias[4].pontuacao = 0;
	//// lista = addItemHead(lista,j);
	//lista = addItemOrderedIterative(lista, j, &compararNomes);




	// Escrita na consola do conteúdo da lista ligada

	printf("-----------------------------------------------------------\n");
	int numero = 2;
	// Remoção da primeiro ocorrência do registo com número de jogador 2
	/*lista = removeItemIterative(lista, &numero, &igual);*/

	// Escrita na consola do conteúdo da lista ligada
}