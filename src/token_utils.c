/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:01:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/10 21:38:55 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"
//Here are the helper functions for the token's

/*
	FUNTIONS that we need to recreate
	we need to create a token
	we need to look for special characters
	add token to te list of token
*/

int is_this(char c)
{
    return (c == '|' || c == '>' || c == '<');
}

/*
	this function creates a token
	and sets the token type
*/

t_token get_token_type(char c)
{
    if (c == '|')
        return PIPE;
    else if (c == '<')
        return REDIROUT;
    else if (c == '>')
        return REDIRIN;
    else if (ft_strncmp(&c, "<<", 2) == 0)
        return HEREDOC;
    else if (ft_strncmp(&c, ">>", 2) == 0)
        return  APPEND;
    else
        return UNKNOWN;
}


t_lexer *create_tok(char *data, t_token type)
{
    t_lexer *token;

    token = malloc (sizeof(t_lexer));
    if (token == NULL)
    {
        perror("Malloc for tokens failed--->create_tok()\n");
        return NULL;
    }
    token->data = ft_strdup(data);
    token->type = type;
    token->next = NULL;
    return (token);
}

void add_token(t_lexer **tokens, t_lexer *new_token)
{
    t_lexer *temp;

    if(!*tokens)
        *tokens = new_token;
    else
    {
        temp = *tokens;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_token;
    }
}

int ft_isspace(char c)
{
    return (c == ' ');
}

char *create_redir_arr(char c)
{
    char *arr;

    arr = malloc(2 * sizeof(char));
    if (!arr)
    {
        perror("malloc of red_arr failed->> create_red_arr[]");
        return NULL;
    }
    arr[0] = c;
    arr[1] = '\0';
    return arr;
}

void print_token(t_lexer *tokens)
{
    char *str;
    //printf("ERROR HERE\n");
    while (tokens)
    {
        //printf("ERROR HERE1\n");
        if (tokens->type == COMMAND)
        {
            //printf("ERROR HERE2\n");
            str = "COMMAND";
        }
        else if (tokens->type == PIPE)
        {
            //printf("ERROR HERE3\n");
            str = "PIPE";
        }
        else if (tokens->type == REDIROUT)
        {
            //printf("ERROR HERE4\n");
            str = "RIDIRECTION_OUT";
        }
        else if (tokens->type == REDIRIN)
        {
            //printf("ERROR HERE4\n");
            str = "RIDIRECTION_IN";
        }
        else if (tokens->type == APPEND)
        {
            //printf("ERROR HERE4\n");
            str = "APPEND";
        }
        else if (tokens->type == APPEND)
        {
            //printf("ERROR HERE4\n");
            str = "APPEND";
        }
        else
        {
            //printf("ERROR HERE5\n");
            str = "UNKNOWN";
        }
        //printf("ERROR HERE666\n");
        printf("Token : %s  Type: %s\n" , tokens->data, str);
        tokens = tokens->next;
    }
}
