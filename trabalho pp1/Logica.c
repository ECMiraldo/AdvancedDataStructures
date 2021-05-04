#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Logica.h"

//Alinea 1
//Aloca memoria para uma struct player e inicializa os seus dados com valores padrao
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

void ShowGuns(s_Gun* data) {
    if (data != NULL) {
        printf("%s", data->tipoArma);
      /*  while (data->player != NULL) {
            s_Player* p = data->player->data;
            printf("%d, %s, %d", p->numero, p->nomeJogador, p->pontuacao);
            data->player = data->player->next;
        }*/
    }
    printf("\n\n\n\n");
}

//Alinea 2
//Construtor para uma struct s_Player
s_Player* SubListCons(int n, char* nickname, int pont) {
    s_Player* aux = (s_Player*)malloc(sizeof(s_Player));
    aux->numero = n;
    aux->pontuacao = pont;
    aux->nomeJogador = nickname;
    aux->atribuda = false;
    return aux;
}
//Construtor para um nodo da lista principal
s_Gun* GunCons(char* gun, int numero, char* nick, int pont) {
    s_Gun* aux = (s_Gun*)malloc(sizeof(s_Gun));
    aux->tipoArma = gun;
    aux->player = SubListCons(numero, nick, pont);
    return aux;
}
//Rodar pela lista procurando uma arma com o mesmo nome gun,
//Se tiver insere todos os dados na sub-lista dessa arma
//Se nao encontrar, cria uma sub-lista nova com todos esses dados
ListElem InsereArma(ListElem gunlist, char* gun, int numero, char* nick, int pont) {
    if (gunlist == NULL)  gunlist = Cons(GunCons(gun, numero, nick, pont), NULL);
    else {
        s_Gun* gun = gunlist->data;
        if (strcmp(gun->tipoArma, gun) == 1) {
            gun->player = Snoc(gun->player, SubListCons(numero, nick, pont));
            return gunlist;
        }
        else gunlist->next = InsereArma(gunlist->next, gun, numero, nick, pont);
    }
}

ListElem InserirTudo(ListElem gunlist, ListElem MainList) {
    if (gunlist != NULL) {
        player* data = gunlist->data;
        for (int i = 0; i < 5; i++) {
            MainList = InsereArma(MainList, data->preferences[i].gun, data->playerid, data->nickname, data->preferences[i].score);
        }
        MainList = InserirTudo(gunlist->next, MainList);
    }
    else return MainList;
}




