
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:09:14 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/05 18:47:05 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

t_lexer	*tokenize_prompt(char *prompt);
bool		pass_to_table(t_lexer **token_list, t_msh *msh, t_table **table);
int		trip_to_table_pipe(t_lexer *token_lst, t_table *table, t_msh *msh);
int		handle_type_of_redir(t_lexer **token_lst, t_msh *msh);
int		handle_type_of_redir_type2(t_lexer **token_lst, t_msh *msh);
bool	expand_env_vars(char **content, t_msh *minish);
int		loop(char *separator, int fd);
void	add_tokens_to_table(t_table **table, t_lexer *token);
void	create_table(t_table **table, bool leftpipe);
void	create_cmd_table(t_table **table, char *data);
//void	expand_env_vars(char **content, t_msh *minish);
void	write_arg_err(int code, char *arg);
void	write_simple_err(int code);
void	write_err(t_msh *minish, int code, char *arg);

int checd_valid(t_lexer *token_lst, t_table *table, t_msh *msh);

void	minishell_parser(char *prompt, t_msh *msh)
{
	t_lexer	*tkn_lst;
	t_lexer	*lst_head;
	t_table		*table;
	//int			i;

	table = NULL;
	//i = 0;
	tkn_lst = tokenize_prompt(prompt);
	lst_head = tkn_lst;
	if (!tkn_lst)
		return ;
	while (tkn_lst)
	{
		if (!pass_to_table(&tkn_lst, msh, &table))
		{
			printf("Error\n");
			//free_parser(msh, lst_head, table);
			return ;
		}
		//i++;
		tkn_lst = tkn_lst->next;
	}
	msh->table = table;
	msh->table_head = table;
}
	// t_lexer	*token_list;
	// t_table	*table;

	// table = NULL;
	// token_list = tokenize_prompt(prompt);
	// if(token_list == NULL)
	// {
	// 	return ;
	// }
	// if(token_list)
	// 	print_token(token_list);
	// while (token_list)
	// {
	// 	pass_to_table(&token_list, msh, &table);
	// 	token_list = token_list->next;
	// }
	// msh->table = table;
	// msh->table_head = table;

bool	pass_to_table(t_lexer **tkn_lst, t_msh *msh, t_table **table)
{
	//int		i;
	t_token	token;

	//i = 0;
	token = (*tkn_lst)->type;
	//printf("Processing token type: %s\n", (char *)token);
	if(tkn_lst == NULL || *tkn_lst == NULL){
		 //printf("Error: tkn_lst or *tkn_lst is NULL\n");
		return (false);}
	if (token == REDIROUT || token == REDIROUTAPP || token == REDIRIN)
	{
		 //printf("Handling redirection token\n");
		if(handle_type_of_redir(tkn_lst, msh)){
			//printf("Error: handle_type_of_redir failed\n");
			return (false);}
	}	
	else if (token == COMMAND || token == DOUBLE_QUOTE)
	{
		 //printf("Handling command or double quote token\n");
		if(!expand_env_vars(&(*tkn_lst)->data, msh)){
			//printf("Error: expand_env_vars failed\n");
			return (false);}

	}
	else if (token == HEREDOC){
		//printf("Handling heredoc token\n");
		if(handle_type_of_redir_type2(tkn_lst, msh)){
			//printf("Error: handle_type_of_redir_type2 failed\n");
			return (false);}
		}
	else if (token == PIPE){
		//printf("Handling pipe token\n");
		if(trip_to_table_pipe(*tkn_lst, *table, msh)){
			//printf("Error: trip_to_table_pipe failed\n");
			return (false);}
		}
	// if (i == -1)
	// 	return (i);
	add_tokens_to_table(table, *tkn_lst);
	return (true);
}
	//t_lexer	*token;

	// token = *token_list;
	// if (token->type == PIPE)
	// 	trip_to_table_pipe(token, table);
	// else if (token->type == REDIRIN || token->type == REDIROUT
	// 	|| token->type == REDIROUTAPP)
	// 	handle_type_of_redir(token, msh);
	// else if (token->type == HEREDOC)
	// 	handle_type_of_redir_type2(token, msh);
	// else if (token->type == COMMAND || token->type == DOUBLE_QUOTE)
	// 	expand_env_vars(&token->data, msh);
	// add_tokens_to_table(table, *token_list);

int checd_valid(t_lexer *token_lst, t_table *table, t_msh *msh)
{
	if (token_lst->type == PIPE && !table)
	{
		write_err(msh, 11, token_lst->data);
		return (-1);
	}
	else if (token_lst->type == PIPE && !token_lst->next)
	{
		write_err(msh, 10, NULL);
		return (-1);
	}
	else if (token_lst->type == PIPE && token_lst->next->type != COMMAND)
	{
		write_err(msh, 12, token_lst->next->data);
		return (-1);
	}
	return (0);
}

int	trip_to_table_pipe(t_lexer *token_lst, t_table *table, t_msh *msh)
{
	t_table	*new_node;
	t_table	*current_node;

	checd_valid(token_lst, table, msh);
	current_node = table;
	while (current_node && current_node->next)
		current_node = current_node->next;
	new_node = malloc(sizeof(t_table));
	if (!new_node)
	{
		perror("malloc");
		return -1;
	}
	new_node->leftpipe = true;
	new_node->rightpipe = false;
	new_node->next = NULL;
	new_node->command = NULL;
	if (current_node)
	{
		current_node->rightpipe = true;
		current_node->next = new_node;
	}
	else
	{
		table = new_node;
	}
	return (0);
}
// }
// {
// 	if (token_lst->type == PIPE && !table)
// 	{
// 		write_err(msh, 11, token_lst->data);
// 		return (-1);
// 	}
// 	else if (token_lst->type == PIPE && !token_lst->next)
// 	{
// 		write_err(msh, 10, NULL);
// 		return (-1);
// 	}
// 	else if (token_lst->type == PIPE && token_lst->next->type != COMMAND)
// 	{
// 		write_err(msh, 12, token_lst->next->data);
// 		return (-1);
// 	}
// 	return (0);
	// if (token->type == PIPE && !table)
	// 	return (-1);
	// else if (token->type == PIPE && token->next->type != COMMAND)
	// 	return (-1);
	// else if (token->type == PIPE && !token->next)
	// 	return (-1);
	// add_pipe_to_table(table, token);
	// return (0);
//}

int	handle_type_of_redir(t_lexer **token_lst, t_msh *msh)
{
	if ((*token_lst)->next == NULL)
		return (write_err(msh, 8, NULL), -1);
	else if ((*token_lst)->next->type != COMMAND)
		return (write_err(msh, 9, (*token_lst)->next->data), -1);
	if ((*token_lst)->type == REDIRIN)
	{
		if (msh->in_redir)
			free(msh->in_redir);
		msh->in_redir = ft_strdup((*token_lst)->next->data);
	}
	else if ((*token_lst)->type == REDIROUT || (*token_lst)->type == REDIROUTAPP)
	{
		if (msh->out_redir)
			free(msh->out_redir);
		msh->out_redir = ft_strdup((*token_lst)->next->data);
	}
	(*token_lst)->next->type = FILENAME;
	if ((*token_lst)->type == REDIROUTAPP)
		msh->append_mode = true;
	return (0);
}
	// if (token->next == NULL)
	// 	return ;
	// else if (token->next->type != COMMAND)
	// 	return ;
	// else if (token->type == COMMAND)
	// {
	// 	if (msh->in_redir)
	// 		free(msh->in_redir);
	// 	msh->in_redir = ft_strdup(token->next->data);
	// }
	// else if (token->type == REDIROUT || token->type == REDIROUTAPP)
	// {
	// 	if (msh->out_redir)
	// 		free(msh->out_redir);
	// 	msh->out_redir = ft_strdup(token->next->data);
	// }
	// token->next->type = FILENAME;
	// if (token->type == REDIROUTAPP)
	// 	msh->append_mode = true;

int	handle_type_of_redir_type2(t_lexer **token_lst, t_msh *msh)
{
	int		fd;
	char	*separator;

	fd = -1;
	if (!(*token_lst)->next)
		return -1;
	else if ((*token_lst)->next->type != COMMAND)
		return -1;
	else
		(*token_lst)->next->type = DELIMITER;
	separator = ft_strdup((*token_lst)->next->data);
	fd = open(".heredoc_tempo", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return -1;
	while (loop(separator, fd))
		;
	msh->in_redir = ft_strdup("heredoc_tempo");
	free(separator);
	separator = NULL;
	close(fd);
	return (0);
}

int	loop(char *separator, int fd)
{
	char	*here;

	here = NULL;
	here = readline(" >");
	if (ft_strcmp(here, separator) == 0)
	{
		free(here);
		here = NULL;
		return (-1);
	}
	else
	{
		write(fd, here, ft_strlen(here));
		write(fd, "\n", 1);
		free(here);
		here = NULL;
		return (0);
	}
}

void	add_tokens_to_table(t_table **table, t_lexer *token_lst)
{
	t_table	*new_node;
	t_table	*current_node;
	t_token	token;

	new_node = NULL;
	current_node = NULL;
	token = token_lst->type;
	if (token == COMMAND || token == DOUBLE_QUOTE || token == SINGLE_QUOTE)
	{
		if (!(*table))
			create_table(table, false);
		current_node = *table;
		while (current_node->next)
			current_node = current_node->next;
		create_cmd_table(&current_node, token_lst->data);
	}
	// else if (token_lst->type == PIPE)
	// {
	// 	while (current_node->next)
	// 		current_node = current_node->next;
	// 	current_node->rightpipe = true;
	// 	create_table(&new_node, true);
	// 	current_node->next = new_node;
}
	// }
	// t_table	*new_node;
	// t_table	*current;
	// t_lexer	*current_token;

	// new_node = NULL;
	// current = NULL;
	// current_token = token;
	// if (current_token->type == COMMAND || current_token->type == DOUBLE_QUOTE)
	// {
	// 	if (!*table)
	// 		create_table(table, false);
	// 	current = *table;
	// 	create_cmd_table(&current, current_token->data);
	// }
	// else if (current_token->type == PIPE)
	// {
	// 	current = *table;
	// 	while (current->next)
	// 		current = current->next;
	// 	current->rightpipe = true;
	// 	create_table(&new_node, true);
	// 	current->next = new_node;

void	create_table(t_table **table, bool leftpipe)
{
	*table = malloc(sizeof(t_table));
	if (!(*table))
		return ;
	if (leftpipe == true)
		(*table)->leftpipe = true;
	else
		(*table)->leftpipe = false;
	(*table)->rightpipe = false;
	(*table)->next = NULL;
	(*table)->command = NULL;
}
	// *table = malloc(sizeof(t_table));
	// if (!table)
	// 	return ;
	// if (leftpipe == true)
	// {
	// 	(*table)->leftpipe = true;
	// }
	// else
	// 	(*table)->leftpipe = false;
	// (*table)->rightpipe = false;
	// (*table)->next = NULL;
	// (*table)->command = NULL;

void	create_cmd_table(t_table **table, char *data)
{
	t_cmd	*new_node;
	t_cmd	*current_node;

	new_node = NULL;
	current_node = NULL;
	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(data);
	new_node->next = NULL;
	if (!(*table)->command)
	{
		(*table)->command = new_node;
		(*table)->cmd_head = new_node;
	}
	else
	{
		current_node = (*table)->command;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
}
// 	t_cmd	*node;
// 	t_cmd	*current;

// 	node = NULL;
// 	current = NULL;
// 	node = malloc(sizeof(t_cmd));
// 	if (!node)
// 		return ;
// 	node->content = ft_strdup(data);
// 	node->next = NULL;
// 	if (!(*table)->command)
// 	{
// 		(*table)->command = node;
// 		(*table)->cmd_head = node;
// 	}
// 	else
// 	{
// 		current = (*table)->command;
// 		while (current->next != NULL)
// 			current = current->next;
// 		current->next = node;
// 	}

void	write_err(t_msh *minish, int code, char *arg)
{
	if (!arg)
		write_simple_err(code);
	else
	{
		if (code == 9 || code == 14 || code == 11 || code == 12)
		{
			write(STDERR_FILENO, "Minishell: syntax error ", 24);
			write(STDERR_FILENO, "near unexpected token `", 23);
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, "'\n", 2);
		}
		else if (code == 2 || code == 4 || code == 5)
		{
			write(STDERR_FILENO, "Minishell: cd: ", 15);
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, ": No such file or directory\n", 29);
		}
		else
			write_arg_err(code, arg);
	}
	minish->exit_code = code;
	minish->success = false;
}

void	write_simple_err(int code)
{
	if (code == 16)
	{
		write(STDERR_FILENO, "Minishell: synthax error: u", 27);
		write(STDERR_FILENO, "nmatched quote character\n", 26);
	}
	else if (code == 8 || code == 13 || code == 10)
	{
		write(STDERR_FILENO, "Minishell: syntax error near ", 29);
		write(STDERR_FILENO, "unexpected token `newline'\n", 28);
	}
	else if (code == 15)
	{
		write(STDERR_FILENO, "Minishell: Failed to ", 21);
		write(STDERR_FILENO, "create heredoc file\n", 21);
	}
	else if (code == 1 || code == 3)
		write(STDERR_FILENO, "Minishell: cd: HOME not set\n", 29);
	else if (code == 21)
		write(STDERR_FILENO, "Minishell: cd: OLDPWD not set\n", 31);
	else if (code == 17)
		write(STDERR_FILENO, "Minishell: exit: too many arguments\n", 36);
	else if (code == 7)
		write(STDERR_FILENO, "Minishell: Error opening output file\n", 38);
}

void	write_arg_err(int code, char *arg)
{
	if (code == 18)
	{
		write(STDERR_FILENO, "Minishell: exit: ", 17);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": numeric argument required\n", 29);
	}
	else if (code == 22 || code == 6)
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
	}
	else if (code == 23 || code == 24)
	{
		write(STDERR_FILENO, "Minishell: ", 11);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": command not found\n", 21);
	}
}