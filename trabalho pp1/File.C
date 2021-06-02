#define _CRT_SECURE_NO_WARNINGS
#include "File.h"
#include "ll.h"
#include "Logica.h"
#include <ctype.h>


//Le um player do ficheiro e retorna nulo caso nao consiga ler todos os campos de um player
//consome o \n
player* ReadPlayer(FILE* file) {
    player* p = EmptyPlayer();
    if (fscanf(file, "%d %s %s %d %s %d %s %d %s %d %s %d",
                       &p->playerid,
                       &p->nickname,
                       &p->preferences[0].gun,
                       &p->preferences[0].score,
                       &p->preferences[1].gun,
                       &p->preferences[1].score,
                       &p->preferences[2].gun,
                       &p->preferences[2].score,
                       &p->preferences[3].gun,
                       &p->preferences[3].score,
                       &p->preferences[4].gun,
                       &p->preferences[4].score) != 12) {
        free(p);
        return NULL;  
    }
    fgetc(file); //para consumir o \n
    return p;
}

s_Gun* ReadGun(FILE* file) {
    s_Gun* aux = EmptyGun();
    if (fscanf(file, "%s %d", aux->tipoArma, &aux->qnt) != 2) {
        free(aux);
        return NULL;
    }
    fgetc(file);
    return aux;
}


ListElem ReadData(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file");
        return NULL;
    }
    ListElem list = NULL;
    while (!feof(fp)) {
        player* p = ReadPlayer(fp);
        if (p != NULL) {
            list = Snoc(list, p);
        }
        else {
            printf("Couldn't read player data. Player was NULL \n");
            return NULL;
        }
    }
    return list;
}

ListElem Readguns(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file");
        return NULL;
    }
    ListElem list = NULL;
    while (!feof(fp)) {
        s_Gun* aux = ReadGun(fp);
        if (aux != NULL) list = Snoc(list, aux);
        else {
            printf("Couldnt read gun data");
            return NULL;
        }
    }
    return list;
}






