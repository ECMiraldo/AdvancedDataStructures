#define _CRT_SECURE_NO_WARNINGS
#include "File.h"


void ReadData(char* filename, ListElem list) {
    FILE* fp = fopen(filename, "r");
    char* xar;
    if (fp == NULL) printf("Error opening file");
    else {
        playerPref* playerlist = NULL;
        list->data = playerlist;
        while (fscanf(fp, "%d" "%s" "%s" "%d" "%s" "%d" "%s" "%d", playerlist->numero, playerlist->nomeJogador, playerlist->preferencias[0], playerlist->pontuacoes[0], playerlist->preferencias[1], playerlist->pontuacoes[1], playerlist->preferencias[2], playerlist->pontuacoes[2]) != EOF) {
            printf("%d" "%s" "%s" "%d" "%s" "%d" "%s" "%d", playerlist->numero, playerlist->nomeJogador, playerlist->preferencias[0], playerlist->pontuacoes[0], playerlist->preferencias[1], playerlist->pontuacoes[1], playerlist->preferencias[2], playerlist->pontuacoes[2]);
            if (fgetc(fp) == '\n') {
                list = addItemLastIterative(list, (playerPref*)playerlist);
            }
        }
    }
    fclose(fp);
}