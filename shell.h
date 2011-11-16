#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/stat.h>
#include <errno.h>

#define NARG 10	/* número máximo de argumentos aceitáveis */
#define NDIR 30	/* número máximo de diretorios na variavel PATH */

/*definição das funções*/

/*inicializa ou limpa a lista, preenchendo-a com NULL*/
void initList(char **list, int tam);

/*captura as variáveis de caminho do sistema na variável path*/
void getPath(char **envp, char *path);

/*armazena cada variável do sistema (contidas em path) em uma linha da matriz listpath*/
void armazenaPath(char *path, char **listpath);

/*armazena o comando digitado separando os argumentos em linhas da matriz listarg*/
void armazenaArg(char *comando, char **listarg, int *tipo);

/*utiliza o comando fopen para verificar se o programa existe ou não
  retorna 1 (e o caminho do comando em arg) caso exista ou 0 (e não alterar o arg) caso contrário*/
int procuraProg(char *arg, char *nomeProg, char **listpath);

/*cria um processo filho para executar o comando*/
void execProg(char *arg, char **listarg, int tipo);
