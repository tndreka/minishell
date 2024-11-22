/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/22 19:48:02 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	parse_input(char *line, t_mini *minish)
{
	t_tkn_lst	*tkn_lst;
	t_tkn_lst	*lst_head;
	t_table	*table;
	int		i = 0;

	table = NULL;
	tkn_lst = process_input(line, minish);
	lst_head = tkn_lst;
	if (!tkn_lst)
		return ;
	while (tkn_lst)
	{
		i = handle_token(&tkn_lst, minish, &table);
		{
			if (i == -1)
			{
				free_parser(minish, lst_head, table);
				return ;
			}
		}
		tkn_lst = tkn_lst->next;
	}
	minish->table = table;
	minish->table_head = table;
}
// void	parse_input(char *line, t_mini *minish)
// {
// 	t_tkn_lst	*tkn_lst;
// 	t_tkn_lst	*lst_head;
// 	t_table		*table;
// 	int			i;

// 	table = NULL;
// 	i = 0;
// 	tkn_lst = process_input(line, minish);
// 	lst_head = tkn_lst;
// 	if (!tkn_lst)
// 		return ;
// 	while (tkn_lst)
// 	{
// 		i = handle_token(&tkn_lst, minish, &table);
// 		if (i == -1)
// 		{
// 			free_parser(minish, lst_head, table);
// 			return ;
// 		}
// 		tkn_lst = tkn_lst->next;
// 	}
// 	free_tkn_lst(lst_head);
// 	minish->table = table;
// 	minish->table_head = table;
// }


 bool	handle_token(t_tkn_lst **tkn_lst, t_mini *minish, t_table **table)
{
 	if ((*tkn_lst)->tkn == STRING || (*tkn_lst)->tkn == DOUBLE_QUOTE)
// 	{
 		expand_env_vars(&(*tkn_lst)->content, minish);
// 		add_token_to_table(table, *tkn_lst);
// 	}
 	// else if ((*tkn_lst)->tkn == PIPE)
 	// {
 	// 	if (!handle_pipe(*tkn_lst, minish, *table))
 	// 		return (false);
 	// }
// 	else if ((*tkn_lst)->tkn == REDIRIN || (*tkn_lst)->tkn == REDIROUT
// 		|| (*tkn_lst)->tkn == REDIROUTAPP)
// 	{
// 		if (!handle_redir(tkn_lst, minish, table))
// 			return (false);
// 	}
// 	else if ((*tkn_lst)->tkn == HEREDOC)
// 	{
// 		if (!handle_heredoc(tkn_lst, minish, table))
// 			return (false);
 		add_token_to_table(table, *tkn_lst);
// 	}
 	return (true);
}
// int	handle_token(t_tkn_lst **tkn_lst, t_mini *minish, t_table **table)
// {
// 	int		i;
// 	t_tkn	token;

// 	i = 0;
// 	token = (*tkn_lst)->tkn;
// 	// if (token == REDIROUT || token == REDIROUTAPP || token == REDIRIN)
// 	// 	i = check_valid_redir_input(tkn_lst, minish);
// 	// else 
// 	if (token == STRING || token == DOUBLE_QUOTE)
// 		expand_env_vars(&(*tkn_lst)->content, minish);
// 	// else if (token == HEREDOC)
// 	// 	i = handle_heredoc(tkn_lst, minish);
// 	// else if (token == PIPE)
// 	// 	i = check_valid_pipe(*tkn_lst, *table, minish);
// 	if (i == -1)
// 		return (i);
// 	add_token_to_table(table, *tkn_lst);
// 	return (i);
// }

// int	check_valid_redir_input(t_tkn_lst **token_lst, t_mini *minish)
// {
// 	if ((*token_lst)->next == NULL)
// 		return (write_err(minish, 8, NULL), -1);
// 	else if ((*token_lst)->next->tkn != STRING)
// 		return (write_err(minish, 9, (*token_lst)->next->content), -1);
// 	if ((*token_lst)->tkn == REDIRIN)
// 	{
// 		if (minish->in_redir)
// 			free(minish->in_redir);
// 		minish->in_redir = ft_strdup((*token_lst)->next->content);
// 	}
// 	else if ((*token_lst)->tkn == REDIROUT || (*token_lst)->tkn == REDIROUTAPP)
// 	{
// 		if (minish->out_redir)
// 			free(minish->out_redir);
// 		minish->out_redir = ft_strdup((*token_lst)->next->content);
// 	}
// 	(*token_lst)->next->tkn = FILENAME;
// 	if ((*token_lst)->tkn == REDIROUTAPP)
// 		minish->append_mode = true;
// 	return (0);
// }

// int	handle_heredoc(t_tkn_lst **token_lst, t_mini *minish)
// {
// 	char	*delimiter;
// 	int		fd;

// 	fd = -1;
// 	if (!(*token_lst)->next)
// 		return (write_err(minish, 13, NULL), -1);
// 	else if ((*token_lst)->next->tkn != STRING)
// 		return (write_err(minish, 14, (*token_lst)->next->content), -1);
// 	else
// 		(*token_lst)->next->tkn = DELIMITER;
// 	delimiter = ft_strdup((*token_lst)->next->content);
// 	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (write_err(minish, 15, NULL), -1);
// 	while (heredoc_loop(delimiter, fd))
// 		;
// 	minish->in_redir = ft_strdup(".heredoc_tmp");
// 	free(delimiter);
// 	delimiter = NULL;
// 	close(fd);
// 	return (0);
// }

// int	check_valid_pipe(t_tkn_lst *token_lst, t_table *table, t_mini *minish)
// {
// 	if (token_lst->tkn == PIPE && !table)
// 	{
// 		write_err(minish, 11, token_lst->content);
// 		return (-1);
// 	}
// 	else if (token_lst->tkn == PIPE && !token_lst->next)
// 	{
// 		write_err(minish, 10, NULL);
// 		return (-1);
// 	}
// 	else if (token_lst->tkn == PIPE && token_lst->next->tkn != STRING)
// 	{
// 		write_err(minish, 12, token_lst->next->content);
// 		return (-1);
// 	}
// 	return (0);
// }
bool	check_valid_pipe(t_tkn_lst *token, t_table *table, t_mini *minish)
{
	if (token->next == NULL)
		return (write_err(minish, 10, NULL), false);
	else if (token->next->tkn != STRING)
		return (write_err(minish, 11, token->next->content), false);
	else if (token->tkn == PIPE && !table)
		return (write_err(minish, 12, NULL), false);
	return (true);
}

bool	handle_pipe(t_tkn_lst *token, t_mini *minish, t_table *table)
{
	t_table	*node;
	t_table	*current;

	check_valid_pipe(token, table, minish);
	current = table;
	while (current && current->next)
		current = current->next;
	node = malloc(sizeof(t_table));
	if (!node)
		return (write_err(minish, 6, NULL), false);
	node->leftpipe = true;
	node->rightpipe = false;
	node->command = NULL;
	node->next = NULL;
	if (current)
	{
		current->rightpipe = true;
		current->next = node;
	}
	else
		table = node;
	return (true);
}
bool	handle_redir(t_tkn_lst **token, t_mini *minish, t_table **table)
{
	if ((*token)->next == NULL)
		return (write_err(minish, 8, NULL), false);
	else if ((*token)->next->tkn != STRING)
		return (write_err(minish, 9, (*token)->next->content), false);
	if ((*token)->tkn == REDIRIN)
	{
		if (minish->in_redir)
			free(minish->in_redir);
		minish->in_redir = ft_strdup((*token)->next->content);
	}
	else if ((*token)->tkn == REDIROUT || (*token)->tkn == REDIROUTAPP)
	{
		if (minish->out_redir)
			free(minish->out_redir);
		minish->out_redir = ft_strdup((*token)->next->content);
	}
	(*token)->next->tkn = FILENAME;
	if ((*token)->tkn == REDIROUTAPP)
		minish->append_mode = true;
	add_redir_to_table(token, table);
	return (true);
}
void	add_redir_to_table(t_tkn_lst **token, t_table **table)
{
	t_table	*new_node;
	t_table	*current_node;

	new_node = NULL;
	current_node = NULL;
	if ((*token)->tkn == STRING || (*token)->tkn == DOUBLE_QUOTE
		|| (*token)->tkn == SINGLE_QUOTE)
	{
		if (!(*table))
			allocate_table(table, false);
		current_node = *table;
		while (current_node->next)
			current_node = current_node->next;
		add_cmd_node(&current_node, (*token)->content);
	}
}

bool	open_the_fd(int *fd, t_mini *msh, char *separator)
{
	(*fd) = open(".temporary_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if ((*fd) < 0)
	{
		write_err(msh, 15, NULL);
		free(separator);
		return (false);
	}
	else
		return (true);
}


bool	check_valid_heredoc(t_tkn_lst **token, t_mini *msh, char **separator)
{
	if ((*token)->next == NULL)
		write_err(msh, 13, NULL);
	else if ((*token)->next->tkn != STRING)
	{
		write_err(msh, 14, ((*token)->next->content));
		return (false);
	}
	else
		(*token)->next->tkn = DELIMITER;
	(*separator) = ft_strdup((*token)->next->content);
	return (true);
}

bool	handle_heredoc(t_tkn_lst **token, t_mini *msh, t_table **table)
{
	char	*separator;
	char	*line;
	int		fd;

	line = NULL;
	fd = -1;
	(void)table;
	check_valid_heredoc(token, msh, &separator);
	open_the_fd(&fd, msh, separator);
	while (true)
	{
		line = readline("heredoc> ");
		if (ft_strcmp(line, separator) == 0)
		{
			free(line);
			break ;
		}
		write_line(fd, line);
		free(line);
	}
	msh->in_redir = ft_strdup(".temporary_heredoc");
	free(separator);
	close(fd);
	return (true);
}
void	write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}