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

#define MAX_BUFFER_SIZE 1024

void systemclear();
bool file_exit(const char* filename);
void existing_table();

void new_table(char* fname);
void print_help();
void menu();
void func();

LIST lToDo,lDoing,lDone;
int id,isNew;
//Default is temp.txt
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
*
* Saves content in file
*
*/
void save(char* user_fname) {

    if(strcmp(user_fname,"") != 0){
        fname = malloc(sizeof(char)*strlen(user_fname));
        strcpy(fname,user_fname);
        strcat(fname,".txt");
    }

    FILE *fp = fopen(fname,"w+");
    LIST temp;

    //guardar os conteudos de lToDo
    fprintf(fp,"%d\n", size(lToDo));
    if(size(lToDo) >= 1) {
        temp = lToDo;
        temp = temp->next;
        while(temp){
            fprintf(fp,"%s\n",temp->task.name);
            fprintf(fp,"%d\n",temp->task.id);
            fprintf(fp,"%d\n",temp->task.priority);
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
            fprintf(fp,"%s\n",temp->task.name);
            fprintf(fp,"%s\n",temp->task.owner);
            fprintf(fp,"%d\n",temp->task.id);
            fprintf(fp,"%d\n",temp->task.priority);
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
            fprintf(fp,"%s\n",temp->task.name);
            fprintf(fp,"%s\n",temp->task.owner);
            fprintf(fp,"%d\n",temp->task.id);
            fprintf(fp,"%d\n",temp->task.priority);
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

        else {
            free(sel);
            char *user_fname = malloc(sizeof(char)*MAX_BUFFER_SIZE);
            printf("+------------------------------------------+\n");
            printf("| Introduza o nome do ficheiro             |\n");
            printf("+------------------------------------------+\n");

            scanf(" %s",user_fname);
            save(user_fname);
            exit(0);
        }
    }

}

/*
* Abre um ficheiro existente para leitura de dados
*
void existing_table() {

	int error = 2;

	while (error == 2) {
		//FILE *fp;

		//char* fname = malloc(sizeof(char)*MAX_BUFFER_SIZE);

		printf("+--------------------------------------------------------------+\n");
		printf("| Introduza o nome do ficheiro:                                |\n");
		printf("+--------------------------------------------------------------+\n");

		scanf(" %s",fname);

		char* path = malloc(strlen("/save/")+strlen(fname)+1);
		strcpy(path,"/save/");
		strcat(path,fname);

		systemclear();

		if(file_exist(path)) {
			/**
			*
			* Abrir o ficheiro e passar para func
			*
			*
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

				systemclear();

				if(strlen(sel) > 1) printf("Introduza apenas um caracter\n\n");
				else{
					switch(sel[0]) {
						case 's': case 'S':
							new_table(fname);
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
		free(fname);
	}
}
*/
void new_table(char* path) {
    func(1);
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
					new_table("");
					error = 0;
					break;
				case '2':
                    free(sel);
					//existing_table();
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

    char *sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);
    while(1) {
        systemclear();
        char* tname = malloc(sizeof(char)*MAX_BUFFER_SIZE);

        printf("+------------------------------------+\n");
        printf("| Introduza o nome da tarefa         |\n");
        printf("| prev para voltar atrás             |\n");
        printf("| q para sair                        |\n");
        printf("| h para ajuda                       |\n");
        printf("+------------------------------------+\n");

        scanf(" %s",tname);
        systemclear();

        if(strlen(tname) == 1) {
            if(tname[0] == 'q'){
                free(tname);
                free(sel);
                user_exit();
            }
        }
        else if(strcmp("prev",tname)==0) {
            free(tname);
            free(sel);
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
            return; //exit
        }
        else {
            int c = atoi(ind);
            TASK temp = findTask(lToDo,c);
            if(temp.id != -1) {
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
            return;
        }
        if(strlen(ind) == 1 && ind[0] == 'q') {
            user_exit();
        }
        else {
            int c = atoi(ind);
            TASK temp = findTask(lDoing,c);
            if(temp.id != -1) {
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
    if(size(lDoing) == 0) {
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
            if(temp.id != -1) {
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

//0 -> existing file
//1 -> new file
void func(int n) {

	int error = 1;

	char *sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);

	while(error != 0 || error != -1) {

		printf("+--------------------------------------------------------------+\n");
		printf("| 1. Adicionar tarefas a ToDo                                  |\n");
		printf("| 2. Passar uma tarefa de ToDo para Doing                      |\n");
		printf("| 3. Terminar uma tarefa                                       |\n"); //Passar para done
		printf("| 4. Reabrir uma tarefa já finalizada                          |\n");
		printf("| 5. Alterar pessoa responsável por uma tarefa                 |\n");
		printf("| 6. Vizualizar o quadro                                       |\n");
		printf("| 7. Vizualizar as tarefas de uma pessoa                       |\n");
		printf("| 8. Vizualizar todas as tarefas ordenadas por data de criação |\n");
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
					error = 0;
					break;
				case '2':
                    systemclear();
                    toDo2Doing();
					error = 0;
					break;
				case '3':
                    systemclear();
					doing2Done();
					error = 0;
					break;
				case '4':
                    systemclear();
                    done2Doing();
					error = 0;
					break;
				case '5':
                    systemclear();
                    //change_owner();
					error = 0;
					break;
				case '6':
                    systemclear();
					//print_table();
					error = 0;
					break;
				case '7':
                    systemclear();
					//print_taskOwned();
					error = 0;
					break;
				case '8':
                    systemclear();
					//print_by_date();
					error = 0;
					break;
				case 'h': case 'H':
                    systemclear();
					print_help();
					error = 1;
					break;
                //Quer guardar o trabalho ? Novo ou já existente
				case 'q': case 'Q':
                    systemclear();
                    user_exit();
					error = -1;
					break;
				default:
					printf("Error: Escolha uma opção válida\n\n");
			}
		}
	}
	free(sel);
}

//Fazer uma função que prepare o ambiente para testing, isto é, mover ficheiros, para temp ou saves, consoante o teste
int main(int argc, char const *argv[]) {
    lToDo = createList();
    lDoing = createList();
    lDone = createList();
 	systemclear();
    id = 0;
    fname = "temp.txt";
	menu();
	save("");
}
