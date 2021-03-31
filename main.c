#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
int id;

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
*
* Abre um ficheiro existente para leitura de dados
*
*/
void existing_table() {

	int error = 2;

	while (error == 2) {
		FILE *fp;

		char* fname = malloc(sizeof(char)*MAX_BUFFER_SIZE);

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
			*/
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

void new_table(char* path) {

	FILE* fp = malloc(sizeof(char)*MAX_BUFFER_SIZE);

	/*
	if (stat("/testes", &st) == -1) {
    	mkdir("/testes", 0700);
	}
	*/

	fp = fopen("temp.txt","w+");

    lToDo = createList();
    lDoing = createList();
    lDone = createList();

    func(1);



	fclose(fp);
	return;

	//fp = rename(oldname, newname); para mudar o nome do ficheiro
	//remove(fp); remover o ficheiro

}


/*
*
* texto de ajuda, como funciona o programa, como deve ser o input dos ficheiros.
* Quando ativado volta ao menu incial.
*
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
					existing_table();
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


void addToDoInterface() {
    int flag = 0;
    char *sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);
    while(flag != 1) {
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
            if(tname[0] == 'q') return;
        }
        else if(strcmp("prev",tname)==0) {
            free(tname);
            free(sel);
            flag = 1;
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

void toDo2Doing() {

    systemclear();
    int flag = 0;

    while(flag != 1) {

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
            flag = 1;
            return;
        }
        if(strlen(ind) == 1) {
            if(ind[0] == 'q') return; //exit
            else {
                int c = ind[0]-'0';
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
                    int error = 0;

                    while(error != 1) {
                        DATE d1,d2;
                        time_t s;
                        struct tm* current_time;
                        s = time(NULL);
                        current_time = localtime(&s);

                        d1.day = current_time->tm_mday;
                        d1.month = current_time->tm_mon+1;
                        d1.year = current_time->tm_year + 1900;

                        printf("dia: ");
                        scanf("%d",&d2.day);
                        printf("mês: ");
                        scanf("%d",&d2.month);
                        printf("ano: ");
                        scanf("%d",&d2.year);

                        if(compareDate(d1,d2) == 1) {
                            systemclear();
                            printf("+--------------------------------+\n");
                            printf("| Introduza uma data válida!     |\n");
                            printf("+--------------------------------+\n");
                        }
                        else {
                            error = 1;
                            temp.deadLine = d2;
                        }
                    }
                    systemclear();

                    addDoing(lDone,temp);

                    printf("+--------------------------------------------+\n");
                    printf("| Tarefa adicionada a Doing com sucesso!     |\n");
                    printf("+--------------------------------------------+\n");

                    flag = 1;
                }
                else {
                    printf("A tarefa que pediu, não existe na lista\n");
                }
            }
        }
        else {
            printf("Introduza apenas um caracter ou prev\n");
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
					//change_owner();
					error = 0;
					break;
				case '4':
                    systemclear();
					//Doing2Done();
					error = 0;
					break;
				case '5':
                    systemclear();
					//Done2Do();
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

 	systemclear();
    id = 0;
	menu();
	printToDo(lDone);

	return 0;


}
