
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

t_lexer         *check_prompt(char *prompt);
// int	handle_token(t_lexer **tkn_lst, t_msh *minish, t_table **table);
// int	check_valid_redir_input(t_lexer **token_lst, t_msh *minish);
// int	handle_heredoc(t_lexer **token_lst, t_msh *minish);
// int	check_valid_pipe(t_lexer *token_lst, t_table *table, t_msh *minish);
// void	expand_env_vars(char **content, t_msh *minish);
// bool	heredoc_loop(char *delimiter, int fd);

// void	free_parser(t_msh *minish, t_lexer *lst, t_table *table);
// void	free_table(t_msh *minish);
// void	free_cmd(t_cmd *cmd);
// void	free_tkn_lst(t_lexer *token_lst);
// void	add_token_to_table(t_table **table, t_lexer *token_lst);
// void	allocate_table(t_table **table, bool leftpipe);
// void	add_cmd_node(t_table **table, char *content);


// void	minishell_parser(char *prompt, t_msh *minish)
// {
// 	t_lexer		*tkn_lst;
// 	t_lexer		*lst_head;
// 	t_table		*table;
// 	int			i;

// 	table = NULL;
// 	i = 0;
// 	tkn_lst = tokenize_prompt(prompt);
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

// int	handle_token(t_lexer **tkn_lst, t_msh *minish, t_table **table)
// {
// 	int		i;
// 	t_lexer	*token;

// 	i = 0;
// 	token = (*tkn_lst);
// 	if (token->type == REDIROUT || token->type == REDIROUTAPP || token->type == REDIRIN)
// 		i = check_valid_redir_input(tkn_lst, minish);
// 	else if (token->type == COMMAND || token->type == DOUBLE_QUOTE)
// 		expand_env_vars(&(*tkn_lst)->data, minish);
// 	else if (token->type == HEREDOC)
// 		i = handle_heredoc(tkn_lst, minish);
// 	else if (token->type == PIPE)
// 		i = check_valid_pipe(*tkn_lst, *table, minish);
// 	if (i == -1)
// 		return (i);
// 	add_token_to_table(table, *tkn_lst);
// 	return (i);
// }

// int	check_valid_redir_input(t_lexer **token_lst, t_msh *minish)
// {
// 	if ((*token_lst)->next == NULL)
// 		return -1;
// 		//return (write_err(minish, 8, NULL), -1);
// 	else if ((*token_lst)->next->type != COMMAND)
// 		return -1;
// 		//return (write_err(minish, 9, (*token_lst)->next->data), -1);
// 	if ((*token_lst)->type == REDIRIN)
// 	{
// 		if (minish->in_redir)
// 			free(minish->in_redir);
// 		minish->in_redir = ft_strdup((*token_lst)->next->data);
// 	}
// 	else if ((*token_lst)->type == REDIROUT || (*token_lst)->type == REDIROUTAPP)
// 	{
// 		if (minish->out_redir)
// 			free(minish->out_redir);
// 		minish->out_redir = ft_strdup((*token_lst)->next->data);
// 	}
// 	(*token_lst)->next->type = FILENAME;
// 	if ((*token_lst)->type == REDIROUTAPP)
// 		minish->append_mode = true;
// 	return (0);
// }

// int	handle_heredoc(t_lexer **token_lst, t_msh *minish)
// {
// 	char	*delimiter;
// 	int		fd;

// 	fd = -1;
// 	if (!(*token_lst)->next)
// 		return -1;
// 		//return (write_err(minish, 13, NULL), -1);
// 	else if ((*token_lst)->next->type != STRING)
// 		return -1;
// 		//return (write_err(minish, 14, (*token_lst)->next->data), -1);
// 	else
// 		(*token_lst)->next->type = DELIMITER;
// 	delimiter = ft_strdup((*token_lst)->next->data);
// 	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return -1;
// 		//return (write_err(minish, 15, NULL), -1);
// 	while (heredoc_loop(delimiter, fd))
// 		;
// 	minish->in_redir = ft_strdup(".heredoc_tmp");
// 	free(delimiter);
// 	delimiter = NULL;
// 	close(fd);
// 	return (0);
// }

// int	check_valid_pipe(t_lexer *token_lst, t_table *table, t_msh *minish)
// {
// 	(void)minish;
// 	if (token_lst->type == PIPE && !table)
// 	{
// 		//write_err(minish, 11, token_lst->data);
// 		return (-1);
// 	}
// 	else if (token_lst->type == PIPE && !token_lst->next)
// 	{
// 		//write_err(minish, 10, NULL);
// 		return (-1);
// 	}
// 	else if (token_lst->type == PIPE && token_lst->next->type != COMMAND)
// 	{
// 		//write_err(minish, 12, token_lst->next->data);
// 		return (-1);
// 	}
// 	return (0);
// }


// void	add_token_to_table(t_table **table, t_lexer *token_lst)
// {
// 	t_table	*new_node;
// 	t_table	*current_node;
// 	t_lexer	*token;

// 	new_node = NULL;
// 	current_node = NULL;
// 	token = token_lst;
// 	if (token->type == COMMAND || token->type == DOUBLE_QUOTE || token->type == SINGLE_QUOTE)
// 	{
// 		if (!(*table))
// 			allocate_table(table, false);
// 		current_node = *table;
// 		while (current_node->next)
// 			current_node = current_node->next;
// 		add_cmd_node(&current_node, token_lst->data);
// 	}
// 	else if (token_lst->type == PIPE)
// 	{
// 		current_node = *table;
// 		while (current_node->next)
// 			current_node = current_node->next;
// 		current_node->rightpipe = true;
// 		allocate_table(&new_node, true);
// 		current_node->next = new_node;
// 	}
// }

// void	allocate_table(t_table **table, bool leftpipe)
// {
// 	*table = malloc(sizeof(t_table));
// 	if (!(*table))
// 		return ;
// 	if (leftpipe == true)
// 		(*table)->leftpipe = true;
// 	else
// 		(*table)->leftpipe = false;
// 	(*table)->rightpipe = false;
// 	(*table)->next = NULL;
// 	(*table)->command = NULL;
// }

// void	add_cmd_node(t_table **table, char *content)
// {
// 	t_cmd	*new_node;
// 	t_cmd	*current_node;

// 	new_node = NULL;
// 	current_node = NULL;
// 	new_node = malloc(sizeof(t_cmd));
// 	if (!new_node)
// 		return ;
// 	new_node->content = ft_strdup(content);
// 	new_node->next = NULL;
// 	if (!(*table)->command)
// 	{
// 		(*table)->command = new_node;
// 		(*table)->cmd_head = new_node;
// 	}
// 	else
// 	{
// 		current_node = (*table)->command;
// 		while (current_node->next != NULL)
// 			current_node = current_node->next;
// 		current_node->next = new_node;
// 	}
// }
// void	free_tkn_lst(t_lexer *token_lst)
// {
// 	t_lexer	*current;
// 	t_lexer	*next;

// 	current = token_lst;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->data)
// 			free(current->data);
// 		free(current);
// 		current = next;
// 	}
// }
// void	free_parser(t_msh *minish, t_lexer *lst, t_table *table)
// {
// 	free_tkn_lst(lst);
// 	if (table)
// 	{
// 		minish->table_head = table;
// 		free_table(minish);
// 	}
// }

// bool	heredoc_loop(char *delimiter, int fd)
// {
// 	char	*line;

// 	line = NULL;
// 	line = readline("heredoc> ");
// 	if (ft_strcmp(line, delimiter) == 0)
// 	{
// 		free(line);
// 		line = NULL;
// 		return (false);
// 	}
// 	write(fd, line, strlen(line));
// 	write(fd, "\n", 1);
// 	free(line);
// 	line = NULL;
// 	return (true);
// }

// size_t          pass_to_table(t_lexer **token_list, t_msh *msh, t_table **table);
// size_t          trip_to_table_pipe(t_lexer *token, t_table *table);
// size_t          handle_type_of_redir(t_lexer *token, t_msh *msh);
// size_t          handle_type_of_redir_type2(t_lexer *token, t_msh *msh);
// void	        expand_env_vars(char **content, t_msh *minish);
// size_t          loop(char *separator, int fd);
// void            add_tokens_to_table(t_table *table, t_lexer *token);
// void            create_table(t_table **table, bool leftpipe);
// void            create_cmd_table(t_table **table, char *data);
// void	        expand_env_vars(char **content, t_msh *minish);

void minishell_parser(char *prompt, t_msh *msh)
{
    t_lexer     *token_list = NULL;
    t_lexer     *headof_list;
    t_table     *table = NULL;
    int         i;

    i = 0;
	(void)msh;
    token_list = check_prompt(prompt);
    headof_list = token_list;
    if(NULL == token_list)
        return;
   	// if (token_list)
   	// {
   	// 	print_token(token_list);
   	// }
    while (token_list)
    {
      i = handle_token(&token_list, msh, &table);
		// printf("hello i is : %zu\n", i);
		if (i == -1)
 		{
 			free_parser(msh, headof_list, table);
 			return ;
 		}
		token_list = token_list->next;
    }
    msh->table = table;
    msh->table_head = table;
}

t_lexer *check_prompt(char *prompt)
{
    t_lexer             *head;

    head = NULL;
    if(ft_strlen(prompt) > 0)
        add_history(prompt);
    head = tokenize_prompt(prompt);
    return (head);
}

// size_t pass_to_table(t_lexer **token_list, t_msh *msh, t_table **table)
// {
//     t_lexer *token;
//     size_t count;

//     token = *token_list;
//     count = 0;
//     while(token != NULL)
//     {
//         if(token->type== PIPE)
//         {
//             trip_to_table_pipe(token, *table);
//             //    return count;
//         }
//         else if (token->type == REDIRIN || token->type ==  REDIROUT || token->type == REDIROUTAPP)
//         {
// 			handle_type_of_redir(token, msh);
//             // err = 
// 			// if err == -1
// 			// 	print err
// 			// 	frre 
// 			// 	break;
//         }
//         else if (token->type == HEREDOC)
//         {	
//             handle_type_of_redir_type2(token, msh);
//             //    return count;
//         }
//         else if (token->type == COMMAND || token->type == DOUBLE_QUOTE)
// 		    expand_env_vars(&token->data, msh);
		
//         add_tokens_to_table(*table, token);
// 		printf("table: %s\n", token->data);
//         count++;
//         token = token->next;
//     }
//     return count;
// }

// size_t trip_to_table_pipe(t_lexer *token, t_table *table)
// {

//     if(token->type == PIPE && !table)
//         return -1;
//     else if(token->type == PIPE && token->next->type != STRING)
//         return -1;
//     else if (token->type == PIPE && !token->next)
//         return -1;
//     else
//         return 0;
// }

// size_t handle_type_of_redir(t_lexer *token, t_msh *msh)
// {
//     if(token->next == NULL)
//         return -1;
//     else if(token->next->type != STRING)
//         return -1;
//     else if(token->type == REDIRIN)
//     {
//         if(msh->in_redir)
//             free(msh->in_redir);
//         msh->in_redir = ft_strdup(token->next->data);
//     }
//     else if(token->type == REDIROUT || token->type == REDIROUTAPP)
//     {
//         if(msh->out_redir)
//             free(msh->out_redir);
//         msh->out_redir = ft_strdup(token->next->data);
//     }
//     token->next->type = FILENAME;
//     if (token->type == REDIROUTAPP)
//         msh->append_mode = true;
//     return 0;
// }

// size_t handle_type_of_redir_type2(t_lexer *token, t_msh *msh)
// {
//     int         fd;
//     char        *separator;

//     fd = -1;
//     if(!token->next)
//         return -1;
//     else if(token->next->type != STRING)
//         return -1;
//     else
//         token->next->type = DELIMITER;
//     separator = ft_strdup(token->next->data);
//     fd = open(".heredoc_tempo", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd < 0)
//         return -1;
//     while(loop(separator, fd))
//         ;
//     msh->in_redir = ft_strdup("heredoc_tempo");
//     free(separator);
//     separator = NULL;
//     close(fd);
//     return 0;
// }

// size_t loop(char *separator, int fd)
// {
//     char *here;

//     here = NULL;
//     here = readline(" >");
//     if (ft_strcmp(here, separator) == 0)
//     {
//         free(here);
//         here = NULL;
//         return -1;
//     }
//     else
//     {
//      write(fd, here, ft_strlen(here));
//      write(fd, "\n", 1);
//      free(here);
//      here = NULL;
//      return 0;
//     }
// }

// void add_tokens_to_table(t_table *table, t_lexer *token)
// {
//     t_table *new_node;
//     t_table *current;
//     t_lexer *current_token;

//     new_node = NULL;
//     current = NULL;
//     current_token = token;
//     if(current_token->type == STRING || current_token->type == DOUBLE_QUOTE)
//     {
//         if(!table)
//             create_table(&table, false);
//         current = current->next;
//         create_cmd_table(&current, current_token->data);
//     }
//     else if(current_token->type == PIPE)
//     {
//         current = table;
//         while(current->next)
//             current = current->next;
//         current->rightpipe = true;
//         create_table(&new_node, true);
//         current->next = new_node;
//     }
// }

// void create_table(t_table **table, bool leftpipe)
// {
//     *table = malloc(sizeof(t_table));
//     if(!table)
//         return;
//     if(leftpipe == true)
//     {
//         (*table)->leftpipe = true;
//     }
//     else
//         (*table)->leftpipe = false;
//     (*table)->rightpipe = false;
//     (*table)->next = NULL;
//     (*table)->command = NULL;
// }

// void create_cmd_table(t_table **table, char *data)
// {
//     t_cmd  	*node;
//     t_cmd   *current;

//     node = NULL;
//     current = NULL;
//     node = malloc(sizeof(t_cmd));
//     if (!node)
//         return;
//     node->content = ft_strdup(data);
//     node->next = NULL;
//     if(!(*table)->command)
//     {
//         (*table)->command = node;
//         (*table)->cmd_head = node;
//     }
//     else
//     {
//         current = (*table)->command;
//         while(current->next != NULL)
//             current = current->next;
//         current->next = node;
//     }
// }

// void	expand_env_vars(char **content, t_msh *minish)
// {
//     char	*expanded_string;

//     expanded_string = NULL;
//     while (1)
//     {
//         expanded_string = check_string(content, minish);
//         if (!expanded_string)
//             break ;
//         else
//         {
//             free(*content);
//             (*content) = ft_strdup(expanded_string);

//             free(expanded_string);
//             expanded_string = NULL;
//         }
//     }
// }