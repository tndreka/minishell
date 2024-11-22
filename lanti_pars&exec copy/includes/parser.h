/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:32:53 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/22 19:44:14 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "lexer.h"
# include <stdbool.h>
# include <fcntl.h>
//=====org======
// // MAIN PARSING FUNCTIONS
void	parse_input(char *line, t_mini *minish);
//int		handle_token(t_tkn_lst **tkn_lst, t_mini *minish, t_table **table);
// int		check_valid_redir_input(t_tkn_lst **token_lst, t_mini *minish);
// int		handle_heredoc(t_tkn_lst **token_lst, t_mini *minish);
// bool	heredoc_loop(char *delimiter, int fd);
// int		check_valid_pipe(t_tkn_lst *tkn_lst, t_table *table, t_mini *minish);
char	*check_string(char **content, t_mini *minish);
void	expand_env_vars(char **content, t_mini *minish);
char	*check_and_expand_env(char **content, int *i, t_mini *minish);

// // PARSING UTILS
int		ft_strcmp(char *s1, char *s2);
char	*ft_getenv(t_mini *minish, char	*env);
char	**copy_env(char **envp);
void	append_remainder(char **expanded_string, char **content, int pos);
void	replace_varname_wtih_var(char **expanded_string, char **temp);

// // STRUCT CREATION
void	add_token_to_table(t_table **table, t_tkn_lst *token_lst);
void	add_cmd_node(t_table **table, char *content);
void	allocate_table(t_table **table, bool leftpipe);

// FREEING 
 void	free_table(t_mini *minish);
 void	free_cmd(t_cmd *cmd);
 void	free_parser(t_mini *minish, t_tkn_lst *lst, t_table *table);
// ==================================================================
bool	handle_token(t_tkn_lst **tkn_lst, t_mini *minish, t_table **table);
bool	check_valid_pipe(t_tkn_lst *token, t_table *table, t_mini *minish);
bool	handle_pipe(t_tkn_lst *token, t_mini *minish, t_table *table);
bool	handle_redir(t_tkn_lst **token, t_mini *minish, t_table **table);
void	add_redir_to_table(t_tkn_lst **token, t_table **table);
bool	open_the_fd(int *fd, t_mini *msh, char *separator);
bool	check_valid_heredoc(t_tkn_lst **token, t_mini *msh, char **separator);
bool	handle_heredoc(t_tkn_lst **token, t_mini *msh, t_table **table);
void	write_line(int fd, char *line);
#endif