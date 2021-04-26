#define _CRT_SECURE_NO_WARNINGS
#include "File.h"
#include "ll.h"
#include "Logica.h"

ListElem ReadData(char* filename) {
    FILE* fp = fopen(filename, "r");
    player* p = EmptyPlayer();
    ListElem list = List_Bin(p);
    if (fp == NULL) {
        printf("Error opening file");
        free(p);
        free(list);
    }


    else {
        
        while (fscanf(fp, "%d %s %s %d %s %d %s %d",&p->playerid, &p->nickname, &p->preferences[0].gun, &p->preferences[0].score,  &p->preferences[1].gun, &p->preferences[1].score, &p->preferences[2].gun, &p->preferences[2].score) != EOF) {
            if (ListLen(list) == 1) list = Cons(list, &p);
            else {
                list = Snoc(list, &p);
            }
            showListRecursive(list, &showPlayer);
            
        }
        
        fclose(fp);
    }
    
    return list;
}




