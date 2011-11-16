#include "shell.h"

void initList(char **list, int tam)
{
	int i;

	for(i=0; i < tam; i++)
		list[i] = NULL;

	return;
}

void getPath(char **envp, char *path)
{
	int countenvp = 0;

	while(1)
	{
		//procura na lista de variaveis do sistema a substring "PATH="
		if((strncmp(envp[countenvp], "PATH=", 5)) != 0)
			countenvp++;
		else //quando encontra a variavel PATH sai do loop
			break; 
	}

	strncpy(path, strtok(envp[countenvp], "PATH="), strlen(envp[countenvp])); //copia a variavel PATH encontrada
	return;
}

void armazenaPath(char *path, char **listpath)
{
	char *string = NULL;
	int i = 0;

	string = strtok(path, ":");
	while(string != NULL)
	{
		listpath[i] = string;
		string = strtok(NULL, ":");
		i++;
	}
	return;
}

void armazenaArg(char *comando, char **listarg, int *tipo)
{
	char *string = NULL;
	int i = 0;	//contador de arg

	string = strtok(comando, " ");  //separa a primeira parte da string
	while(string != NULL)
	{
			if(string[0] == '<') tipo = 0;
			else if (string[0] == '>') tipo = 1;
			else
			{
				listarg[i] = string; //ponteiro apontando para parte da string que será o argumento
				string = strtok(NULL, " "); //continua do ponto que parou anteriormente
				i++;
			}
	}
	return;
}

int procuraProg(char *arg, char *nomeProg, char **listpath)
{
	char local[400];
	FILE *prog;
	int i = 0;

	while(listpath[i] != NULL)
	{
		strcpy(local, listpath[i]);
		strcat(local, "/");
		strcat(local, nomeProg);

		if((prog = fopen(local, "r"))) //se o arquivo existe a funcao fopen retorna 1 caso contrario 0
		{
    		fclose(prog);
    		strncpy(arg, local, strlen(local));  // a variavel caminho passada por parametro recebe o local
    		return 1;  //sucesso
  		}
		i++;
	}
	return 0; //não encontrou o comando
}

void execProg(char *arg, char **listarg, int tipo)
{
	pid_t pid;
	int status;
	int fd;

	pid = fork();
	if (pid < 0 )
	{
		printf("Erro!\n");
		exit (-1);
	}
	if (pid  == 0) /* PROCESSO FILHO */
	{
		if(tipo == 0) fd = fopen(arg, "r");
		else fd = fopen(arg, "w");

		if (fd < 0)
		{
			printf("Erro fatal na execução\n");
			exit(0);
		}
		if (!tipo) dup2(fd,0);
		else dup2(fd,1);

		if(execv(arg, listarg) == -1)
			printf("Erro na execucao\n");
		close (fd);
	}
	else /* PROCESSO PAI */
	{
		pid = wait(&status); /* espera que o filho termine */
	}
	return;
}
