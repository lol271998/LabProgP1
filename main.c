#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "getline.h"
#include "list.h"
#define _GNU_SOURCE

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
#define sep "*_*"
#define MAX_BUFFER_SIZE 1024

void systemclear();
bool file_exit(const char* filename);
void existing_table();

void new_table(char* fname);
void print_help();
void menu();
void func();

LIST lToDo,lDoing,lDone;
TASK temp;
int id,isNew;
//Default is temp->txt
char* fname;

void systemclear() {
	system(CLEAR);
	printf("Quadro de KanBan\n\n");
}


bool file_exist(const char * filename){
    /* try to open file to read */
    FILE *file;
    if ((file = fopen(filename, "r"))){
        fclose(file);
        return true;
    }
    return false;
}

/*
* Saves content in file
*/
void save(char* user_fname) {

    if(strcmp(user_fname,"temp.txt") != 0){
        fname = malloc(sizeof(char)*strlen(user_fname));
        strcpy(fname,user_fname);
        strcat(fname,".txt");
    }

    FILE *fp = fopen(fname,"w+");
    if (fp == NULL) {
        perror("fopen()");
        exit(1);
    }
    LIST temp;

    //guardar os conteudos de lToDo
    fprintf(fp,"%d\n", size(lToDo));
    if(size(lToDo) >= 1) {
        temp = lToDo;
        temp = temp->next;
        while(temp){
            fprintf(fp,"%s%s%d%s%d\n",temp->task.name,sep,temp->task.id,sep,temp->task.priority);
            fprintf(fp,"%d %d %d\n",temp->task.dStart.day,temp->task.dStart.month,temp->task.dStart.year);
            temp = temp->next;
        }
    }
    //guardar os conteudos de lDoing
    fprintf(fp,"%d\n", size(lDoing));
    if(size(lDoing) >= 1){
        temp = lDoing;
        temp = temp->next;
        while(temp){
            fprintf(fp,"%s%s%s%s%d%s%d\n",temp->task.name,sep,temp->task.owner,sep,temp->task.id,sep,temp->task.priority);
            fprintf(fp,"%d %d %d\n",temp->task.dStart.day,temp->task.dStart.month,temp->task.dStart.year);
            fprintf(fp,"%d %d %d\n",temp->task.deadLine.day,temp->task.deadLine.month,temp->task.deadLine.year);
            temp = temp->next;
        }
    }

    //guardar o conteudo de lDone
    fprintf(fp,"%d\n", size(lDone));
    if(size(lDone) >= 1) {
        temp = lDone;
        temp = temp->next;
        while(temp){
            fprintf(fp,"%s%s%s%s%d%s%d\n",temp->task.name,sep,temp->task.owner,sep,temp->task.id,sep,temp->task.priority);
            fprintf(fp,"%d %d %d\n",temp->task.dStart.day,temp->task.dStart.month,temp->task.dStart.year);
            fprintf(fp,"%d %d %d\n",temp->task.deadLine.day,temp->task.deadLine.month,temp->task.deadLine.year);
            fprintf(fp,"%d %d %d\n",temp->task.dEnd.day,temp->task.dEnd.month,temp->task.dEnd.year);
            temp = temp->next;
        }
    }
    free(temp);
    fclose(fp);
}

/*
* Função para sair do projecto
*/
void user_exit() {
    systemclear();
    char* sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);

    printf("+------------------------------------------+\n");
	printf("| Quer guardar o ficheiro ?                |\n");
	printf("| s para sim, n para não                   |\n");
    printf("+------------------------------------------+\n");

    while(1) {
        scanf(" %s",sel);

        if(strlen(sel) > 1){
            printf("Introduza apenas um caracter \n\n");
            continue;
        }

<<<<<<< HEAD
        else if(sel[0] == 's'){
            free(sel);
            char *user_fname = malloc(sizeof(char)*MAX_BUFFER_SIZE);
            printf("+------------------------------------------+\n");
            printf("| Introduza o nome do ficheiro             |\n");
            printf("+------------------------------------------+\n");

            scanf(" %s",user_fname);
            save(user_fname);
            printToDo(lToDo);
            printDoing(lDoing);
            printDone(lDone);
            free(lToDo);
            free(lDoing);
            free(lDone);
            exit(0);
=======
        strtok(sel, "\n");
        systemclear();

        if(strlen(sel) == 1) {
            switch(sel[0]){
                case 's':
                    free(sel);
                    char *user_fname = malloc(sizeof(char)*MAX_BUFFER_SIZE);
                    printf("+------------------------------------------+\n");
                    printf("| Introduza o nome do ficheiro             |\n");
                    printf("| Sem extensão                             |\n");
                    printf("+------------------------------------------+\n");

                    scanf(" %s",user_fname);
                    save(user_fname);
                    free(lToDo);
                    free(lDoing);
                    free(lDone);
                    exit(0);
					break;
				case 'n':
                    free(sel);
                    remove(fname);
                    free(lToDo);
                    free(lDoing);
                    free(lDone);
                    exit(0);
					break;
				default:
					printf("Error: Escolha uma opção válida\n\n");
            }
>>>>>>> e2212507a2176d28dd08335a94f5f7015a27c5b3
        }
        else {
            free(sel);
            remove(fname);
            printToDo(lToDo);
            printDoing(lDoing);
            printDone(lDone);
            free(lToDo);
            free(lDoing);
            free(lDone);
            exit(0);
        }
    }
}

/*
* Abre um ficheiro existente para leitura de dados - Não guarda os nomes
*/
void existing_table() {

	int error = 2;

	fname = malloc(sizeof(char)*MAX_BUFFER_SIZE);

	while (error == 2) {

		printf("+-----------------------------------------+\n");
		printf("| Introduza o nome do ficheiro:           |\n");
		printf("+-----------------------------------------+\n");

		fgets(fname,MAX_BUFFER_SIZE,stdin);

        if(fname[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(fname, "\n");
        systemclear();

		if(file_exist(fname)) {
            FILE * file = fopen(fname,"r");
            while (1) {

                char* line = malloc(sizeof(char)*MAX_BUFFER_SIZE);
                size_t buffsize = MAX_BUFFER_SIZE;
                getline(&line,&buffsize,file);
                int n = atoi(line);
                //AddToDo
                for(int i = 0; i<n; i++) {
                    getline(&line,&buffsize,file);
                    char linearray[strlen(line)];

                    strcpy(linearray,line);
                    strcpy(temp.name,strtok(linearray,sep));

                    temp.id= atoi(strtok(NULL,sep));
                    temp.priority = atoi(strtok(NULL,sep));

                    getline(&line,&buffsize,file);
                    char date[strlen(line)];
                    strcpy(date,line);

                    temp.dStart.day = atoi(strtok(date," "));
                    temp.dStart.month = atoi(strtok(NULL," "));
                    temp.dStart.year = atoi(strtok(NULL," "));

                    addToDo(lToDo,temp);
                }

                //AddDoing
                getline(&line,&buffsize,file);
                n = atoi(line);

                for(int i = 0; i<n; i++) {
                    getline(&line,&buffsize,file);
                    char linearray[strlen(line)];

                    strcpy(linearray,line);

                    strcpy(temp.name,strtok(linearray,sep));
                    strcpy(temp.owner,strtok(NULL,sep));
                    temp.id = atoi(strtok(NULL,sep));
                    temp.priority = atoi(strtok(NULL,sep));

                    getline(&line,&buffsize,file);
                    char date[strlen(line)];
                    strcpy(date,line);

                    temp.dStart.day = atoi(strtok(date," "));
                    temp.dStart.month = atoi(strtok(NULL," "));
                    temp.dStart.year = atoi(strtok(NULL," "));

                    getline(&line,&buffsize,file);
                    date[strlen(line)]; //O tamanho da line pode mudar
                    strcpy(date,line);

                    temp.deadLine.day = atoi(strtok(date," "));
                    temp.deadLine.month = atoi(strtok(NULL," "));
                    temp.deadLine.year = atoi(strtok(NULL," "));

                    addDoing(lDoing,temp);
                }

                getline(&line,&buffsize,file);
                n = atoi(line);

                for(int i = 0; i<n; i++) {
                    getline(&line,&buffsize,file);
                    char linearray[strlen(line)];

                    strcpy(linearray,line);

                    strcpy(temp.name,strtok(linearray,sep));
                    strcpy(temp.owner,strtok(NULL,sep));
                    temp.id= atoi(strtok(NULL,sep));
                    temp.priority = atoi(strtok(NULL,sep));

                    getline(&line,&buffsize,file);
                    char date[strlen(line)];
                    strcpy(date,line);

                    temp.dStart.day = atoi(strtok(date," "));
                    temp.dStart.month = atoi(strtok(NULL," "));
                    temp.dStart.year = atoi(strtok(NULL," "));

                    getline(&line,&buffsize,file);
                    date[strlen(line)]; //O tamanho da line pode mudar
                    strcpy(date,line);

                    temp.deadLine.day = atoi(strtok(date," "));
                    temp.deadLine.month = atoi(strtok(NULL," "));
                    temp.deadLine.year = atoi(strtok(NULL," "));

                    getline(&line,&buffsize,file);
                    date[strlen(line)]; //O tamanho da line pode mudar
                    strcpy(date,line);

                    temp.dEnd.day = atoi(strtok(date," "));
                    temp.dEnd.month = atoi(strtok(NULL," "));
                    temp.dEnd.year = atoi(strtok(NULL," "));


                    addDone(lDone,temp);
                }
                free(line);
                break;
            }
            fclose(file);
            break;
		}
		else {
			printf("+--------------------------------------------------------------+\n");
			printf("| Ficheiro não existe.                                         |\n");
			printf("| Verifique se escreveu o nome sem erros.                      |\n");
			printf("| Quer criar um novo ficheiro com esse nome ?                  |\n");
			printf("| s para sim, n para reescrever o nome do ficheiro.            |\n");
			printf("+--------------------------------------------------------------+\n");

			while(error != 0) {
                char* sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);
				scanf(" %s",sel);

				//systemclear();

				if(strlen(sel) > 1) printf("Introduza apenas um caracter\n\n");
				else{
					switch(sel[0]) {
						case 's': case 'S':
                            save(fname);
                            func();
							error = 0;
							break;
						case 'n': case 'N':
							error = 2;
							break;
						case 'h': case 'H':
							print_help();
							error = 1;
							break;
						case 'q': case 'Q':
							return;
							break;
						default:
							printf("Error: Escolha uma opção válida\n\n");
					}
				}
				if(error == 2) break;
				free(sel);
				systemclear();
			}
		}
	}
}

/*
* Texto de ajuda, como funciona o programa, como deve ser o input dos ficheiros.
* Quando ativado volta ao menu incial.
*/
void print_help() {
	systemclear();
	printf("help\n");
    menu();
}

/*
* Menu inicial
*/
void menu() {

	while(1) {

		printf("+--------------------------------------------------------------+\n");
		printf("| 1. Criar um novo quadro                                      |\n");
		printf("| 2. Usar um quadro exisistente                                |\n");
		printf("| h for help, q for quit                                       |\n");
		printf("+--------------------------------------------------------------+\n");

        char* sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);
		fgets(sel,MAX_BUFFER_SIZE,stdin);

        if(sel[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(sel, "\n");
        systemclear();

        if(strlen(sel) == 1) {
            switch(sel[0]){
                case '1':
                    free(sel);
                    fname = "temp.txt";
					func();
					break;
				case '2':
                    free(sel);
					existing_table();
					func();
					break;
                case 'q':
                    free(sel);
                    user_exit();
                    break;
				default:
					printf("Error: Escolha uma opção válida\n\n");
            }
        }
        else if(strcmp("prev",sel)==0) {
            free(sel);
            systemclear();
            menu();
        }

		else if(strlen(sel) > 1){
            printf("+--------------------------------------------------------------+\n");
            printf("| Introduza apenas um caracter                                 |\n");
            printf("+--------------------------------------------------------------+\n");
            free(sel);
            continue;
        }
		else{
			switch(sel[0]) {
				case '1':
                    free(sel);
                    fname = "temp.txt";
					func();
					break;
				case '2':
                    free(sel);
					existing_table();
					func();
					break;
				default:
					printf("Error: Escolha uma opção válida\n\n");
			}
		}
	}
	return;
}

/*
* Adiciona tarefas à lista toDo (check)
*/
void addToDoInterface() {

    int count = 0;
    while(1) {
        if(count == 0) systemclear();

        char* tname = malloc(sizeof(char)*MAX_BUFFER_SIZE);

        printf("+------------------------------------+\n");
        printf("| Introduza o nome da tarefa         |\n");
        printf("| prev para voltar atrás             |\n");
        printf("| q para sair                        |\n");
        printf("| h para ajuda                       |\n");
        printf("+------------------------------------+\n");

        fgets(tname,MAX_BUFFER_SIZE,stdin);

        if(tname[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(tname, "\n");
        systemclear();

        if(strlen(tname) == 1 && tname[0] == 'q') {
            free(tname);
            user_exit();
        }
        else if(strcmp("prev",tname)==0) {
            free(tname);
            systemclear();
            return;
        }
        else {
            int p = -1;
            time_t s;
            struct tm* current_time;
            s = time(NULL);
            current_time = localtime(&s);
            systemclear();

            while(1) {
                printf("+------------------------------------+\n");
                printf("| Introduza a prioridade             |\n");
                printf("+------------------------------------+\n");

                char* in  = malloc(sizeof(char)*MAX_BUFFER_SIZE);
                fgets(in,MAX_BUFFER_SIZE,stdin);

                if(in[0] == '\n'){
                    systemclear();
                    continue;
                }

                strtok(in, "\n");
                p = atoi(in);

                if(p<1 || p>10) {
                    printf("+------------------------------------+\n");
                    printf("| Introduza um valor entre 1 e 10    |\n");
                    printf("+------------------------------------+\n");
                    free(in);
                    continue;
                }
                else{
                    free(in);
                    break;
                }
            }

            DATE d;
            d.day = current_time->tm_mday;
            d.month = current_time->tm_mon+1;
            d.year = current_time->tm_year + 1900;

            TASK t = createTASK(d,tname,id,p);
            id++;
            addToDo(lToDo,t);
            systemclear();
            printf("+------------------------------------+\n");
            printf("| Tarefa adicionada com sucesso!     |\n");
            printf("+------------------------------------+\n");
            save(fname);
            count++;
        }
    }
}

/*
* Verifica se a data inserida é válida
*/
int isDateValid(char* d, int t) {

    if(t == 0){
        for(int i = 0; i<strlen(d); i++) {
            if(isdigit(d[i]) == 0) return 0;
            else t = atoi(d);
        }
        if(t<1 || t>31) return 0;
        else return 1;
    }

    if(t == 1) {
        for(int i = 0; i<strlen(d); i++) {
            if(isdigit(d[i]) == 0) return 0;
            else t = atoi(d);
        }
        if(t<1 || t>12) return 0;
        else return 1;
    }

    if(t == 2) {
        for(int i = 0; i<strlen(d); i++) {
            if(isdigit(d[i]) == 0) return 0;
        }
    }

    return 1;
}

/*
* Adiciona tarefas da lista toDo->Doing (check)
*/
void toDo2Doing() {

    if(size(lToDo) == 0) {
        printf("+-------------------------------------------------------------------------+\n");
        printf("| Ainda não existem tarefas em toDo que possam ser adicionadas a Doing    |\n");
        printf("+-------------------------------------------------------------------------+\n");
        return;
    }

    while(1) {

        char *ind = malloc(sizeof(char)*MAX_BUFFER_SIZE);

        printf("+---------------------------------------------------------------+\n");
        printf("| Escolha a tarefa que quer passar de toDo para Doing           |\n");
        printf("| prev para voltar atrás                                        |\n");
        printf("| q para sair                                                   |\n");
        printf("| h para ajuda                                                  |\n");
        printf("+---------------------------------------------------------------+\n");

        printToDo(lToDo);

        fgets(ind,MAX_BUFFER_SIZE,stdin);

        if(ind[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(ind, "\n");
        systemclear();

        if(strlen(ind) == 1 && ind[0] == 'q') {
            free(ind);
            user_exit();
        }
        else if(strcmp("prev",ind)==0) {
            free(ind);
            systemclear();
            return;
        }
        else {
            int c = atoi(ind);
            free(ind);
            TASK temp = findTask(lToDo,c);
            if(temp.id!= -1) {
                removeTask(lToDo,temp);
                systemclear();

                while(1) {
                    printf("+------------------------------+\n");
                    printf("| Introduza o dono da tarefa   |\n");
                    printf("+------------------------------+\n");
                    char* owner = malloc(sizeof(char)*MAX_BUFFER_SIZE);

                    fgets(owner,MAX_BUFFER_SIZE,stdin);

                    if(owner[0] == '\n'){
                        systemclear();
                        continue;
                    }
                    else{
                        strtok(owner, "\n");
                        strcpy(temp.owner,owner);
                        systemclear();
                        break;
                    }
                }

                while(1) {
                    printf("+------------------------------+\n");
                    printf("| Introduza a data limite      |\n");
                    printf("+------------------------------+\n");
                    DATE d1,d2;
                    time_t s;
                    struct tm* current_time;
                    s = time(NULL);
                    current_time = localtime(&s);

                    d1.day = current_time->tm_mday;
                    d1.month = current_time->tm_mon+1;
                    d1.year = current_time->tm_year + 1900;
                    char* d = malloc(sizeof(char)*2);
                    printf("dia: ");
                    fgets(d,MAX_BUFFER_SIZE,stdin);
                    if(d[0] == '\n'){
                        systemclear();
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        free(d);
                        continue;
                    }

                    strtok(d, "\n");
                    if(isDateValid(d,0) == 0){
                        systemclear();
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        continue;
                    }
                    else d2.day = atoi(d);

                    printf("mês: ");

                    fgets(d,MAX_BUFFER_SIZE,stdin);
                    if(d[0] == '\n'){
                        systemclear();
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        free(d);
                        continue;
                    }

                    strtok(d, "\n");

                    if(isDateValid(d,1) == 0){
                        systemclear();
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        free(d);
                        continue;
                    }
                    else d2.month = atoi(d);

                    printf("ano: ");

                    fgets(d,MAX_BUFFER_SIZE,stdin);
                    if(d[0] == '\n'){
                        systemclear();
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        free(d);
                        continue;
                    }

                    strtok(d, "\n");

                    if(isDateValid(d,2) == 0){
                        systemclear();
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        free(d);
                        continue;
                    }
                    else d2.year = atoi(d);

                    if(compareDate(d1,d2) >= 0) {
                        systemclear();
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        continue;
                    }

                    else {
                        temp.deadLine = d2;
                        break;
                    }
                }

                systemclear();
                addDoing(lDoing,temp);
                printf("+--------------------------------------------+\n");
                printf("| Tarefa adicionada a Doing com sucesso!     |\n");
                printf("+--------------------------------------------+\n");
                save(fname);
                break;
           }
           else {
                systemclear();
                printf("+--------------------------------------------+\n");
                printf("| A tarefa que pediu, não existe na lista    |\n");
                printf("+--------------------------------------------+\n");
                continue;
            }
        }
    }
}

/*
* Adiciona tarefas da lista Doing->toDo (check)
*/
void doing2ToDo() {

    if(size(lDoing) == 0) {
        printf("+-------------------------------------------------------------------------+\n");
        printf("| Ainda não existem tarefas em Doing onde o responsável pode ser alterado |\n");
        printf("+-------------------------------------------------------------------------+\n");
        return;
    }
    while(1) {

        char *ind = malloc(sizeof(char)*MAX_BUFFER_SIZE);

        printf("+---------------------------------------------------------------+\n");
        printf("| Escolha a tarefa que quer passar para ToDo                    |\n");
        printf("| prev para voltar atrás                                        |\n");
        printf("| q para sair                                                   |\n");
        printf("| h para ajuda                                                  |\n");
        printf("+---------------------------------------------------------------+\n");

        printDoing(lDoing);

        fgets(ind,MAX_BUFFER_SIZE,stdin);

        if(ind[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(ind, "\n");
        systemclear();

        if(strlen(ind) == 1 && ind[0] == 'q') {
            free(ind);
            user_exit();
        }
        else if(strcmp("prev",ind)==0) {
            free(ind);
            systemclear();
            return;
        }
        else {
            int c = atoi(ind);
            free(ind);
            TASK temp = findTask(lDoing,c);
            if(temp.id!= -1) {
                systemclear();
                removeTask(lDoing,temp);

                DATE d;
                d.day = -1;
                d.month = -1;
                d.year = -1;

                temp.dEnd = d;
                temp.owner[0] = '\0';

                addToDo(lToDo,temp);
                save(fname);
                break;
            }
        }
    }
}

/*
* Adiciona tarefas da lista Doing->Done (check)
*/
void doing2Done () {

    systemclear();
    if(size(lDoing) == 0) {
        printf("+-------------------------------------------------------------------------+\n");
        printf("| Ainda não existem tarefas em Doing que possam ser adicionadas a Done    |\n");
        printf("+-------------------------------------------------------------------------+\n");
        return;
    }
    while(1) {

        char *ind = malloc(sizeof(char)*MAX_BUFFER_SIZE);

        printf("+---------------------------------------------------------------+\n");
        printf("| Escolha a tarefa que quer terminar                            |\n");
        printf("| prev para voltar atrás                                        |\n");
        printf("| q para sair                                                   |\n");
        printf("| h para ajuda                                                  |\n");
        printf("+---------------------------------------------------------------+\n");

        printDoing(lDoing);

        fgets(ind,MAX_BUFFER_SIZE,stdin);

        if(ind[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(ind, "\n");
        systemclear();

        if(strlen(ind) == 1 && ind[0] == 'q') {
            free(ind);
            user_exit();
        }
        else if(strcmp("prev",ind)==0) {
            free(ind);
            systemclear();
            return;
        }
        else {
            int c = atoi(ind);
            free(ind);
            TASK temp = findTask(lDoing,c);
            if(temp.id!= -1) {
                systemclear();
                removeTask(lDoing,temp);

                DATE d;
                time_t s;
                struct tm* current_time;
                s = time(NULL);
                current_time = localtime(&s);

                d.day = current_time->tm_mday;
                d.month = current_time->tm_mon+1;
                d.year = current_time->tm_year + 1900;
                temp.dEnd = d;
                systemclear();

                addDone(lDone,temp);

                printf("+--------------------------------------------+\n");
                printf("| Tarefa adicionada a Done com sucesso!      |\n");
                printf("+--------------------------------------------+\n");
                save(fname);
                break;
            }
            else {
                printf("+--------------------------------------------+\n");
                printf("| A tarefa que pediu, não existe na lista    |\n");
                printf("+--------------------------------------------+\n");
                continue;
            }
        }
    }
}

/*
* Reabre uma tarefa, anteriormente terminada (check)
*/
void done2Doing() {

    if(size(lDone) == 0) {
        printf("+-------------------------------------------------------------------------+\n");
        printf("| Ainda não existem tarefas em Done que possam ser reabertas              |\n");
        printf("+-------------------------------------------------------------------------+\n");
        return;
    }
    while(1) {

        char *ind = malloc(sizeof(char)*MAX_BUFFER_SIZE);

        printf("+---------------------------------------------------------------+\n");
        printf("| Escolha a tarefa que quer reabrir                             |\n");
        printf("| prev para voltar atrás                                        |\n");
        printf("| q para sair                                                   |\n");
        printf("| h para ajuda                                                  |\n");
        printf("+---------------------------------------------------------------+\n");

        printDone(lDone);

        fgets(ind,MAX_BUFFER_SIZE,stdin);

        if(ind[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(ind, "\n");
        systemclear();

        if(strlen(ind) == 1 && ind[0] == 'q') {
            free(ind);
            user_exit();
        }
        else if(strcmp("prev",ind)==0) {
            free(ind);
            systemclear();
            return;
        }
        else {
            int c = atoi(ind);
            free(ind);
            TASK temp = findTask(lDone,c);
            if(temp.id!= -1) {
                systemclear();
                removeTask(lDone,temp);
                DATE d;
                d.day = -1;
                d.month = -1;
                d.year = -1;
                temp.dEnd = d;
                systemclear();

                addDoing(lDoing,temp);

                printf("+--------------------------------------------+\n");
                printf("| Tarefa adicionada a Doing com sucesso!     |\n");
                printf("+--------------------------------------------+\n");
                save(fname);
                break;
            }
            else {
                printf("+--------------------------------------------+\n");
                printf("| A tarefa que pediu, não existe na lista    |\n");
                printf("+--------------------------------------------+\n");
                continue;
            }
        }
    }
}

/*
* Muda o dono de uma certa tarefa (check)
*/
void change_owner() {

    if(size(lDoing) == 0) {
        printf("+-------------------------------------------------------------------------+\n");
        printf("| Ainda não existem tarefas em Doing onde o responsável pode ser alterado |\n");
        printf("+-------------------------------------------------------------------------+\n");
        return;
    }
    while(1) {

        char *ind = malloc(sizeof(char)*MAX_BUFFER_SIZE);

        printf("+---------------------------------------------------------------+\n");
        printf("| Escolha a tarefa que quer alterar o responsável               |\n");
        printf("| prev para voltar atrás                                        |\n");
        printf("| q para sair                                                   |\n");
        printf("| h para ajuda                                                  |\n");
        printf("+---------------------------------------------------------------+\n");

        printDoing(lDoing);

        fgets(ind,MAX_BUFFER_SIZE,stdin);

        if(ind[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(ind, "\n");
        systemclear();

        if(strlen(ind) == 1 && ind[0] == 'q') {
            free(ind);
            user_exit();
        }
        else if(strcmp("prev",ind)==0) {
            free(ind);
            systemclear();
            return;
        }
        else {
            int c = atoi(ind);
            free(ind);
            TASK temp = findTask(lDoing,c);
            if(temp.id!= -1) {
                systemclear();
                removeTask(lDoing,temp);

                printf("+--------------------------------------------+\n");
                printf("| Introduza o novo responsável pela tarefa   |\n");
                printf("+--------------------------------------------+\n");

                while(1) {
                    char* owner = malloc(sizeof(char)*MAX_BUFFER_SIZE);

                    fgets(owner,MAX_BUFFER_SIZE,stdin);

                    if(owner[0] == '\n'){
                        systemclear();
                        continue;
                    }
                    else{
                        strtok(owner, "\n");
                        strcpy(temp.owner,owner);
                        addDoing(lDoing,temp);
                        printf("+--------------------------------------------+\n");
                        printf("| Responsável alterado com sucesso!          |\n");
                        printf("+--------------------------------------------+\n");
                        free(owner);
                        save(fname);
                        systemclear();
                        return;
                    }
                }
            }
            else {
                printf("+--------------------------------------------+\n");
                printf("| A tarefa que pediu, não existe na lista    |\n");
                printf("+--------------------------------------------+\n");
                continue;
            }
        }
    }
}

/*
* Menu principal onde se fazem as mudanças de quadros (check)
*/
void func() {
	while(1) {
        char *sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);
		printf("+--------------------------------------------------------------+\n");
		printf("| 1. Adicionar tarefas a ToDo                                  |\n");
		printf("| 2. Passar uma tarefa de ToDo para Doing                      |\n");
        printf("| 3. Passar uma tarefa de Doing para ToDo                      |\n");
		printf("| 4. Terminar uma tarefa                                       |\n");
		printf("| 5. Reabrir uma tarefa já finalizada                          |\n");
		printf("| 6. Alterar pessoa responsável por uma tarefa                 |\n");
		printf("| 7. Vizualizar o quadro                                       |\n");
		printf("| 8. Vizualizar as tarefas de uma pessoa                       |\n");
		printf("| 9. Vizualizar todas as tarefas ordenadas por data de criação |\n");
		printf("| prev para voltar atrás                                       |\n");
        printf("| q para sair                                                  |\n");
		printf("+--------------------------------------------------------------+\n");

		fgets(sel,MAX_BUFFER_SIZE,stdin);

        if(sel[0] == '\n'){
            systemclear();
            continue;
        }

        strtok(sel, "\n");
        systemclear();

        if(strlen(sel) == 1 && sel[0] == 'q') {
            free(sel);
            user_exit();
        }
        else if(strcmp("prev",sel)==0) {
            free(sel);
            systemclear();
            menu();
        }

		else if(strlen(sel) > 1){
            printf("+--------------------------------------------------------------+\n");
            printf("| Introduza apenas um caracter                                 |\n");
            printf("+--------------------------------------------------------------+\n");
            free(sel);
            continue;
        }

		else{
			switch(sel[0]) {
				case '1':
                    systemclear();
					addToDoInterface();
					free(sel);
					break;
				case '2':
                    systemclear();
                    toDo2Doing();
                    free(sel);
					break;
                case '3':
                    systemclear();
                    doing2ToDo();
                    free(sel);
                    break;
				case '4':
                    systemclear();
					doing2Done();
					free(sel);
					break;
				case '5':
                    systemclear();
                    done2Doing();
                    free(sel);
					break;
				case '6':
                    systemclear();
                    change_owner();
                    free(sel);
					break;
				case '7':
                    systemclear();
					//print_table();
					free(sel);
					break;
				case '8':
                    systemclear();
					//print_taskOwned();
					free(sel);
					break;
				case '9':
                    systemclear();
					//print_by_date();
					free(sel);
					break;
				case 'h': case 'H':
                    systemclear();
					print_help();
					free(sel);
					break;
                //Quer guardar o trabalho ? Novo ou já existente
				case 'q': case 'Q':
                    systemclear();
                    user_exit();
                    free(sel);
					break;
				default:
					printf("Error: Escolha uma opção válida\n\n");
					free(sel);
					continue;
			}
		}
	}
}

//Main
int main(int argc, char const *argv[]) {
    DATE d;
	d.day = 1;
	d.month = 1;
	d.year = 1999;
	temp = createTASK(d,"",0,0);
    lToDo = createList();
    lDoing = createList();
    lDone = createList();
 	systemclear();
    id = 0;
	menu();
}
