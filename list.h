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


typedef struct ldone LDONE;

struct ldone {
    TASK t;
    struct ldone* next;
};

void addToDo(TASK t);
void toDo2Doing(TASK t);
void Doing2Done(TASK t);
void Done2ToDo(TASK t);
void printTable();
void printIndTask(char* name);
void printAllTask();



#endif // LIST_H_INCLUDED


