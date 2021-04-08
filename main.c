#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "list.h"

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

    if(strcmp(user_fname,"temp->txt") != 0){
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

        else if(sel[0] == 's'){
            free(sel);
            char *user_fname = malloc(sizeof(char)*MAX_BUFFER_SIZE);
            printf("+------------------------------------------+\n");
            printf("| Introduza o nome do ficheiro             |\n");
            printf("+------------------------------------------+\n");

            scanf(" %s",user_fname);
            save(user_fname);
            exit(0);
        }
        else {
            free(sel);
            remove(fname);
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

                getline(&line,&buffsize,file);
                n = atoi(line);

                for(int i = 0; i<n; i++) {
                    getline(&line,&buffsize,file);
                    char linearray[strlen(line)];

                    strcpy(linearray,line);

                    strcpy(temp.name,strtok(linearray,sep));
                    temp.owner = strtok(NULL,sep);
                    temp.id= atoi(strtok(NULL,sep));
                    temp.priority = atoi(strtok(NULL,sep));

                    getline(&line,&buffsize,file);
                    char date[strlen(line)];
                    strcpy(date,line);

                    temp.dStart.day = atoi(strtok(date," "));
                    temp.dStart.month = atoi(strtok(NULL," "));
                    temp.dStart.year = atoi(strtok(NULL," "));

                    getline(&line,&buffsize,file);
                    date[strlen(line)];
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
                    temp.owner = strtok(NULL,sep);
                    temp.id= atoi(strtok(NULL,sep));
                    temp.priority = atoi(strtok(NULL,sep));

                    getline(&line,&buffsize,file);
                    char date[strlen(line)];
                    strcpy(date,line);

                    temp.dStart.day = atoi(strtok(date," "));
                    temp.dStart.month = atoi(strtok(NULL," "));
                    temp.dStart.year = atoi(strtok(NULL," "));

                    getline(&line,&buffsize,file);
                    date[strlen(line)];
                    strcpy(date,line);

                    temp.deadLine.day = atoi(strtok(date," "));
                    temp.deadLine.month = atoi(strtok(NULL," "));
                    temp.deadLine.year = atoi(strtok(NULL," "));

                    getline(&line,&buffsize,file);
                    date[strlen(line)];
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

	char* sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);
	int error = 1;

	while(error!=0) {

		printf("+--------------------------------------------------------------+\n");
		printf("| 1. Criar um novo quadro                                      |\n");
		printf("| 2. Usar um quadro exisistente                                |\n");
		printf("| h for help, q for quit                                       |\n");
		printf("+--------------------------------------------------------------+\n");

		scanf(" %s",sel);

		systemclear();

		if(strlen(sel) > 1) printf("Introduza apenas um caracter\n\n");
		else{
			switch(sel[0]) {
				case '1':
                    free(sel);
                    fname = "temp->txt";
					func();
					error = 0;
					break;
				case '2':
                    free(sel);
					existing_table();
					func();
					error = 0;
					break;
				case 'h': case 'H':
                    free(sel);
					print_help();
					error = 1;
					break;
				case 'q': case 'Q':
                    free(sel);
					return;
				default:
					printf("Error: Escolha uma opção válida\n\n");
			}
		}
	}
	return;
}

/*
* Adiciona tarefas à lista toDo
*/
void addToDoInterface() {
    //flush inputbuffer
    int c;
    while((c = getchar()) != '\n' && c != EOF);

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
            printf("+------------------------------------+\n");
            printf("| Introduza a prioridade             |\n");
            printf("+------------------------------------+\n");
            //bug se for letra
            scanf(" %d",&p);

            while(p<1 || p>10) {
                systemclear();
                printf("+------------------------------------+\n");
                printf("| Introduza um valor entre 1 e 10    |\n");
                printf("+------------------------------------+\n");
                scanf("%d",&p);
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
* Adiciona tarefas da lista toDo->Doing
*/
void toDo2Doing() {

    systemclear();

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

        scanf(" %s",ind);

        if(strcmp("prev",ind)==0) {
            free(ind);
            return;
        }
        else if(strlen(ind) == 1 && ind[0] == 'q') {
            user_exit();
        }
        else {
            int c = atoi(ind);
            TASK temp = findTask(lToDo,c);
            if(temp.id!= -1) {
                systemclear();
                temp.owner = malloc(sizeof(char)*MAX_BUFFER_SIZE);
                removeTask(lToDo,temp);

                printf("+------------------------------+\n");
                printf("| Introduza o dono da tarefa   |\n");
                printf("+------------------------------+\n");

                scanf(" %s",temp.owner);

                systemclear();

                printf("+------------------------------+\n");
                printf("| Introduza a data limite      |\n");
                printf("+------------------------------+\n");

                while(1) {

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
                    scanf("%s",d);
                    if(isDateValid(d,0) == 0){
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        continue;
                    }
                    else d2.day = atoi(d);

                    printf("mês: ");
                    scanf("%s",d);
                    if(isDateValid(d,1) == 0){
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
                        continue;
                    }
                    else d2.month = atoi(d);

                    printf("ano: ");
                    scanf("%s",d);
                    if(isDateValid(d,2) == 0){
                        printf("+--------------------------------+\n");
                        printf("| Introduza uma data válida!     |\n");
                        printf("+--------------------------------+\n");
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
* Adiciona tarefas da lista Doing->toDo
*/
void Doing2ToDo() {
    systemclear();
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

        scanf(" %s",ind);

        if(strcmp("prev",ind)==0) {
            free(ind);
            return;
        }
        if(strlen(ind) == 1 && ind[0] == 'q') {
            user_exit();
        }
        else {
            int c = atoi(ind);
            TASK temp = findTask(lDoing,c);
            if(temp.id!= -1) {
                systemclear();
                removeTask(lDoing,temp);

                DATE d;
                d.day = -1;
                d.month = -1;
                d.year = -1;

                temp.dEnd = d;
                temp.owner = NULL;

                addToDo(lToDo,temp);


                break;
            }
        }
    }
}

/*
* Adiciona tarefas da lista Doing->Done
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

        scanf(" %s",ind);

        if(strcmp("prev",ind)==0) {
            free(ind);
            save(fname);
            return;
        }
        if(strlen(ind) == 1 && ind[0] == 'q') {
            user_exit();
        }
        else {
            int c = atoi(ind);
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
                save("");
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
* Reabre uma tarefa, anteriormente terminada
*/
void done2Doing() {
    systemclear();
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

        scanf(" %s",ind);

        if(strcmp("prev",ind)==0) {
            free(ind);
            return;
        }
        if(strlen(ind) == 1 && ind[0] == 'q') {
            user_exit();
        }
        else {
            int c = atoi(ind);
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
* Muda o dono de uma certa tarefa
*/
void change_owner() {
    systemclear();
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

        printDone(lDoing);

        scanf(" %s",ind);

        if(strcmp("prev",ind)==0) {
            free(ind);
            return;
        }
        if(strlen(ind) == 1 && ind[0] == 'q') {
            user_exit();
        }
        else {
            int c = atoi(ind);
            TASK temp = findTask(lDoing,c);
            if(temp.id!= -1) {
                systemclear();
                char* new_owner = malloc(sizeof(char)*MAX_BUFFER_SIZE);
                removeTask(lDoing,temp);

                printf("+--------------------------------------------+\n");
                printf("| Introduza o novo responsável pela tarefa   |\n");
                printf("+--------------------------------------------+\n");

                scanf(" %s",new_owner);

                strcpy(temp.owner,new_owner);
                addDoing(lDoing,temp);

                printf("+--------------------------------------------+\n");
                printf("| Responsável alterado com sucesso!          |\n");
                printf("+--------------------------------------------+\n");

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

//0 -> existing file
//1 -> new file
void func(int n) {

	char *sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);
	while(1) {
		printf("+--------------------------------------------------------------+\n");
		printf("| 1. Adicionar tarefas a ToDo                                  |\n");
		printf("| 2. Passar uma tarefa de ToDo para Doing                      |\n");
        printf("| 3. Passar uma tarefa de Doing para ToDo                      |\n");
		printf("| 4. Terminar uma tarefa                                       |\n"); //Passar para done
		printf("| 5. Reabrir uma tarefa já finalizada                          |\n");
		printf("| 6. Alterar pessoa responsável por uma tarefa                 |\n");
		printf("| 7. Vizualizar o quadro                                       |\n");
		printf("| 8. Vizualizar as tarefas de uma pessoa                       |\n");
		printf("| 9. Vizualizar todas as tarefas ordenadas por data de criação |\n");
		printf("+--------------------------------------------------------------+\n");

		scanf(" %s",sel);

		systemclear();

		if(strlen(sel) > 1) printf("Introduza apenas um caracter \n\n");
		else{
            printf("%s",sel);
			switch(sel[0]) {
				case '1':
                    systemclear();
					addToDoInterface();
					break;
				case '2':
                    systemclear();
                    toDo2Doing();
					break;
                case '3':
                    systemclear();
                    Doing2ToDo();
                    break;
				case '4':
                    systemclear();
					doing2Done();
					break;
				case '5':
                    systemclear();
                    done2Doing();
					break;
				case '6':
                    systemclear();
                    change_owner();
					break;
				case '7':
                    systemclear();
					//print_table();
					break;
				case '8':
                    systemclear();
					//print_taskOwned();
					break;
				case '9':
                    systemclear();
					//print_by_date();
					break;
				case 'h': case 'H':
                    systemclear();
					print_help();
					break;
                //Quer guardar o trabalho ? Novo ou já existente
				case 'q': case 'Q':
                    systemclear();
                    user_exit();
					break;
				default:
					printf("Error: Escolha uma opção válida\n\n");
					continue;
			}
		}
	}
	free(sel);
}

//Fazer uma função que prepare o ambiente para testing, isto é, mover ficheiros, para temp ou saves, consoante o teste
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
