#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Logica.h"

player* EmptyPlayer() {
    player* aux = (player*)malloc(sizeof(player));
    aux->playerid = 0;
    strcpy(aux->nickname, "unnamed");
    for (int i = 0; i < 5; i++) {
        strcpy(aux->preferences[i].gun, "N/A");
        aux->preferences[i].score = 0;
    }
    return aux;
}
player* Constructor(player* aux, int numero, char* nomeJogador, char* pref1, int pont1, char* pref2, int pont2, char* pref3, int pont3, char* pref4, int pont4, char* pref5, int pont5) {
    aux->playerid = numero;
    strcpy(aux->nickname, nomeJogador);
    strcpy(aux->preferences[0].gun, pref1);
    strcpy(aux->preferences[1].gun, pref2);
    strcpy(aux->preferences[2].gun, pref3);
    strcpy(aux->preferences[3].gun, pref4);
    strcpy(aux->preferences[4].gun, pref5);

    aux->preferences[0].score = pont1;
    aux->preferences[1].score = pont2;
    aux->preferences[2].score = pont3;
    aux->preferences[3].score = pont4;
    aux->preferences[4].score = pont5;
    return aux;
}

// Escrita na consola do dados de um jogador
void showPlayer(player* data) {     
    if (data != NULL) {
        printf("%d %s ", data->playerid, data->nickname);
        for (int i = 0; i < 5; i++) {
            printf("%s %d ", data->preferences[i].gun, data->preferences[i].score);
        }
    }
    printf("\n");
}

ListElem GetAllGuns(ListElem playerlist) {
    if (playerlist != NULL) {
        ListElem aux = NULL;
        char gun[50];

        while (playerlist != NULL) {
            player* p = playerlist->data;
            for (int i = 0; i < 5; i++) {
                strcpy(gun, p->preferences[i].gun);
                if (gun != '-' && ContainsRec(aux, gun) == 0) {
                    aux = addItemLastRecursive(aux, gun);
                }
            }
            playerlist = playerlist->next;
        }
        return aux;
    }
    else return NULL;
}

void PrintGuns(char* data) {
    if (data != NULL) printf("%s \n", data);
}


//ListElem GunSnoc(char* tipoArma, int qnt, ListElem player) {
//    s_Gun* gun = NULL;
//    gun->tipoArma = tipoArma;
//    gun->quantidade = qnt;
//    gun->player = player;
//
//    ListElem gunList = NULL;
//    gunList = addItemLastRecursive(gunList, (s_Gun*)gun);
//    return gunList;
//}
//
//ListElem PlayerSnoc(int n, char nome, int pont, bool at) {
//    s_Player* player = NULL;
//    player->numero = n;
//    player->nomeJogador = nome;
//    player->pontuacao = pont;
//    player->atribuda = false;
//
//    ListElem playerList = NULL;
//    playerList = addItemLastRecursive(playerList, (s_Player*)player);
//    return playerList;
//}
//
//void showPlayer(void* data) {
//    playerPref* j = (playerPref*)data;
//    if (j != NULL)
//        printf("%d %s ", j->numero, j->nomeJogador);
//    for (int i = 0; i < 5; i++) {
//        printf("%s %d ", j->preferencias[i], j->pontuacoes[i]);
//        printf("\n");
//    }
//}
//
//int CompararPontuacao(char* gun, void* data1, void* data2) {
//    playerPref* p1 = (playerPref*)data1;
//    playerPref* p2 = (playerPref*)data2;
//    
//    int pontP1 = 0;
//    int pontP2 = 0;
//    for (int i = 0; i < 5; i++) {
//        if (p1->preferencias[i] == gun) pontP1 = p1->pontuacoes[i];
//        else if (p2->preferencias[i] == gun) pontP2 = p2->pontuacoes[i];
//    }
//    if (pontP1 > pontP2) return 1;
//    else if (pontP1 < pontP2) return -1;
//    else return 0;
//}
//
//int PontMax(s_Gun* GunList) {
//    if (GunList != NULL) {
//        s_Player* playerList = (s_Player*)GunList->player->data;
//        int max = playerList->pontuacao;
//        while (GunList->player != NULL) {
//            GunList->player = GunList->player->next;
//            playerList = (s_Player*)GunList->player->data;
//            if (playerList->pontuacao > max) max = playerList->pontuacao;
//        }
//        return max;
//    }
//    else return NULL;
//}


//ListElem MainlistCons(ListElem list) {
//    playerPref* prefList = (playerPref*)list->data;
//
//    ListElem main = GunCons
//    Main->data = ReturnData(Main);
//
//}


