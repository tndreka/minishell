/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:36:22 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 20:40:08 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishelll.h"


t_token *lexer(char *prompt)
{
	char *buffer;
	t_token *head = NULL;
	t_token *current = NULL;
	size_t len = 0;
	int i = 0;

	while (prompt[i])
	{
		while (prompt[i] && ft_isspace(prompt[i]))
			i++;
		if(prompt[i] == '|')
		{
			current = create_tok("|", TOKEN_PIPE);
			i++;
		}
		else if (prompt[i] == '>' || prompt[i] == '<')
		{
			current = create_tok(create_redir_arr(prompt[i]), TOKEN_RIDIRECTION);
			i++;
		}
		else if (prompt[i])
		{
			len = 0;
			while (prompt[i] && !ft_isspace(prompt[i]) && prompt[i] != '|' && prompt[i] != '<' && prompt[i] != '<')
			{
				len++;
				i++;
			}
			buffer = malloc((len + 1) * sizeof(char));
			if(!buffer)
			{
				perror("malloc for buffer at lexer() FAILED !!");
				return NULL;
			
			}
			ft_strncpy(buffer, prompt + (i - len) , len);
			buffer[len] = '\0';
			current = create_tok(buffer, TOKEN_WORD);
			free(buffer);
		}
		if (current)
		{
			current->next = head;
			head = current;
		}
	}
	return head;	
}


void free_token(t_token *head)
{
	t_token *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->data);
		free(tmp);
	}
}

int is_this(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

/*
	this function creates a token 
	and sets the token type
*/

token_type get_token_type(char c)
{
	if (c == '|')
		return TOKEN_PIPE;
	if (c == '<' || c == '>')
		return TOKEN_RIDIRECTION;
	else
		return TOKEN_UNKNOWN;
}


t_token *create_tok(char *data, token_type type)
{
	t_token *token;

	token = malloc (sizeof(t_token));
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

void add_token(t_token **tokens, t_token *new_token)
{
	t_token *temp;
	
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