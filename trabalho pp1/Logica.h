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
player* Constructor(player* aux, int numero, char* nomeJogador, char* pref1, int pont1, char* pref2, int pont2, char* pref3, int pont3, char* pref4, int pont4, char* pref5, int pont5);
//Used to print player's data as show function
void showPlayer(player* data);

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
    bool atribuda;
} s_Player;


s_Player* SubListCons(int n, char* nickname, int pref, int pont);

//Main-list
typedef struct S_Gun {
    char* tipoArma;
    ListElem subList;
} s_Gun;

s_Gun* GunCons(char* gun, int numero, char* nick, int pref, int pont);
ListElem InsereArma(ListElem gunlist, char* gun, int numero, char* nick, int pref, int pont);
void ShowGuns(s_Gun* data);
ListElem InserirTudo(ListElem gunlist, ListElem MainList);
int FilterGuns(void* value);
int SortSubList(void* data1, void* data2);
ListElem SortMainList(ListElem gunList);
ListElem Sort2Table(void* player1, void* player2);
ListElem SortMain2Table(ListElem mainList);
void Atribuir(ListElem mainList);
