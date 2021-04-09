#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct date DATE;
struct date {
    int year;
    int month;
    int day;
};

typedef struct task TASK;
struct task {

    char name [40]; // NULL se não definido
    int id;         // -1 se não definido
    int priority;   // -1 se não definido
    char owner[40];    // NULL se não definido
    DATE dStart;    // (0,0,0) se não definida
    DATE deadLine;  // (0,0,0) se não definida
    DATE dEnd;      // (0,0,0) se não definida

};

typedef struct list *LIST;
struct list{
    TASK task;
    LIST next;
}List_node;

int size(LIST l); //Devolve o tamanho da lista //Done
TASK createTASK(DATE d, char name[], int id, int p); //Done

LIST createList(); //Done
DATE dateNULL();
/**
*
* Funções do main
*
*/
void addToDoInterface(); //Data de sistema
void toDo2Doing();
void Doing2Done();

int compareDate(DATE d1, DATE d2);
int compareToDone(TASK t1, TASK t2);
int compareToDo(TASK t1,TASK t2);

void addToDo(LIST l, TASK t); //Done
void addDoing(LIST l, TASK t);//Done
void addDone(LIST l, TASK t); //Done

void printToDo(LIST l); //Done
void printDoing(LIST l);//Done
void printDone();//Done

void removeTask(LIST l, TASK t);
TASK findTask(LIST l, int ind);

void printTable();
void printIndTask(char* name);
void printAllTask();

void printDate(DATE d);

void auxAddByDate(LIST lista,TASK t,LIST *ant,LIST *atual);
void addByDate(LIST l,TASK t);
int ownsTask(LIST l,char * owne);
void pTasksAll(LIST l1,LIST l2,LIST l3,char * owne);
void pTasks(LIST l,char * owne);
void dispList(LIST l1);

#endif // LIST_H_INCLUDED


