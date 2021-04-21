#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ll.h"

#define Empty NULL

#define TAMANHO 512
#define tamanho 64


//Alinea 1

typedef struct L_Pref {
    char* nomeJogador;
    int numero;
    char* preferencias[5];
    int* pontuacoes[5];
} playerPref;


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