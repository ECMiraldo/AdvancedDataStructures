#define _CRT_SECURE_NO_WARNINGS
#include "File.h"


ListElem ReadData(char* filename, ListElem list) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) printf("Error opening file");


    else {
        player* p = EmptyPlayer();

        while (fscanf(fp, "%d %s %s %d %s %d %s %d",&p->playerid, &p->nickname, &p->preferences[0].gun, &p->preferences[0].score,  &p->preferences[1].gun, &p->preferences[1].score, &p->preferences[2].gun, &p->preferences[2].score) != EOF) {
            list = addItemLastIterative(list, (player*)p);
            showListRecursive(list, &showPlayer);
            
        }
        
        fclose(fp);
    }
    
    return list;
}




