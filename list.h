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

    char* name;    // "NULL" se não definido
    int id;        // -1 se não definido
    int priority;  // -1 se não definido
    char* owner;   // "NULL" se não definido
    DATE dStart;   //(0,0,0) se não definida
    DATE deadLine; //(0,0,0) se não definida
    DATE dEnd;     //(0,0,0) se não definida

};


typedef struct list *LIST;

struct list{
    TASK task;
    LIST next;
}List_node;

int size(LIST l); //Devolve o tamanho da lista
TASK createTASK(int day, int month, int year, char* name, int id, int p, char* owner);

LIST createToDo();
void addToDo(LIST l, TASK t); //Data de sistema

void createDoing();
void toDo2Doing(LIST l, TASK t);

LIST createDone();
void Doing2Done(LIST l, TASK t);
void Done2ToDo(LIST l, TASK t);
void printDone();

void printTable();
void printIndTask(char* name);
void printAllTask();



#endif // LIST_H_INCLUDED


