#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

#define MAX_BUFFER_SIZE 1024

void new_table(char* fname);
void print_help();
void systemclear();

void systemclear() {
	system("clear");
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

void existing_table() {

	int error = 1;
	while (error != 2) {
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
			*
			* Abrir o ficheiro e passar para func
			*
			*/
		}
		else {
			char* sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);

			printf("+--------------------------------------------------------------+\n");
			printf("| Ficheiro não existe.                                         |\n");
			printf("| Verifique se escreveu o nome sem erros.                      |\n");
			printf("| Quer criar um novo ficheiro com esse nome ?                  |\n");
			printf("| s para sim, n para reescrever o nome do ficheiro.            |\n");
			printf("+--------------------------------------------------------------+\n");

			while(error != 0 || error != 2) {

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

	fclose(fp);
	return;

	//fp = rename(oldname, newname); para mudar o nome do ficheiro
	//remove(fp); remover o ficheiro

}


/*
*
* texto de ajuda, como funciona o programa, como deve ser o input dos ficheiros.
*
*/
void print_help() {
	systemclear();
	printf("help");
	return;
}


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
					new_table("");
					error = 0;
					break;
				case '2':
					existing_table();
					error = 0;
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
	}
	free(sel);
	return;
}

void func() {

	int error = 1;

	char *sel = malloc(sizeof(char)*MAX_BUFFER_SIZE);

	while(error != 0) {

		printf("+--------------------------------------------------------------+\n");
		printf("| 1. Adicionar tarefas a ToDo                                  |\n");
		printf("| 2. Mover Cartões                                             |\n");
		printf("| 3. Alterar pessoa responsável                                |\n");
		printf("| 4. Terminar uma tarefa                                       |\n"); //Passar para done
		printf("| 5. Passar tarefa Done ToDo                                   |\n");
		printf("| 6. Vizualizar o quadro                                       |\n");
		printf("| 7. Vizualizar as tarefas de uma pessoa                       |\n");
		printf("| 8. Vizualizar todas as tarefas ordenadas por data de criação |\n");
		printf("+--------------------------------------------------------------+\n");

		scanf(" %s",sel);

		systemclear();

		if(strlen(sel) > 1) printf("Introduza apenas um caracter \n\n");
		else{
			switch(sel[0]) {
				case '1':
					//new_table("");
					error = 0;
					break;
				case '2':
					//existing_table();
					error = 0;
					break;
				case '3':
					//existing_table();
					error = 0;
					break;
				case '4':
					//existing_table();
					error = 0;
					break;
				case '5':
					//existing_table();
					error = 0;
					break;
				case '6':
					//existing_table();
					error = 0;
					break;
				case '7':
					//existing_table();
					error = 0;
					break;
				case '8':
					//existing_table();
					error = 0;
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
	}
}

//Fazer uma função que prepare o ambiente para testing, isto é, mover ficheiros, para temp ou saves, consoante o teste

int main(int argc, char const *argv[]) {

 	systemclear();

	menu();

	return 0;


}
