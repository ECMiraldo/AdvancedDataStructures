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
    if (mainList == NULL) return;
    ListElem nomes = NULL;
    ListElem armasatribuidas = NULL;
    char* guns[5];
    for (int i = 0; i < 5; i++) {
        guns[i] = "Sem Arma";
    }
    ListElem head = mainList;
    while (head != NULL) {
        s_Gun* gunList = (s_Gun*)head->data;
        ListElem sublist = gunList->subList;
        s_Player* aux = (s_Player*)gunList->subList->data; //primeiro nodo da sub-lista
        //Se o primeiro nodo esta sem arma, uma vez que a lista ja se encontra ordenada, entao atribuimos
        if (strcmp(guns[aux->numero - 1], "Sem Arma") == 0) {
            guns[aux->numero - 1] = gunList->tipoArma;
            armasatribuidas = Cons(gunList->tipoArma, armasatribuidas);
        }
        sublist = sublist->next;
        //Depois verificamos se existe empate
        while (sublist != NULL) {
            s_Player* playerData = (s_Player*)sublist->data;
            if (aux->pref == playerData->pref && aux->pontuacao == playerData->pontuacao) {
                if (strcmp(guns[playerData->numero - 1], "Sem Arma") == 0) {
                    guns[playerData->numero - 1] = strcat(gunList->tipoArma, " (Empate)");
                }
            }
            else break;
            sublist = sublist->next;
        }
        head = head->next;
    }
    head = mainList;
    while (head != NULL) {
        s_Gun* gunList = (s_Gun*)head->data;
        ListElem subList = gunList->subList;

        //Encontra qual arma que nao está atribuida
        if (ContainsRec(armasatribuidas, gunList->tipoArma) == 0) {
            //Dentro da sublista verifica se existe algum jogador sem arma e atribui a ele
            while (subList != NULL) {
                s_Player* playerData = (s_Player*)subList->data;
                if (strcmp(guns[playerData->numero - 1], "Sem Arma") == 0) {
                    guns[playerData->numero - 1] = gunList->tipoArma;
                    armasatribuidas = Cons(gunList->tipoArma, armasatribuidas);
                }
                if (subList->next != NULL) {
                    s_Player* nextplayerData = (s_Player*)subList->next->data;
                    if (nextplayerData->pref == playerData->pref && nextplayerData->pontuacao == playerData->pontuacao) {
                        if (strcmp(guns[nextplayerData->numero - 1], "Sem Arma") == 0) {
                            guns[nextplayerData->numero - 1] = strcat(gunList->tipoArma, "Empate");
                        }
                    }
                }
                subList = subList->next;
            }
        }
        head = head->next;
    }
    head = mainList;
    while (head != NULL) {
        s_Gun* gunList = (s_Gun*)head->data;
        ListElem sublist = gunList->subList;
        while (sublist != NULL) {
            s_Player* aux = (s_Player*)sublist->data;
            aux->atribuda = guns[aux->numero - 1];
            sublist = sublist->next;
        }
        head = head->next;
    }

}



       

//Alinea 3

int Sort2Table(s_Gun* gunList) {
    if (gunList == NULL) return 1;
    if (gunList->subList == NULL) return 1;
    if (gunList->subList->next == NULL) return 1;
    s_Player* p1 = (s_Player*)gunList->subList->data;
    s_Player* p2 = (s_Player*)gunList->subList->next->data;

    if (strcmp(p1->atribuda, gunList->tipoArma) != 0 && strcmp(p2->atribuda, gunList->tipoArma) == 0) return -1;
    if (strcmp(p1->atribuda, gunList->tipoArma) == 0 && strcmp(p2->atribuda, gunList->tipoArma) != 0) return 1;
    if (strcmp(p1->atribuda, gunList->tipoArma) != 0 && strcmp(p2->atribuda, gunList->tipoArma) != 0) {
        if (p1->pontuacao > p2->pontuacao) return -1;
        if (p1->pontuacao < p2->pontuacao) return 1;
    }
    if (strcmp(p1->atribuda, gunList->tipoArma) == 0 && strcmp(p2->atribuda, gunList->tipoArma) == 0) {
        if (p1->numero > p2->numero) return 1;
        if (p1->numero < p2->numero) return -1;
    }
}

ListElem SortMain2Table(ListElem mainList) {
    if (mainList == NULL) return NULL;
    s_Gun* gunList = (s_Gun*)mainList->data;
    gunList = MergeSort(gunList, &Sort2Table);
    mainList->next = SortMain2Table(mainList->next);
    return mainList;
}

void ExportTable(ListElem mainlist) {
    if (mainlist == NULL) return NULL;
    else {
        s_Gun* MainListData = (s_Gun*)mainlist->data;
        ListElem sublist = MainListData->subList;
        s_Player* SubListData = (s_Player*)sublist->data;



    }
}