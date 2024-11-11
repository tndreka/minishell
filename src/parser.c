
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
void          pass_to_table(t_lexer **token_list, t_msh *msh, t_table **table);
void          trip_to_table_pipe(t_lexer *token, t_table *table);
void          handle_type_of_redir(t_lexer *token, t_msh *msh);
void          handle_type_of_redir_type2(t_lexer *token, t_msh *msh);
void	        expand_env_vars(char **content, t_msh *minish);
size_t          loop(char *separator, int fd);
void            add_tokens_to_table(t_table **table, t_lexer *token);
void            create_table(t_table **table, bool leftpipe);
void            create_cmd_table(t_table **table, char *data);
void	        expand_env_vars(char **content, t_msh *minish);

void minishell_parser(char *prompt, t_msh *msh)
{
    t_lexer     *token_list;
    t_table     *table;

	table = NULL;
    token_list = tokenize_prompt(prompt);
    if(NULL == token_list)
        return;
    while (token_list)
    {
      pass_to_table(&token_list, msh, &table);
      token_list = token_list->next;
    }
    msh->table = table;
    msh->table_head = table;
}

void pass_to_table(t_lexer **token_list, t_msh *msh, t_table **table)
{
    t_lexer *token;

    token = *token_list;
    if(token->type== PIPE)
        trip_to_table_pipe(token, *table);
    else if (token->type == REDIRIN || token->type ==  REDIROUT || token->type == REDIROUTAPP)
		handle_type_of_redir(token, msh);
    else if (token->type == HEREDOC)
        handle_type_of_redir_type2(token, msh);
    else if (token->type == COMMAND || token->type == DOUBLE_QUOTE)
        expand_env_vars(&token->data, msh);	
    add_tokens_to_table(table, *token_list);
}

void trip_to_table_pipe(t_lexer *token, t_table *table)
{

    if(token->type == PIPE && !table)
        return;
    else if(token->type == PIPE && token->next->type != COMMAND)
        return;
    else if (token->type == PIPE && !token->next)
        return ;
}

void handle_type_of_redir(t_lexer *token, t_msh *msh)
{
    if(token->next == NULL)
        return ;
    else if(token->next->type != COMMAND)
        return ;
    else if(token->type == COMMAND)
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
}

void handle_type_of_redir_type2(t_lexer *token, t_msh *msh)
{
    int         fd;
    char        *separator;

    fd = -1;
    if(!token->next)
        return ;
    else if(token->next->type != COMMAND)
        return ;
    else
        token->next->type = DELIMITER;
    separator = ft_strdup(token->next->data);
    fd = open(".heredoc_tempo", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return ;
    while(loop(separator, fd))
        ;
    msh->in_redir = ft_strdup("heredoc_tempo");
    free(separator);
    separator = NULL;
    close(fd);
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

void add_tokens_to_table(t_table **table, t_lexer *token)
{
    t_table *new_node;
    t_table *current;
    t_lexer *current_token;

    new_node = NULL;
    current = NULL;
    current_token = token;
    if(current_token->type == COMMAND || current_token->type == DOUBLE_QUOTE)
    {
        if(!*table)
            create_table(table, false);
        current = *table;
        create_cmd_table(&current, current_token->data);
    }
    else if(current_token->type == PIPE)
    {
        current = *table;
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
