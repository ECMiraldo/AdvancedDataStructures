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


//Alinea 2

//Nodo vazio da lista principal
s_Gun* EmptyGun() {
    s_Gun* aux = (s_Gun*)malloc(sizeof(s_Gun));
    strcpy(aux->tipoArma, "N/A");
    aux->qnt = 0;
    aux->subList = NULL;
    return aux;
}

//Para testar, pedir para mostrar a preferencia, ajuda bastante.
void ShowSubList(s_Player* data) {
    if (data != NULL) {
        printf("Jogador numero: %d \t Nick: %s \t Pont: %d \t  %s \n",
            data->numero,
            data->nomeJogador,
            data->pontuacao,
            data->atribuda);
    }
}

//Mostra a lista principal
void ShowGuns(s_Gun* data) {
    if (data != NULL) {
        printf("Arma: %s \nQnt: %d \n", data->tipoArma, data->qnt);
        /*printf("Qnt: %d", data->qnt);*/
        printf("\n");
        showListIterative(data->subList, &ShowSubList);
    }
    printf("\n\n");
}

//Construtor para o conteudo de um nodo da sublista
s_Player* SubListCons(int n, char* nickname, int pref, int pont) {
    s_Player* aux = (s_Player*)malloc(sizeof(s_Player));
    aux->numero = n;
    aux->pontuacao = pont;
    aux->pref = pref;
    aux->nomeJogador = nickname;
    aux->atribuda = " ";
    return aux;
}

//Insere um jogador com todas suas armas na lista principal
ListElem InserePlayer(ListElem mainList, player* player) {
    if (mainList == NULL || player == NULL) return NULL;
    ListElem aux = mainList;
    while (aux != NULL) {
        s_Gun* gunNode = (s_Gun*)aux->data;
        for (int i = 0; i < 5; i++) {
            if (strcmp(player->preferences[i].gun, gunNode->tipoArma) == 0) {
                gunNode->subList = Cons(SubListCons(player->playerid,
                                                    player->nickname,
                                                    i,
                                                    player->preferences[i].score),
                                                    gunNode->subList);
            }
        }
        aux = aux->next;
    }
    return mainList;
}

//Insere todos jogadores da lista da alinea 1 na lista principal
ListElem InserirTudo(ListElem playerlist, ListElem mainList) {
    if (playerlist != NULL) {
        player* data = playerlist->data;
        InserePlayer(mainList, data);
        InserirTudo(playerlist->next, mainList);
    }
    else return mainList;
}

int SortSubList(void* player1, void* player2) {
    s_Player* p1 = (s_Player*)player1;
    s_Player* p2 = (s_Player*)player2;

    if (p1->pref > p2->pref) return 1;
    if (p1->pref < p2->pref) return -1;
    else {
        if (p1->pontuacao > p2->pontuacao) return -1;
        if (p1->pontuacao < p2->pontuacao) return 1;
        else return 0;
    }
}

ListElem SortMainList(ListElem gunList) {
    if (gunList == NULL) return NULL;
    s_Gun* mainNode = (s_Gun*)gunList->data;
    mainNode->subList = MergeSort(mainNode->subList, &SortSubList);
    gunList->next = SortMainList(gunList->next);
    return gunList;
}

int CmpPlayer(ListElem subList) {
    if (subList == NULL) return -1;
    s_Player* player = (s_Player*)subList->data;
    if (subList->next != NULL) {

        s_Player* playernext = (s_Player*)subList->next->data;
        if (player->pref < playernext->pref) return 1;
        else {
            if (player->pontuacao > playernext->pontuacao) return 1;
            else if (player->pref == playernext->pref &&
                player->pontuacao == playernext->pontuacao) return 0;
            else return -1;
        }
    }
    else return -1;
}

ListElem Atribuir(ListElem mainList, int Nplayers) {
    ListElem playersatribuidos = Empty;
    int preferenciaactual = 0;
    char* guns[TAMANHO];
    for (int i = 0; i < Nplayers; i++) {
        guns[i] = "Sem Arma";
    }
    while (preferenciaactual < 5) {
        ListElem aux = mainList;
        while (aux != NULL) {
            s_Gun* data = (s_Gun*)aux->data;
            if (data->qnt > 0) {
                ListElem subList = data->subList;
                while (subList != NULL) {
                    s_Player* playerdata = (s_Player*)subList->data; /*primeiro nodo da sub-lista*/
                    if (guns[playerdata->numero - 1] == "Sem Arma") { //Se esse jogador ja nao tem uma arma
                    //A lista ja se encontra ordenada, ou seja, 
                    //devemos atribuir ao primeiro jogador de cada sublista,
                    //excepto se esse jogador tiver alguma outra arma numa preferencia maior
                        if (data->qnt > 0 && playerdata->pref == preferenciaactual) { //Se foi a primeira preferencia dele e existe um exemplar dessa arma para atribuir
                            if (CmpPlayer(subList) == 0) { //Verificamos se ha empate
                                playerdata->pref = -1;
                                data->qnt--;
                                guns[playerdata->numero - 1] = data->tipoArma;
                                playerdata->atribuda = "Atribuida (Empate)";
                                playerdata = (s_Player*)subList->next->data;
                                playerdata->atribuda = "Atribuida (Empate)";
                                playerdata->pref = -1;
                                data->qnt--;
                                guns[playerdata->numero - 1] = data->tipoArma;
                            }
                            else {
                                playerdata->atribuda = "Atribuida";
                                playerdata->pref = -1;
                                data->qnt--;
                                guns[playerdata->numero - 1] = data->tipoArma;
                            }
                        }
                    }
                    subList = subList->next;
                }
            }
            aux = aux->next;
        }
        preferenciaactual++;
    }
    //Se depois deste algoritmo, o jogador ainda esta sem arma, entao indicamos
    ListElem aux = mainList;
    while (aux != NULL) {
        s_Gun* data = (s_Gun*)aux->data;
        ListElem subList = data->subList;
        while (subList != NULL) {
            s_Player* playerdata = (s_Player*)subList->data;
            if (guns[playerdata->numero - 1] == "Sem Arma") playerdata->atribuda = "Sem Arma";
            //playerdata->atribuda = guns[playerdata->numero -1];
            subList = subList->next;
        }
        aux = aux->next;
    }
    return mainList;
}

//Alinea 3

int Sort2Table(void* player1, void* player2) {
    s_Player* p1 = (s_Player*)player1;
    s_Player* p2 = (s_Player*)player2;
    
    if (p1->pref == -1) {
        if (p2->pref == -1) {
            if (p1->pontuacao > p2->pontuacao) return -1;
            if (p1->pontuacao < p2->pontuacao) return 1;
            else {
                if (p1->numero < p2->numero) return -1;
                else return 1;
            }
        }
        else return -1;
    }
    if (p1->numero > p2->numero) return 1;
    if (p1->numero < p2->numero) return -1;
    else return 0;
}

ListElem SortMain2Table(ListElem mainList) {
    if (mainList == NULL) return NULL;
    s_Gun* gunList = (s_Gun*)mainList->data;  
    gunList->subList = MergeSort(gunList->subList, &Sort2Table);
    mainList->next = SortMain2Table(mainList->next);
    return mainList;
}

void ExportSublist(FILE* fp, s_Player* data) {
    if (data != NULL) {
        fprintf(fp, "Jogador numero: %d \t Nick: %s \t Pont: %d \t  %s \n",
            data->numero,
            data->nomeJogador,
            data->pontuacao,
            data->atribuda);
    }
}

void ExportMainList(FILE* fp, s_Gun* data) {
    if (data != NULL) {
        fprintf(fp, "Arma: %s \n", data->tipoArma);
        ExportListIterative(fp, data->subList, &ExportSublist);
        fprintf(fp, "\n\n");
    }
}

void ExportData(char* filename, ListElem main) {
    FILE* fp = fopen(filename, "w");
    if (main != NULL) {
        ExportListIterative(fp, main, &ExportMainList);
        fprintf(fp,"\n\n");
        fclose(fp);
    }
}
