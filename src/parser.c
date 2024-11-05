/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:09:14 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/05 14:35:11 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"


t_lexer *check_prompt(char *prompt, t_msh *msh);

t_lexer *tokenize_prompt(char *prompt, t_msh *msh);


void minishell_parser(char *prompt, t_msh *msh)
{
    t_lexer     *token_list = NULL;
    t_lexer     *headof_list;
    t_table     *table = NULL;
    (void)msh;

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
        i = pass_to_table(&token_list, msh, &table);
        if (-1 == i)
        {
            free_everything(msh, headof_list, table);
            break;
        }
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

int pass_to_table(t_lexer **token_list, t_msh *msh, t_table **table)
{
    t_lexer     *token;
    t_cmd       *new_command;
       
    token = (*token_list);
    new_command = malloc(sizeof(t_cmd));
    if (NULL == new_command)
    {
        printf("allocation of the new_command failed\n");
        return -1;
    }
    new_command->next = NULL;
    if (token->type == COMMAND)
    {
        new_command->content = ft_strdup(token->data);
        if(NULL == new_command)
        {
            free(new_command);
            return -1;
        }
    }
}