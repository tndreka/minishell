
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
size_t          pass_to_table(t_lexer **token_list, t_msh *msh, t_table **table);
size_t          trip_to_table_pipe(t_lexer *token, t_table *table);
size_t          handle_type_of_redir(t_lexer *token, t_msh *msh);
size_t          handle_type_of_redir_type2(t_lexer *token, t_msh *msh);
void	        expand_env_vars(char **content, t_msh *minish);
size_t          loop(char *separator, int fd);
void            add_tokens_to_table(t_table *table, t_lexer *token);
void            create_table(t_table **table, bool leftpipe);
void            create_cmd_table(t_table **table, char *data);
void	        expand_env_vars(char **content, t_msh *minish);

void minishell_parser(char *prompt, t_msh *msh)
{
    t_lexer     *token_list = NULL;
    t_lexer     *headof_list;
    t_table     *table = NULL;
    size_t         i;

    i = 0;
    token_list = check_prompt(prompt);
    headof_list = token_list;
    if(NULL == token_list)
        return;
//    if (token_list)
//    {
//    print_token(token_list);
//    }
    // while (token_list)
    // {
        i = pass_to_table(&token_list, msh, &table);
		// printf("hello i is : %zu\n", i);

	// 	token_list = token_list->next;
    // }
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

size_t pass_to_table(t_lexer **token_list, t_msh *msh, t_table **table)
{
    t_lexer *token;
    size_t count;

    token = *token_list;
    count = 0;
    while(token != NULL)
    {
        if(token->type== PIPE)
        {
            trip_to_table_pipe(token, *table);
            //    return count;
        }
        else if (token->type == REDIRIN || token->type ==  REDIROUT || token->type == REDIROUTAPP)
        {
			handle_type_of_redir(token, msh);
            // err = 
			// if err == -1
			// 	print err
			// 	frre 
			// 	break;
        }
        else if (token->type == HEREDOC)
        {	
            handle_type_of_redir_type2(token, msh);
            //    return count;
        }
        else if (token->type == STRING || token->type == DOUBLE_QUOTE)
		    expand_env_vars(&token->data, msh);
		
        add_tokens_to_table(*table, token);
		printf("table: %s\n", token->data);
        count++;
        token = token->next;
    }
    return count;
}

size_t trip_to_table_pipe(t_lexer *token, t_table *table)
{

    if(token->type == PIPE && !table)
        return -1;
    else if(token->type == PIPE && token->next->type != STRING)
        return -1;
    else if (token->type == PIPE && !token->next)
        return -1;
    else
        return 0;
}

size_t handle_type_of_redir(t_lexer *token, t_msh *msh)
{
    if(token->next == NULL)
        return -1;
    else if(token->next->type != STRING)
        return -1;
    else if(token->type == REDIRIN)
    {
        if(msh->in_redir)
            free(msh->in_redir);
        msh->in_redir = ft_strdup(token->next->data);
    }
    else if(token->type == REDIROUT || token->type == REDIROUTAPP)
    {
        if(msh->out_redir)
            free(msh->out_redir);
        msh->out_redir = ft_strdup(token->next->data);
    }
    token->next->type = FILENAME;
    if (token->type == REDIROUTAPP)
        msh->append_mode = true;
    return 0;
}

size_t handle_type_of_redir_type2(t_lexer *token, t_msh *msh)
{
    int         fd;
    char        *separator;

    fd = -1;
    if(!token->next)
        return -1;
    else if(token->next->type != STRING)
        return -1;
    else
        token->next->type = DELIMITER;
    separator = ft_strdup(token->next->data);
    fd = open(".heredoc_tempo", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return -1;
    while(loop(separator, fd))
        ;
    msh->in_redir = ft_strdup("heredoc_tempo");
    free(separator);
    separator = NULL;
    close(fd);
    return 0;
}

size_t loop(char *separator, int fd)
{
    char *here;

    here = NULL;
    here = readline(" >");
    if (ft_strcmp(here, separator) == 0)
    {
        free(here);
        here = NULL;
        return -1;
    }
    else
    {
     write(fd, here, ft_strlen(here));
     write(fd, "\n", 1);
     free(here);
     here = NULL;
     return 0;
    }
}

void add_tokens_to_table(t_table *table, t_lexer *token)
{
    t_table *new_node;
    t_table *current;
    t_lexer *current_token;

    new_node = NULL;
    current = NULL;
    current_token = token;
    if(current_token->type == STRING || current_token->type == DOUBLE_QUOTE)
    {
        if(!table)
            create_table(&table, false);
        current = current->next;
        create_cmd_table(&current, current_token->data);
    }
    else if(current_token->type == PIPE)
    {
        current = table;
        while(current->next)
            current = current->next;
        current->rightpipe = true;
        create_table(&new_node, true);
        current->next = new_node;
    }
}

void create_table(t_table **table, bool leftpipe)
{
    *table = malloc(sizeof(t_table));
    if(!table)
        return;
    if(leftpipe == true)
    {
        (*table)->leftpipe = true;
    }
    else
        (*table)->leftpipe = false;
    (*table)->rightpipe = false;
    (*table)->next = NULL;
    (*table)->command = NULL;
}

void create_cmd_table(t_table **table, char *data)
{
    t_cmd  	*node;
    t_cmd   *current;

    node = NULL;
    current = NULL;
    node = malloc(sizeof(t_cmd));
    if (!node)
        return;
    node->content = ft_strdup(data);
    node->next = NULL;
    if(!(*table)->command)
    {
        (*table)->command = node;
        (*table)->cmd_head = node;
    }
    else
    {
        current = (*table)->command;
        while(current->next != NULL)
            current = current->next;
        current->next = node;
    }
}

void	expand_env_vars(char **content, t_msh *minish)
{
    char	*expanded_string;

    expanded_string = NULL;
    while (1)
    {
        expanded_string = check_string(content, minish);
        if (!expanded_string)
            break ;
        else
        {
            free(*content);
            (*content) = ft_strdup(expanded_string);

            free(expanded_string);
            expanded_string = NULL;
        }
    }
}