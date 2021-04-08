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
* - Atribuir dono (Doing)
* - Atribuir Data limite (Doing)
* - Atribuir Data limite (Doing)
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
    strcpy(t_info.name,name);
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
    t_head.name[0] = '\0';
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

int compareToDo(TASK t1,TASK t2){
    return compareDate(t1.dStart,t2.dStart);
}



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

/**
*
*
* Dado um indice, procura uma tarefa
*
*/

TASK findTask(LIST l, int ind) {
    TASK tnull = createTASK(dNULL(),"",-1,-1);
    LIST temp = l;
    temp = temp->next;
    int i = 1;
    while(temp){
        if(i == ind) return temp->task;
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
    LIST cur, prev;
    cur = l;
    prev = l;

    cur = cur->next;
    if(cur->task.id == t.id) {
        prev->next = cur->next;
        return;
    }

    prev = prev->next;
    cur = cur->next;

    while(cur->next != NULL) {
        if(cur->task.id == t.id) {
            prev->next = cur->next;
            return;
        }
        else {
            prev = prev->next;
            cur = cur->next;
        }
    }

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

void printDate(DATE d) {
    if(d.day == -1 && d.month == -1 && d.year == -1) printf("N/A");
    printf("%d/%d/%d",d.day,d.month,d.year);
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
        printf("   Data de inicio: "); printDate(temp->task.dStart);
        printf("\n \n");
        i++;
        temp = temp->next;
    }


}

void printDoing(LIST l){
    LIST temp = l;
    temp = temp->next;
    int i = 1;
    while(temp) {
        printf("\n \n");
        printf("%d. Nome: %s\n",i,temp->task.name);
        printf("   id: %d\n",temp->task.id);
        printf("   prioridade: %d\n",temp->task.priority);
        printf("   Dono: %s\n",temp->task.owner);
        printf("   Data de inicio: "); printDate(temp->task.dStart);
        printf("   Data limite: "); printDate(temp->task.deadLine);
        printf("\n \n");
        i++;
        temp = temp->next;
    }
}

void printDone(LIST l){
    LIST temp = l;
    temp = temp->next;
    int i = 1;
    while(temp) {
        printf("\n \n");
        printf("%d. Nome: %s\n",i,temp->task.name);
        printf("   id: %d\n",temp->task.id);
        printf("   prioridade: %d\n",temp->task.priority);
        printf("   Dono: %s\n",temp->task.owner);
        printf("   Data de inicio: "); printDate(temp->task.dStart);
        printf("   Data limite: "); printDate(temp->task.deadLine);
        printf("   Data de conclusão: "); printDate(temp->task.dEnd);
        printf("\n \n");
        i++;
        temp = temp->next;
    }
}

void dispLists(LIST l1,LIST l2,LIST l3){
    LIST temp1 = l1;
    LIST temp2 = l2;
    LIST temp3 = l3;
    temp1=temp1->next;
    temp2=temp2->next;
    temp3=temp3->next;
    while(temp1 || temp2 || temp3){
        printf(" %s\n",temp1->task.name);
        temp1=temp1->next;
        temp2=temp2->next;
        temp3=temp3->next;
    }
}
