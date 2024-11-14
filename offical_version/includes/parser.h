/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:32:53 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/14 16:12:42 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "lexer.h"
# include <stdbool.h>
# include <fcntl.h>

// MAIN PARSING FUNCTIONS
// void	parse_input(char *line, t_mini *minish);
void	minishell_parser(char *prompt, t_mini *msh);
int		handle_token(t_lexer **tkn_lst, t_mini *minish, t_table **table);
int		check_valid_redir_input(t_lexer **token_lst, t_mini *minish);
int		handle_heredoc(t_lexer **token_lst, t_mini *minish);
bool	heredoc_loop(char *delimiter, int fd);
int		check_valid_pipe(t_lexer *tkn_lst, t_table *table, t_mini *minish);
char	*check_string(char **content, t_mini *minish);
void	expand_env_vars(char **content, t_mini *minish);
char	*check_and_expand_env(char **content, int *i, t_mini *minish);

// PARSING UTILS
int		ft_strcmp(char *s1, char *s2);
char	*ft_getenv(t_mini *minish, char	*env);
char	**copy_env(char **envp);
void	append_remainder(char **expanded_string, char **content, int pos);
void	replace_varname_wtih_var(char **expanded_string, char **temp);

// STRUCT CREATION
void	add_token_to_table(t_table **table, t_lexer *token_lst);
void	add_cmd_node(t_table **table, char *content);
void	allocate_table(t_table **table, bool leftpipe);

// FREEING 
void	free_table(t_mini *minish);
void	free_cmd(t_cmd *cmd);
void	free_parser(t_mini *minish, t_lexer *lst, t_table *table);
void	ft_free(char **content);

#endif