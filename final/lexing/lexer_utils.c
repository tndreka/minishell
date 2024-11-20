/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:45:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/20 19:00:09 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	redirection(t_lexer_params *param)
{
	if (param->prompt[*(param->i) + 1] == '<')
	{
		*(param->current) = create_tok("<<", APPEND);
		add_token(param->head, *(param->current));
		(*(param->i)) += 2;
	}
	else
	{
		*(param->current) = create_tok("<", REDIROUT);
		add_token(param->head, (*(param->current)));
		(*(param->i))++;
	}
}

t_lexer	*create_tok(char *data, t_token type)
{
	t_lexer	*token;

	token = malloc(sizeof(t_lexer));
	if (token == NULL)
		return (NULL);
	token->data = ft_strdup(data);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_lexer **tokens, t_lexer *new_token)
{
	t_lexer	*temp;

	if (!*tokens)
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

char	*handle_quote(char *prompt)
{
	char	*end;
	char	*string;

	end = ft_strchr(prompt, 34);
	string = malloc(ft_strlen(prompt - 1));
	if (!string)
		return (NULL);
	if (prompt && end)
	{
		ft_memmove(string, prompt, end - prompt);
		string[end - prompt] = '\0';
	}
	return (string);
}

char	*handle_single_quote(char *prompt)
{
	char	*end;
	char	*string;

	end = ft_strchr(prompt, '\'');
	string = malloc(ft_strlen(prompt - 1));
	if (!string)
		return (NULL);
	if (prompt && end)
	{
		ft_memmove(string, prompt, end - prompt);
		string[end - prompt] = '\0';
	}
	return (string);
}
