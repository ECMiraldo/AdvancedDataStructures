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

//Alinea 2
//Construtor para uma struct s_Player
s_Player* SubListCons(int n, char* nickname, int pref, int pont) {
    s_Player* aux = (s_Player*)malloc(sizeof(s_Player));
    aux->numero = n;
    aux->pontuacao = pont;
    aux->pref = pref;
    aux->nomeJogador = nickname;
    aux->atribuda = "Sem Arma";
    return aux;
}
//Construtor para um nodo da lista principal
s_Gun* GunCons(char* gun, int numero, char* nick, int pref, int pont) {
    s_Gun* aux = (s_Gun*)malloc(sizeof(s_Gun));
    aux->tipoArma = gun;
    aux->subList = Snoc(NULL, SubListCons(numero, nick, pref, pont));
    return aux;
}
//Rodar pela lista procurando uma arma com o mesmo nome gun,
//Se tiver insere todos os dados na sub-lista dessa arma
//Se nao encontrar, cria uma sub-lista nova com todos esses dados
ListElem InsereArma(ListElem mainList, char* gun, int numero, char* nick, int pref, int pont) {
    if (mainList == NULL) return Cons(GunCons(gun, numero, nick, pref, pont), NULL);
    else {
        s_Gun* gunl = mainList->data;
        /*if (strcmp(gun, "-") == 0 || strcmp(gun,"N/A") == 0) return NULL;*/
        if (strcmp(gunl->tipoArma, gun) == 0) {
            gunl->subList = Snoc(gunl->subList, SubListCons(numero, nick, pref, pont));
            return mainList;
        }
        else {
            mainList->next = InsereArma(mainList->next, gun, numero, nick, pref, pont);
            return mainList;
        }
    }
}

ListElem InserirTudo(ListElem playerlist, ListElem mainList) {
    if (playerlist != NULL) {
        player* data = playerlist->data;
        for (int i = 0; i < 5; i++) {
           mainList = InsereArma(mainList,
                        data->preferences[i].gun,
                        data->playerid,
                        data->nickname,
                        i,
                        data->preferences[i].score);
        }
        InserirTudo(playerlist->next, mainList);
    }
    else return Filter(mainList, &FilterGuns);  
}

void ShowSubList(s_Player* data) {
    if (data != NULL) {
        printf("Jogador numero: %d \t Nick: %s \t Pont: %d \t %s \n",
            data->numero,
            data->nomeJogador,
            data->pontuacao,
            data->atribuda);
    }
}

void ShowGuns(s_Gun* data) {
    if (data != NULL) {
        printf("Arma: %s", data->tipoArma);
        printf("\n");
        showListIterative(data->subList, &ShowSubList);
    }
    printf("\n\n");
}

int FilterGuns(void* value) {
    s_Gun* data = (s_Gun*)value;
    char* a = "-";
    char* b = "N/A";
    if (strcmp(data->tipoArma, a) == 0 || strcmp(data->tipoArma, b) == 0) {
        FreeList(data->subList);
        return 1;
    }
    else return 0;
}

ListElem SortMainList(ListElem gunList) {
    if (gunList == NULL) return NULL;
    s_Gun* mainNode = (s_Gun*)gunList->data;
    mainNode->subList = MergeSort(mainNode->subList, &SortSubList);
    gunList->next = SortMainList(gunList->next);
    return gunList;
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

void Atribuir(ListElem mainList) {
    
    ListElem nomes = NULL;
    ListElem guns = NULL;
    int nArmas = 0;
    ListElem head = mainList;
    while (mainList != NULL) {
        s_Gun* gundata = (s_Gun*)mainList->data;
        ListElem subList = gundata->subList;
        s_Player* playerData = (s_Player*)subList->data;
        
        //checamos se ha empate
        ListElem aux = subList->next;
        s_Player* auxData = (s_Player*)aux->data;
        if (playerData->pref == auxData->pref && playerData->pontuacao == auxData->pontuacao) {
            if (ContainsRec(nomes, playerData->nomeJogador) == 0 
             && ContainsRec(guns, gundata->tipoArma) == 0) {

                playerData->atribuda = gundata->tipoArma;
                nomes = Cons(playerData->nomeJogador, nomes);
                guns  = Cons(gundata->tipoArma, guns);
            }
            if (ContainsRec(nomes, auxData->nomeJogador) == 0) {
                strcat(gundata->tipoArma, " Empate");

                auxData->atribuda = gundata->tipoArma ;
                nomes = Cons(playerData->nomeJogador, nomes);
                guns  = Cons(gundata->tipoArma, guns);
                nArmas++;;
            }
        }

        //Checamos se esse jogador que ja tem arm atribuida
        if (ContainsRec(nomes, playerData->nomeJogador) == 0
            && ContainsRec(guns, gundata->tipoArma) == 0) {
            playerData->atribuda = gundata->tipoArma;
            nomes = Cons(playerData->nomeJogador, nomes);
            guns  = Cons(gundata->tipoArma, guns);
        }

        nArmas++;
        mainList = mainList->next;
    } //end first while

    //verifica se existe alguma arma sem atribuicao
    if (ListLen(nomes) < nArmas) { 
        while (head != NULL)
        {
            s_Gun* gundata = (s_Gun*)head->data;
            ListElem subList = gundata->subList;
           
            //Encontra qual arma que nao est� atribuida
            if (ContainsRec(guns, gundata->tipoArma) == 0) {
                //Dentro da sublista verifica se existe algum jogador sem arma e atribui a ele
                while (subList != NULL) {
                    s_Player* playerData = (s_Player*)subList->data;
                    ListElem aux = subList->next;
                    
                    if (ContainsRec(nomes, playerData->nomeJogador) == 0) {
                        playerData->atribuda = gundata->tipoArma;
                      
                        nomes = Cons(playerData->nomeJogador, nomes);
                        guns  = Cons(gundata->tipoArma, guns);
                    }

                    //checamos se ha empate
                    if (aux != NULL) { //Se subList nao esta no ultimo nodo
                        s_Player* auxData = (s_Player*)aux->data;
                        if (playerData->pref == auxData->pref
                            && playerData->pontuacao == auxData->pontuacao) {
                            if (ContainsRec(nomes, auxData->nomeJogador) == 0) {

                                strcat(gundata->tipoArma, " Empate");
                                playerData->atribuda = gundata->tipoArma;
                                auxData->atribuda = gundata->tipoArma;
                                nomes = Cons(playerData->nomeJogador, nomes);
                                guns = Cons(gundata->tipoArma, guns);
                            }
                        }
                    }
                    subList = subList->next;
                } //end sub-list traverse
            } 
            head = head->next;
        } //end second while
    }
    FreeList(nomes);
    FreeList(guns);
}

//Alinea 3

int Sort2Table(void* player1, void* player2) {
    s_Player* p1 = (s_Player*)player1;
    s_Player* p2 = (s_Player*)player2;

    if (strcmp(p1->atribuda, "Sem Arma") != 0 && strcmp(p2->atribuda, "Sem Arma") == 0) return -1;
    if (strcmp(p1->atribuda, "Sem Arma") == 0 && strcmp(p2->atribuda, "Sem Arma") != 0) return 1;
    if (strcmp(p1->atribuda, "Sem Arma") != 0 && strcmp(p2->atribuda, "Sem Arma") != 0) {
        if (p1->pontuacao > p2->pontuacao) return -1;
        if (p1->pontuacao < p2->pontuacao) return 1;
    }
    if (strcmp(p1->atribuda, "Sem Arma") == 0 && strcmp(p2->atribuda, "Sem Arma") == 0) {
        if (p1->numero > p2->numero) return 1;
        if (p1->numero < p2->numero) return -1;
    }
}

ListElem SortMain2Table(ListElem mainList) {
    if (mainList == NULL) return NULL;
    s_Gun* gunList = (s_Gun*)mainList->data;
    gunList->subList = MergeSort(gunList->subList, &Sort2Table);
    mainList->next = SortMain2Table(mainList->next);
    return mainList;
}

void RemoveSemArma(ListElem mainList) {
    ListElem aux = NULL;
    ListElem head = mainList;
    while(mainList != NULL) {
        s_Gun* MainListData = (s_Gun*)mainList->data;
        ListElem sublist = MainListData->subList;
        while (sublist != NULL) {
            s_Player* subListData = (s_Player*)sublist->data;
            //Se o jogador ja possui uma arma atribuida, entao
            //Guardamos o numero desse jogador numa lista
            if (strcmp(subListData->atribuda, "Sem Arma") != 0) {
                aux = Cons(subListData->numero, aux);
            }
            sublist = sublist->next;
        }
        mainList = mainList->next;
    }
    //Agora iremos passar pelas listas outra vez e, atribuir a string " "
    //Para todos jogador contidos na lista aux
    while (head != NULL) {
        s_Gun* MainListData = (s_Gun*)head->data;
        ListElem sublist = MainListData->subList;
        while (sublist != NULL) {
            s_Player* subListData = (s_Player*)sublist->data;
            if (ContainsRec(aux, subListData->numero) == 1) {
                if (strcmp(MainListData->tipoArma, subListData->atribuda) != 0) subListData->atribuda = " ";
            }
            sublist = sublist->next;
        }
        head = head->next;
    }
    FreeList(aux);
}
void ExportTable(ListElem mainlist) {
    if (mainlist == NULL) return NULL;
    else {
        s_Gun* MainListData = (s_Gun*)mainlist->data;
        ListElem sublist = MainListData->subList;
        s_Player* SubListData = (s_Player*)sublist->data;



    }
}