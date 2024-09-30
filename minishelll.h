#ifndef MINISHELL_H
# define MINISHELL_H


//========= DEFINITIONS =====================

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100000
#endif
//========== Libft ===================
#include "libft/libft.h"

//============ HEADER FILES =============
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


//=========== STRUCTS =====================
typedef struct s_comands
{
    char    cmd;
    char    **args;
    int     arg_count;
    struct s_comand *next;
}   t_comands;

typedef struct s_shell
{
    char **env;
    char *input;
    char *prompt;
    t_comands   cmd;
} t_shell;

//============ FUNCTIONS ===============

// inicializon shellin
int init_shell(t_shell *msh, char **enviroment);

//duplikon enviroment variables
char **dub_env(char **enviroment);
void free_env(char **env);


//starton loopen e shell
void start_shell(t_shell *msh);

// prompt;
char *create_prompt(void);

// the loop
void shell_loop(t_shell *msh); 
#endif