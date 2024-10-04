/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelll.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:36:58 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 20:49:02 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


//========= DEFINITIONS =====================

# define EXIT_SUCCESS 	0
# define EXIT_FAILURE 	1

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100000
#endif
//========== Libft ===================
#include <libft/libft.h>

//============ HEADER FILES =============
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


//=========== STRUCTS =====================

typedef enum {
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_RIDIRECTION,
	TOKEN_UNKNOWN 	
}	token_type;

/*
	COMMAND STRUCT
*/
typedef struct s_comands
{
    char    *cmd; // this is going to store the comand name
    char    **args; // arguments of the comands
	int		input_redir; // FD for input rederections
	int		output_redir;// FD for output rederections
    struct s_comand *next;
}   t_comands;

/*
	LEXER STRUCT
*/
typedef struct s_lexer
{
	char		*input; // the original input 
	t_comands	*comands; // pointer to the commands => STRUCT
	int			n_of_cmd; // Number of commands
}	t_lexer;

/*
	TOKEN STRUCT
*/
typedef struct s_token
{
	char		*data;
	token_type	type;
	struct s_token *next;
}	t_token;



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
void shell_loop(t_shell *msh);

// prompt;
char *create_prompt(void);

// the loop
void shell_loop(t_shell *msh); 

// LEXING
int ft_isspace(char c); // chec if it is a white space
 
int is_this(char c);  // checks the delimeter

token_type get_token_type(char c); // check what type of token is

t_token *create_tok(char *data, token_type type); // creates a token 

void add_token(t_token **tokens, t_token *new_token); // ad the token to the list of tokens

char *create_redir_arr(char c);

t_token *lexer(char *prompt);

void free_token(t_token *head);
#endif