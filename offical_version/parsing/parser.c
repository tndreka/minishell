/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/18 02:16:43 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
bool	pass_token_to_table(t_lexer **token, t_mini *minish, t_table **table);
bool	handle_redir(t_lexer **token, t_mini *minish, t_table **table);
//** This function will call the lexer function and pass the tokens to the parser
void	minishell_parser(char *prompt, t_mini *msh)
{
	t_lexer		*tkn_lst;
	t_lexer		*lst_head;
	t_table		*table;

	table = NULL;
	tkn_lst = lexer(prompt);
	lst_head = tkn_lst;
	if (!tkn_lst)
		return ;
	while (tkn_lst)
	{
		if (!pass_token_to_table(&tkn_lst, msh, &table))
		{
			printf("Error\n");
			free_parser(msh, lst_head, table);
			return ;
		}
		tkn_lst = tkn_lst->next;
	}
	msh->table = table;
	msh->table_head = table;
}
//======== pAss tO tAblE FuNctiOns =========
//** This function will check the type of the token and call the appropriate
bool	pass_token_to_table(t_lexer **token, t_mini *minish, t_table **table)
{	
    if ((*token)->data == NULL)
        return false;
    if ((*token)->type == STRING || (*token)->type == DOUBLE_QUOTE || (*token)->type == SINGLE_QUOTE)
    {
        exp_env_vars(&(*token)->data, minish);
		add_token_to_table(table, *token);	
    }
	else if ((*token)->type == PIPE)
		handle_pipe(*token, minish, *table);
	else if ((*token)->type == REDIRIN || (*token)->type == REDIROUT || (*token)->type == REDIROUTAPP)
    {
        handle_redir(token, minish, table);
    }
	return (true);
}

//==============================================================================

// int	check_valid_redir_input(t_lexer **token_lst, t_mini *minish)
// {
// 	int	fd;

// 	fd = 0;
// 	if ((*token_lst)->next == NULL)
// 		return (write_err(minish, 8, NULL), -1);
// 	else if ((*token_lst)->next->type != STRING)
// 		return (write_err(minish, 9, (*token_lst)->next->data), -1);
// 	if ((*token_lst)->type == REDIRIN)
// 	{
// 		if (minish->in_redir)
// 			free(minish->in_redir);
// 		minish->in_redir = ft_strdup((*token_lst)->next->data);
// 	}
// 	else if ((*token_lst)->type == REDIROUT || (*token_lst)->type == REDIROUTAPP)
// 	{
// 		if (minish->out_redir)
// 		{
// 			fd = open(minish->out_redir, O_CREAT, 0644);
// 			if (fd < 0)
// 				return (write_err(minish, 7, NULL), -1);
// 			close(fd);
// 			free(minish->out_redir);
// 		}
// 		minish->out_redir = ft_strdup((*token_lst)->next->data);
// 	}
// 	(*token_lst)->next->type = FILENAME;
// 	if ((*token_lst)->type == REDIROUTAPP)
// 		minish->append_mode = true;
// 	return (0);
// }
// int	handle_heredoc(t_lexer **token_lst, t_mini *minish)
// {
// 	char	*delimiter;
// 	int		fd;

// 	fd = -1;
// 	if (!(*token_lst)->next)
// 		return (write_err(minish, 13, NULL), -1);
// 	else if ((*token_lst)->next->type != STRING)
// 		return (write_err(minish, 14, (*token_lst)->next->data), -1);
// 	else
// 		(*token_lst)->next->type = DELIMITER;
// 	delimiter = ft_strdup((*token_lst)->next->data);
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
//============================================================================


//================== PIPE =================================================
bool check_valid_pipe(t_lexer *token, t_table *table, t_mini *minish)
{
	if(token->next == NULL)
		return (write_err(minish, 10, NULL), false);
	else if (token->next->type != STRING)
		return (write_err(minish, 11, token->next->data), false);
	else if (token->type == PIPE && !table)
		return (write_err(minish, 12, NULL), false);
	return (true);
}

bool handle_pipe(t_lexer *token, t_mini *minish, t_table *table)
{	
	t_table *node;
	t_table *current;
	
	check_valid_pipe(token, table, minish);
	current = table;
	while(current && current->next)
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
//===================================================================================

//=============================== COMMANF & ENV_VAR =================================

// bool exp_env_vars(char **content, t_mini *msh)
// {
// 	char *expanded_string;
// 	char *prefix;
// 	int i = 0;	
// 	// int j = 0;
// 	(void)msh;	
// 	// expanded_string = ft_strdup("");
// 	while((*content)[i])
// 	{
// 		while ((*content)[i] && (*content)[i] != '$')
// 			i++;
// 		prefix = ft_strndup(*content, i);
// 		expanded_string = ft_strjoin(expanded_string, prefix);
// 		free(prefix);
// 	}
// 	return (true);
// }
// bool exp_env_vars(char **content, t_mini *minish)
// {
//     char *expanded_string;
//     char *env;
//     int i, j;
//     char *temp, *temp2;

//     expanded_string = NULL;
//     while (1)
//     {
//         i = 0;
//         env = NULL;
//         expanded_string = NULL;
        
//         // Check string and expand environment variables
//         while ((*content)[i] && (*content)[i] != '$')
//             i++;
//         if (!(*content)[i])
//             break;
        
//         expanded_string = ft_strndup(*content, i);
//         i++;
//         if ((*content)[i] == '?')
//         {
//             env = ft_itoa(minish->exit_code);
//             i++;
//         }
//         else
//         {
//             j = 0;
//             temp = NULL;
//             while ((*content)[i])
//             {
//                 if (ft_isalnum((*content)[i]) == 1 || (*content)[i] == '_')
//                 {
//                     i++;
//                     j++;
//                 }
//                 else
//                     break;
//             }
//             temp2 = ft_strndup((*content) + (i - j), j);
//             temp = ft_getenv(minish, temp2);
//             free(temp2);
//             temp2 = NULL;
//             env = temp;
//         }
        
//         if (env)
//             replace_varname_wtih_var(&expanded_string, &env);
//         if ((*content)[i])
//             append_remainder(&expanded_string, content, i);

//         // Update content
//         if (!expanded_string)
//             break;
//         else
//         {
//             free(*content);
//             (*content) = ft_strdup(expanded_string);
//             free(expanded_string);
//             expanded_string = NULL;
//         }
//     }
// 	return (true);
// }
//------------------- full function -------------------
// bool exp_env_vars(char **content, t_mini *minish)
// {
//     char *expanded_string;
//     char *env;
//     int i, j;
//     char *temp, *temp2;

//     expanded_string = NULL;
//     while (1)
//     {
//         i = 0;
//         env = NULL;
//         expanded_string = NULL;

//         // Find the next '$' in the content
//         while ((*content)[i] && (*content)[i] != '$')
//             i++;
//         if (!(*content)[i])
//             break;

//         // Duplicate the string up to the '$'
//         expanded_string = ft_strndup(*content, i);
//         i++;
//         if ((*content)[i] == '?')
//         {
//             env = ft_itoa(minish->exit_code);
//             i++;
//         }
//         else
//         {
//             j = 0;
//             temp = NULL;
//             while ((*content)[i])
//             {
//                 if (ft_isalnum((*content)[i]) == 1 || (*content)[i] == '_')
//                 {
//                     i++;
//                     j++;
//                 }
//                 else
//                     break;
//             }
//             temp2 = ft_strndup((*content) + (i - j), j);
//             temp = ft_getenv(minish, temp2);
//             free(temp2);
//             temp2 = NULL;
//             env = temp;
//         }

//         // Replace variable name with its value
//         if (env)
//         {
//             temp = ft_strdup(expanded_string);
//             free(expanded_string);
//             expanded_string = ft_strjoin(temp, env);
//             free(temp);
//             free(env);
//             env = NULL;
//         }

//         // Append the remainder of the string
//         if ((*content)[i])
//         {
//             temp = ft_strdup(expanded_string);
//             free(expanded_string);
//             expanded_string = ft_strjoin(temp, (*content) + i);
//             free(temp);
//         }

//         // Update content
//         if (!expanded_string)
//             break;
//         else
//         {
//             free(*content);
//             (*content) = ft_strdup(expanded_string);
//             free(expanded_string);
//             expanded_string = NULL;
//         }
//     }
// 	return (true);
// }

//===================================================================================

//========================== REDIRECTIONS ===========================================
bool handle_redir(t_lexer **token, t_mini *minish, t_table **table)
{
	t_table	*current_node;
	// new_node = NULL;
	// current_node = NULL;
	if ((*token)->next == NULL)
		return (write_err(minish, 8, NULL), false);
	else if ((*token)->next->type != STRING)
		return (write_err(minish, 9, (*token)->next->data), false);
	if ((*token)->type == REDIRIN)
	{
		if (minish->in_redir)
			free(minish->in_redir);
		minish->in_redir = ft_strdup((*token)->next->data);
	}
	else if ((*token)->type == REDIROUT || (*token)->type == REDIROUTAPP)
	{
		if (minish->out_redir)
			free(minish->out_redir);
		minish->out_redir = ft_strdup((*token)->next->data);
	}
	(*token)->next->type = FILENAME;
	if ((*token)->type == REDIROUTAPP)
		minish->append_mode = true;
	if ((*token)->type == STRING || (*token)->type == DOUBLE_QUOTE || (*token)->type == SINGLE_QUOTE)
	{
		if (!(*table))
			create_table(table, false);
		current_node = *table;
		while (current_node->next)
			current_node = current_node->next;
		create_cmd_table(&current_node, (*token)->data);
	}
	return (true);
}
// ==================================================================================

//======================== HEREDOC ==================================================
