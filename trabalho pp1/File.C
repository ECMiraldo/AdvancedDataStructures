#define _CRT_SECURE_NO_WARNINGS
#include "File.h"


void ReadData(char* filename, ListElem list) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) printf("Error opening file");
    else {
        playerPref* player = EmptyPref();
        while (fscanf(fp, "%d %s %s %d %s %d %s %d", &player->numero, &player->nomeJogador, &player->preferencias[0], &player->pontuacoes[0], &player->preferencias[1], &player->pontuacoes[1], &player->preferencias[2], &player->pontuacoes[2]) != EOF) {
            printf("%d" "%s" "%s" "%d" "%s" "%d" "%s" "%d", player->numero, player->nomeJogador, &player->preferencias[0], &player->pontuacoes[0], &player->preferencias[1], &player->pontuacoes[1], &player->preferencias[2], &player->pontuacoes[2]);
            if (fgetc(fp) == '\n') {
                list = addItemLastIterative(list, (playerPref*)player);
            }
        }
    }
    fclose(fp);
}