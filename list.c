#include "list.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
/*

LIST createDone() {

    DATE d;
    d.day = 0;
    d.month = 0;
    d.year = 0;

    TASK t_head;
    t_head.name = "NULL";
    t_head.id = -1;
    t_head.priority = -1;
    t_head.owner = "NULL";
    t_head.dStart = d;
    t_head.deadLine = d;
    t_head.dEnd = d;

    LIST l;

    l = (LIST) malloc (sizeof (List_node));

    if(l != NULL) {
        l->t = t_head;
        l->next = NULL;
    }

    return l;
}

/**
*
* Devolve 1 se d1 > d2, -1 se d1 < d2, 0 se d1 = d2
*

int compareDate(DATE d1, DATE d2) {

    if(d1.year>d2.year) return 1;
    if(d1.year<d2.year) return -1;

    else {
        if(d1.month>d2.month) return 1;
        if(d1.month<d2.month) return -1;

        else {
            if(d1.day>d2.day) return 1;
            if(d1.day<d2.day) return -1;
            else return 0;
        }
    }
}

int compareToDone(TASK t1, TASK t2) {
    return compareDate(t1.dEnd,t2.dEnd);
}

void Doing2Done(TASK t) {

    LIST node;

    node = (LIST) malloc (sizeof(List_node));

    while (node != NULL) {
        if(compareToDone(node->t,t)>=0) {
            //Inserir antes
        }
        else; //Inserir depois
    }
}
/**
*
* Just for testing purposes
*
*
void printDone(LIST l) {
    while(l) {
        printf("%d ", l->t.id);
        l=l->next;
    }
}
*/
