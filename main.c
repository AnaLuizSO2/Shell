#include "shell.h"

int main (int argc, char *argv[], char *envp[])
{
	char *listarg[NARG];	//lista de argumentos
	char *listpath[NDIR];	//lista de diretórios no PATH

	initList(listarg, NARG);
	initList(listpath, NDIR);

	char comando[400]; //vetor para armazenar o leitura do terminal
	char path[400];  //vetor para armazernar a variavel path
	char *arg = (char *)malloc(sizeof(char) * 400);   //indicara o diretório do comando

	int tipo = 0;

	getPath(envp, path);
	armazenaPath(path, listpath);
	bzero(comando,400);  //preenche variável com zeros

	system("clear"); //limpa a tela
	printf("> ");

	while(1){
		scanf("%[^\n]", comando);   //captura do teclado até que um \n seja encontrado
		
		if((strcmp(comando, "exit")) == 0) break; //caso comando digitado for exit, sai do loop

		if (strlen(comando) != 0) {
			armazenaArg(comando, listarg, &tipo);

			if(procuraProg(arg, listarg[0], listpath))
				execProg(arg, listarg, tipo);
			else
				printf("%s: Comando não encontrado!\n" ,listarg[0]);
		}
		printf("> ");
		setbuf(stdin, NULL); //funcao para limpar o buffer
		bzero(comando,400);
		bzero(arg,400);
		initList(listarg, NARG);
	} //while

	free(arg);
	return 0;
}
