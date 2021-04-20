#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

#define Empty NULL

#define TAMANHO 512
#define tamanho 64

typedef enum { False, True } bool;

//Alinea 1

typedef struct L_Pref {
    char* nomeJogador;
    int numero;
    char* pref1;
    int pont1;
    char* pref2;
    int pont2;
    char* pref3;
    int pont3;
} l_Pref;
//Alinea 2

//sub-list
typedef struct S_Player {
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