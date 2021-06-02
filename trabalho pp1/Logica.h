#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ll.h"
#include "File.h"

#define Empty NULL

#define TAMANHO 512
#define tamanho 64


//Alinea 1

typedef struct
{
    char gun[50]; // arma de combate
    int score; // 0 a 100
} Pref;

typedef struct dados
{
    int playerid;
    char nickname[50];
    Pref preferences[5]; // ordem de preferências (máximo de 5)
}player;

//Alinea 1 functions
player* EmptyPlayer();



//Alinea 2
/*
* Metralha -> [Jose(true), Maria, carlos]
* Sniper -> [Joao(true), Joana, Maria, Carlos]
* Espingarda -> [Joao, Joana(true)]
* Pistola -> [Joao, Joana, Carlos(true)]
*
*
*
* 4 armas 5 jogadores,
*/

//sub-list
typedef struct S_Player {
    int numero;
    char* nomeJogador;
    int pref;  //0 a 4
    int pontuacao;
    char* atribuda;
} s_Player;


s_Player* SubListCons(int n, char* nickname, int pref, int pont);

//Main-list
typedef struct S_Gun {
    char tipoArma[50];
    int qnt;
    ListElem subList;
} s_Gun;

s_Gun* EmptyGun();
void ShowGuns(s_Gun* data);
ListElem InserirTudo(ListElem playerlist, ListElem mainList);
ListElem SortMainList(ListElem gunList);
ListElem SortMain2Table(ListElem mainList);
ListElem Atribuir(ListElem mainList, int Nplayers);
void ExportData(char* filename, ListElem main);