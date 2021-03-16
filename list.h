#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

struct {
    int year;
    int month;
    int day;
} Date;

//Tipo que representa cada task;
struct {
    char* name;   // "NULL" se não definido
    int id;       // -1 se não definido
    int priority; // -1 se não definido
    char* owner;  // "NULL" se não definido
    Date dStart;  //(0,0,0) se não definida
    Date dEnd;    //(0,0,0) se não definida
}Task;

struct LDone {
    Task tname;
    struct LDone* next;
};

#endif // LIST_H_INCLUDED
