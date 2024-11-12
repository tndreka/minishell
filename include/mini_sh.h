/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:48:37 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/11 16:02:00 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

//============ HEADER FILES =============
# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include  <limits.h>
# include <fcntl.h>


# define EXIT_SUCCESS 	0
# define EXIT_FAILURE 	1

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000
#endif

//=========== STRUCTS =====================

typedef enum e_token {
    COMMAND,
    FILENAME,
    ARGUMENT,
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    PIPE,
    REDIRIN,
    REDIROUT,
    REDIROUTAPP,
    HEREDOC,
    DELIMITER,
    STRING,
    APPEND,
    UNKNOWN
}	t_token;


typedef struct s_lexer
{
    char				*data;
    t_token				type;
    struct s_lexer		*next;
}	t_lexer;

typedef struct t_simple_command
{
    char						*content;
    struct t_simple_command		*next;
}	t_cmd;

typedef struct t_command_table
{
    bool						leftpipe;
    bool						rightpipe;
    t_cmd						*command;
    t_cmd						*cmd_head;
    struct t_command_table		*next;
}		t_table;

/* === MINISHELL STRUCT ===*/
/*
*** This struct is going to contain every information if minishell data
*** comand info , comand table
*** input information.
*/

typedef struct s_minishell
{
    t_table	*table;
    t_table	*table_head;
    char	**env;
    char	**var_lst;
    char	*out_redir;
    int		outfd;
    char	*in_redir;
    int		infd;
    int		exit_code;
    bool	success;
    bool	append_mode;
}		t_msh;


t_msh *init_minishell(int ac, char *av[], char *envp[]);
void minishell_parser(char *prompt, t_msh *msh);
void prompt(t_msh *msh);
t_lexer *tokenize_prompt(char *prompt);

// LEXING
int ft_isspace(char c); // chec if it is a white space

int is_this(char c);  // checks the delimeter

t_token get_token_type(char c); // check what type of token is

t_lexer *create_tok(char *data, t_token type); // creates a token 

void add_token(t_lexer **tokens, t_lexer *new_token); // ad the token to the list of tokens

char *create_redir_arr(char c);

t_lexer *lexer(char *prompt);

void free_token(t_lexer *head);

void print_token(t_lexer *tokens);

char *handle_quote(char *start);


void		executor(t_msh *mini);
void		handle_echo(t_msh *mini);
void		handle_pwd(t_msh *mini);
void		handle_cd(t_msh *mini);
void		handle_env(t_msh *mini);
void		handle_export(t_msh *mini);
void		handle_unset(t_msh *mini);
void        handle_exit(t_msh *mini);
void		execute_file(t_msh *mini);
void		check_path(t_msh *mini);
char		**list2array(t_msh *mini);
void		free_arr(char **arr);
void		swap_vars(char **newenv);
void		replace_env(t_msh *mini, char *path, char *env);
char		*ft_getcwd(t_msh *mini);
char		**create_arg_lst(t_msh *mini);
char		*ft_check_var_lst(t_msh *mini, char *var);
void		add_var_to_list(t_msh *mini);
void    	mini_main(t_msh *mini);
int			handle_redirections(t_msh *mini);
void		restore_redirections(t_msh *mini);
t_msh		*init_mini_vars(int argc, char **argv, char **envp);
bool		ft_isnumber(char *content);
void		free_mini(t_msh *mini, bool keep_env);
void        sigint_handler(int sig);
void	    handle_signals(void);
int         check_existing_var(char *newvar, t_msh *mini);
void    	handle_shlvl(t_msh *mini, char sign);
bool	    check_nl(char *content);
bool		check_builtin(t_msh *minish);
char        *ft_strndup(char *s1, size_t len);
void	    free_table(t_msh *minish);
void	    free_cmd(t_cmd *cmd);

char	    *ft_getenv(t_msh *mini, char *env);
int	        ft_strcmp(char *s1, char *s2);
void	    replace_varname_wtih_var(char **expanded_string, char **env);
void	    append_remainder(char **expanded_string, char **content, int pos);
char	    **copy_env(char **envp);
char	    *check_and_expand_env(char **content, int *i, t_msh *minish);
char	    *check_string(char **content, t_msh *minish);
// void		trip_to_table_pipe(t_lexer *token, t_table *table);
#endif