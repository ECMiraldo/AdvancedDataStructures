#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Logica.h"

playerPref* Constructor(int numero, char* nomeJogador, char* pref1, int pont1, char* pref2, int pont2, char* pref3, int pont3) {
    playerPref* aux = (playerPref*)malloc(sizeof(playerPref));
    aux->numero = numero;
    aux->nomeJogador = nomeJogador;
    aux->preferencias[0] = pref1;
    aux->pontuacoes[0] = pont1;
    aux->preferencias[1] = pref2;
    aux->pontuacoes[1] = pont2;
    aux->preferencias[2] = pref3;
    aux->pontuacoes[2] = pont3;
    return aux;
}

playerPref* EmptyPref() {
    playerPref* aux = (playerPref*)malloc(sizeof(playerPref));
    aux->nomeJogador = NULL;
    aux->numero = 0;
    for (int i = 0; i < 5; i++) { //TO DO: NOT HARDCODED
        aux->preferencias[i] = NULL;
        aux->pontuacoes[i] = NULL;
    }
    return aux;
}


ListElem GunSnoc(char* tipoArma, int qnt, ListElem player) {
    s_Gun* gun = NULL;
    gun->tipoArma = tipoArma;
    gun->quantidade = qnt;
    gun->player = player;

    ListElem gunList = NULL;
    gunList = addItemLastRecursive(gunList, (s_Gun*)gun);
    return gunList;
}

ListElem PlayerSnoc(int n, char nome, int pont, bool at) {
    s_Player* player = NULL;
    player->numero = n;
    player->nomeJogador = nome;
    player->pontuacao = pont;
    player->atribuda = false;

    ListElem playerList = NULL;
    playerList = addItemLastRecursive(playerList, (s_Player*)player);
    return playerList;
}

void showPlayer(void* data) {
    playerPref* j = (playerPref*)data;
    if (j != NULL)
        printf("%d %s ", j->numero, j->nomeJogador);
    for (int i = 0; i < 5; i++) {
        printf("%s %d ", j->preferencias[i], j->pontuacoes[i]);
        printf("\n");
    }
}

int CompararPontuacao(char* gun, void* data1, void* data2) {
    playerPref* p1 = (playerPref*)data1;
    playerPref* p2 = (playerPref*)data2;
    
    int pontP1 = 0;
    int pontP2 = 0;
    for (int i = 0; i < 5; i++) {
        if (p1->preferencias[i] == gun) pontP1 = p1->pontuacoes[i];
        else if (p2->preferencias[i] == gun) pontP2 = p2->pontuacoes[i];
    }
    if (pontP1 > pontP2) return 1;
    else if (pontP1 < pontP2) return -1;
    else return 0;
}

int PontMax(s_Gun* GunList) {
    if (GunList != NULL) {
        s_Player* playerList = (s_Player*)GunList->player->data;
        int max = playerList->pontuacao;
        while (GunList->player != NULL) {
            GunList->player = GunList->player->next;
            playerList = (s_Player*)GunList->player->data;
            if (playerList->pontuacao > max) max = playerList->pontuacao;
        }
        return max;
    }
    else return NULL;
}

char** GetAllGuns(ListElem list) {
    if (list != NULL) {
        playerPref* prefList = (playerPref*)list->data;
        char** guns;
        while (list != NULL) {
            
        }
    }
}


//ListElem MainlistCons(ListElem list) {
//    playerPref* prefList = (playerPref*)list->data;
//
//    ListElem main = GunCons
//    Main->data = ReturnData(Main);
//
//}