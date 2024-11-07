/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:22:02 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/06 16:16:26 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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


t_lexer *check_prompt(char *prompt, t_msh *msh);

t_lexer *tokenize_prompt(char *prompt, t_msh *msh);

size_t pass_to_table(t_lexer *token_list, t_msh *msh, t_table **table);

size_t tri_to_table_pipe(t_lexer *token_list, t_msh *msh, t_table *table)

size_t handle_type_of_redir(t_lexer *token, t_msh *msh);

size_t handle_type_of_redir_type2(t_lexer *token, t_msh *msh)

void add_tokens_to_table(t_table *table, t_lexer *token);

void create_table(t_table **table, bool leftpipe);

size_t loop(char *separator, int fd);

void ceate_cmd_table(t_table **table, char *data);

void minishell_parser(char *prompt, t_msh *msh)
{
    t_lexer     *token_list = NULL;
    t_lexer     *headof_list;
    t_table     *table = NULL;
    size_t         i;

    i = 0;
    token_list = check_prompt(prompt, msh);
    headof_list = token_list;
    //token_list = lexer(prompt);
    if(NULL == token_list)
        return;
    if(!token_list)
    {
        return ;
        if (token_list)
        {
            print_token(token_list);
        }
    }
    while (token_list)
    {
        i = pass_to_table(token_list, msh, &table);
    }
    msh->table = table;
    msh->table_head = table;
}

t_lexer *check_prompt(char *prompt, t_msh *msh)
{
    t_lexer             *head;

    head = NULL;
    if(ft_strlen(prompt) > 0)
        add_history(prompt);
    head = tokenize_prompt(prompt, msh);
    return (head);
}

size_t pass_to_table(t_lexer *token_list, t_msh *msh, t_table **table)
{
    t_lexer *token;
    size_t count;

    token = *token_list->type;
    count = 0;

    while(token)
    {
        if(token->type == PIPE)
        {
            if(trip_to_table_pipe(token, *table) == -1) // need to write the error to themsh STDOUt//for all of the function//
                return count;
        }
        else if (token->type == REDIRIN || token->type ==  REDIROUT || token->type == REDIROUTAPP)
        }
            handle_type_of_redir(token, msh);
        {
        else if (token->type == HEREDOC)
        {
            if(handle_type_of_redir_type2(token, msh) == -1);
                return count;
        }
        else if (token == STRING || token == DOUBLE_QUOTE)
                expand_env_vars(&(*tkn_lst)->content, minish);
        else
            return count;

        add_tokens_to_table(table, token);
        count++;
        token = token->next
    }
    return count;
}

size_t trip_to_table_pipe(t_lexer *token ,t_table *table)
{
    if(token->type == PIPE && !table)
        return -1;
    else if(token->type == PIPE && token->next != STRING)
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
        token->next->type == DELIMITER;
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
        free(line);
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
    current_token = token->type;
    if(current_token == STRING || current_token == DOUBLE_QUOTE)
    {
        if(!table)
            create_table(table, false);
        current = current->next;
        create_cmd_table(&current, current_token->data);
    }
    else if(current_token == PIPE)
    {
        current = table;
        while(current->next)
            current = current->next;
        current->leftpipe = true;
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
    (*table)->leftpipe = false;
    (*table)->next = NULL;
    (*table)->command = NULL;
}

void ceate_cmd_table(t_table **table, char *data)
{
    t_cmd  *node;
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
        (*table)->cmd_head = nodel;
    }
    else
    {
        current = (*table)->command;
        while(current->next != NULL)
            current = current->next;
        current->next = node;
    }
}
//{
//    t_lexer     *token;
//    t_cmd       *new_command;
//
//    (void)msh;
//    (void)table;
//    token = (*token_list);
//    new_command = malloc(sizeof(t_cmd));
//    if (NULL == new_command)
//    {
//        printf("allocation of the new_command failed\n");
//        return -1;
//    }
//    new_command->next = NULL;
//    if (token->type == COMMAND)
//    {
//        new_command->content = ft_strdup(token->data);
//        if(NULL == new_command)
//        {
//            free(new_command);
//            return -1;
//        }
//    }
//    else if (token->type == REDIRIN)
//    {
//        new_command->content = ft_strdup(token->data);
//        if (NULL == new_command)
//        {
//            free(new_command);
//            return -1;
//        }
//    }
//    else if (token->type == REDIROUT)
//    {
//        new_command->content = ft_strdup(token->data);
//        if (NULL == new_command)
//        {
//            free(new_command);
//            return -1;
//        }
//    }
//    else if (token->type == HEREDOC)
//    {
//        new_command->content = ft_strdup(token->data);
//        if (NULL == new_command)
//        {
//            free(new_command);
//            return -1;
//        }
//    }
//    else if (token->type == APPEND)
//    {
//        new_command->content = ft_strdup(token->data);
//        if (NULL == new_command)
//        {
//            free(new_command);
//            return -1;
//        }
//    }
//    else if (token->type == STRING)
//    {
//        new_command->content = ft_strdup(token->data);
//        if(NULL == new_command)
//        {
//            free(new_command);
//            return -1;
//        }
//    }
//    else if (token->type == PIPE)
//    {
//        if(NULL == new_command)
//
//            return -1;
//
//    }
//    return 0;
//}