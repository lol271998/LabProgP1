#include "list.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

DATE dNULL() {
    DATE dNULL;
    dNULL.day = 0;
    dNULL.month = 0;
    dNULL.year = 0;

    return dNULL;
}

/**
*
* Quando passamos de tabela para tabela não esquecer de:
* - Atribuir dono (Doint)
* - Atribuir Data limite (Doing)
* - Atribuir data de conclusão (Done)
*
**/
TASK createTASK(DATE d, char* name, int id, int p) {
    /*
    *
    * Quando criamos uma tarefa só precisamos de:
    * - Data de criação
    * - nome da tarefa,
    * - id
    * - prioridade
    *
    */


    TASK t_info;
    t_info.name = name;
    t_info.id = id;
    t_info.priority = p;
    t_info.owner = NULL;
    t_info.dStart = d;
    t_info.deadLine = dNULL();
    t_info.dEnd = dNULL();

    return t_info;
}

LIST createList() {

    DATE d;
    d.day = 0;
    d.month = 0;
    d.year = 0;

    TASK t_head;
    t_head.name = NULL;
    t_head.id = -1;
    t_head.priority = -1;
    t_head.owner = NULL;
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
<<<<<<< HEAD

int compareToDo(TASK t1,TASK t2){
    return compareDate(t1.dStart,t2.dStart);
=======

int compareToDo(TASK t1,TASK t2){
    return compareDate(t1.dStart,t2.dStart);
>>>>>>> 8cdfe12a59ac96d4534b0076c35fc3ab10e2d017
}
/*
void DoneSearch(LISTA l, DATE d, LISTA *prev, LIST *cur) {
    *prev = l;
    *cur = l->next;

    while((*cur) != NULL && (*actual))
}
*/

//Ordenado por data de conclusão (task.dEnd)
void addDone (LIST l, TASK t) {

    LIST cur,prev;
    cur = l;
    prev = l;

    LIST node = (LIST) malloc (sizeof(List_node));
    node->task = t;

    if(cur->next == NULL) {
        node->next = NULL;
        cur->next = node;
    }

    else {
        cur = cur->next;
        while(cur != NULL) {
            if(compareToDone(cur->task,t)>=1) {
                prev->next = node;
                node->next = cur;
                return;
            }
            else {
                cur = cur->next;
                prev = prev->next;
            }
        }
        prev->next = node;
        node->next = NULL;
    }

}

void auxDoing(LIST lista,TASK t,LIST *ant,LIST *atual){
    *ant=lista;
    *atual=lista->next;
    while ((*atual) != NULL && (strcmp((*atual)->task.name,t.name)<0) ){
        *ant = *atual;
        *atual = (*atual)->next;
    }
}

//Ordenado por nome (task.name)
void addDoing(LIST l, TASK t){
    LIST node;
    LIST ant,inut;
    node = (LIST) malloc (sizeof(List_node));
    if(node!=NULL){
        node->task = t;
        auxDoing(l,t,&ant,&inut);
        node->next = ant->next;
        ant->next = node;
    }
}
<<<<<<< HEAD

void auxToDo(LIST lista, TASK t,LIST *ant,LIST *atual){
    *ant=lista;
    *atual=lista->next;
    while ((*atual) != NULL && ( (*atual)->task.priority>t.priority ) ){
        *ant = *atual;
        *atual = (*atual)->next;
    }
    while ((*atual) != NULL &&  (compareToDo((*atual)->task,t ))>=-1 ){
        *ant = *atual;
        *atual = (*atual)->next;
    }
=======

void auxToDo(LIST lista, TASK t,LIST *ant,LIST *atual){
    *ant=lista;
    *atual=lista->next;
    while ((*atual) != NULL && ( (*atual)->task.priority>t.priority ) ){
        *ant = *atual;
        *atual = (*atual)->next;
    }
    while ((*atual) != NULL &&  (compareToDo((*atual)->task,t ))>=-1 ){
        *ant = *atual;
        *atual = (*atual)->next;
    }
>>>>>>> 8cdfe12a59ac96d4534b0076c35fc3ab10e2d017
}
//Ordenado por prioridade e depois data de ciraçao (task.priority) (task.dStart)
void addToDo(LIST l, TASK t){
    LIST node;
    LIST ant,inut;
    node = (LIST) malloc (sizeof(List_node));
    if(node!=NULL){
        node->task = t;
        auxToDo(l,t,&ant,&inut);
        node->next = ant->next;
        ant->next = node;
    }
}

/**
*
*
* Dado um indice, procura uma tarefa
*
*/

TASK findTask(LIST l,int ind) {
    TASK tnull = createTASK(dNULL(),-1,-1,NULL);
    LIST temp = l;
    temp = temp->next;
    int i = 1;
    while(temp){
        if(i == temp) return temp->task;
        temp=temp->next;
        i++;
    }
    return tnull;
}

/**
*
* Remove uma tarefa de uma lista, se removida com sucesso devolve a tarefa pretendida
* Caso contrário devolve uma tarefa tnull com id = -1 (id inválido)
*
*/

void removeTask(LIST l, TASK t) {
    TASK tnull = createTASK(dNULL(),-1,-1,NULL);
    LIST cur, prev;
    cur = l;
    prev = l;

    cur = cur->next;
    if(cur->task.id == t.id) {
        prev->next = cur->next;
        //printf("removedFirst\n");
        return t;
    }

    prev = prev->next;
    cur = cur->next;

    while(cur->next != NULL) {
        if(cur->task.id == t.id) {
            prev->next = cur->next;
            /*
            printf("\nprev: %s\n\n",prev->task.name);
            printf("\ncur: %s\n\n",cur->task.name);
            */
            return;
        }
        else {
            /*
            printf("\nprev: %s\n\n",prev->task.name);
            printf("\ncur: %s\n\n",cur->task.name);
            */
            prev = prev->next;
            cur = cur->next;
        }
    }

    //printf("\nprev: %s\n\n",prev->task.name);

    if(cur->task.id == t.id) {
        prev->next = cur->next;
        return;
    }
    else {
        //Não existe
        return;
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

void printToDo(LIST l) {

    LIST temp = l;
    temp = temp->next;
    int i = 1;
    while(temp) {
        printf("\n \n");
        printf("%d. Nome: %s\n",i,temp->task.name);
        printf("   id: %d\n",temp->task.id);
        printf("   prioridade: %d\n",temp->task.priority);
        printf("\n \n");
        i++;
        temp = temp->next;
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

