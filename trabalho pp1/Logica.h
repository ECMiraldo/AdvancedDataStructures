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
player* Constructor(int numero, char* nomeJogador, char* pref1, int pont1, char* pref2, int pont2, char* pref3, int pont3, char* pref4, int pont4, char* pref5, int pont5);
//Used to print player's data as show function
void showPlayer(player* data);
//Returns a list of char* with all the guns;
ListElem GetAllGuns(ListElem head);
//Prints elements of a list of char*
void PrintGuns(char* data);

int igual(void* data1, void* data2);

//Alinea 2

//sub-list
typedef struct S_Player {
    int numero;
    char* nomeJogador;
    int pontuacao;
    bool atribuda;
} s_Player;


//Main-list
typedef struct S_Gun {
    char* tipoArma;
    int quantidade;
    ListElem player;
} s_Gun;