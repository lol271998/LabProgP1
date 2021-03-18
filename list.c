#include "list.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TASK createTASK(int day, int month, int year, char* name, int id, int p, char* owner) {

    DATE d;
    d.day = day;
    d.month = month;
    d.year = year;

    TASK t_info;
    t_info.name = name;
    t_info.id = id;
    t_info.priority = p;
    t_info.owner = owner;
    t_info.dStart = d;
    t_info.deadLine = d;
    t_info.dEnd = d;

    return t_info;
}

LIST createList() {

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
        l->task = t_head;
        l->next = NULL;
    }

    return l;
}

int size(LIST l) {
    LIST temp = l;
    if(temp->next == NULL) return 0;

    int count = 1;
    temp = temp->next;
    while(temp->next != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

/**
*
* Devolve 1 se d1 > d2, -1 se d1 < d2, 0 se d1 = d2
*
*/
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

/*
void DoneSearch(LISTA l, DATE d, LISTA *prev, LIST *cur) {
    *prev = l;
    *cur = l->next;

    while((*cur) != NULL && (*actual))
}
*/

//Ordenado por data de conclusão (task.dEnd)
void Doing2Done(LIST l, TASK t) {

    LIST cur,prev;
    cur = l;
    prev = l;

    LIST node = (LIST) malloc (sizeof(List_node));
    node->task = t;

    if(cur -> next == NULL) {
        node->next = NULL;
        cur -> next = node;
    }

    else {
        cur = cur->next;
        while(cur != NULL) {
            if(compareToDone(cur->task,t)>=1) {
                prev -> next = node;
                node -> next = cur;
                return;
            }
            else {
                cur = cur->next;
                prev = prev->next;
            }
        }
        prev -> next = node;
        node -> next = NULL;
    }

}

void auxToDo2Doing(LIST lista,TASK t,LIST *ant,LIST *atual){
    *ant=lista;
    *atual=lista->next;
    while ((*atual) != NULL && (strcmp((*atual)->task.name,t.name)<0) ){
        *ant = *atual;
        *atual = (*atual)->next;
    }
}

//Ordenado por nome (task.name)
void toDo2Doing(LIST l, TASK t){
    LIST node;
    LIST ant,inut;
    node = (LIST) malloc (sizeof(List_node));
    if(node!=NULL){
        node->task = t;
        auxToDo2Doing(l,t,&ant,&inut);
        node->next = ant->next;
        ant->next = node;
    }
}
//Ordenado por prioridade e depois data de ciraçao (task.priority) (task.dStart)
void Done2ToDo(LIST l, TASK t){
    LIST node;
    LIST ant,inut;
    node = (LIST) malloc (sizeof(List_node));
    if(node!=NULL){
        node->task = t;
        auxToDo2Doing(l,t,&ant,&inut);
        node->next = ant->next;
        ant->next = node;
    }
}


/**
*
* Just for testing purposes
*
*/
void printDone(LIST l) {
    LIST temp = l;
    temp = temp->next;
    while(temp) {
        printDate(temp->task.dEnd);
        printf("\n");
        temp=temp->next;
    }
}

void printDate(DATE d) {
    printf("%d/%d/%d",d.day,d.month,d.year);
}

void printDoing(LIST l){
     LIST temp = l;
    temp = temp->next;
    while(temp){
        printf("%s\n",temp->task.name);
        temp=temp->next;
    }
}

