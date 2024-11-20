/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:27:42 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/20 18:17:12 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H

# define LEXER_H

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

typedef struct t_minishell
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
	int		redirfd;
}		t_mini;

typedef enum token_type
{
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

typedef struct t_tokenizer
{
	char				*data;
	t_token				type;
	struct t_tokenizer	*next;
}		t_lexer;

typedef struct s_lexer_params
{
	char		*prompt;
	t_lexer		**head;
	t_lexer		**current;
	int			*i;
	t_mini		*msh;
}	t_lexer_params;

// // MAIN FUNCTIONS
t_lexer		*lexer(char *prompt, t_mini *msh);

void		handle_token(t_lexer_params *param);
void		create_comand_token(t_lexer_params *param);
void		double_qoute(t_lexer_params *param);
void		single_qoute(t_lexer_params *param);
void		redirection_less(t_lexer_params *param);
void		redirection(t_lexer_params *param);
// // HELPER FUNCTIONS
char		*ft_strndup(const char *s1, size_t len);
void		free_tkn_lst(t_lexer *token_lst);
int			ft_isspace(char c);
char		*ft_strncpy(char *dst, const char *src, size_t n);
// // UTILS
void		add_token(t_lexer **tokens, t_lexer *new_token);
t_lexer		*create_tok(char *data, t_token type);
char		*handle_quote(char *prompt);
char		*handle_single_quote(char *prompt);

// ERROR HANDLING
void		write_err(t_mini *minish, int code, char *arg);
void		write_simple_err(int code);
void		write_arg_err(int code, char *arg);

#endif