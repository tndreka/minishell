/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:41:30 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/11 17:40:24 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

/*
	lexer()
	t
*/


t_lexer *lexer(char *prompt)
{
	char *buffer;
	t_lexer *head = NULL;
	t_lexer *current = NULL;
	size_t len = 0;
    //quotes
    char *tmp;
    char *quote_end;
    int i = 0;
	int quote_length = 0;

	while (prompt[i])
	{
		while (prompt[i] && ft_isspace(prompt[i]))
			i++;
        if(prompt[i] == '\"') {
			quote_end = ft_strchr((&prompt[i])+1, '\"');
            if (quote_end)
            {
                quote_length = quote_end - (prompt + i);
                tmp = handle_quote(&prompt[i]);
			    current = create_tok("\"", TOKEN_DOUBLE_QUOTE_STRING);
                add_token(&head, current);
			    free(tmp);
                i = quote_end - prompt + 1;
            }
		}
		else if(prompt[i] == '|')
		{
			current = create_tok("|", TOKEN_PIPE);
			add_token(&head, current);
			i++;
		}
		else if (prompt[i] == '>')
		{
			if (prompt[i + 1] == '>')
			{
				current = create_tok(create_redir_arr(prompt[i]), TOKEN_RIDIRECTION_GREAT_GREAT);
				add_token(&head, current);
				i += 2;
			}
			else
			{
				current = create_tok(create_redir_arr(prompt[i]), TOKEN_RIDIRECTION_GREAT);
				add_token(&head, current);
				i++;
			}
		}
		else if (prompt[i] == '<')
		{
			if (prompt[i + 1] == '<')
			{
				current = create_tok(create_redir_arr(prompt[i]), TOKEN_RIDIRECTION_LESS_LESS);	
				add_token(&head, current);
				i += 2;
			}
			else
			{
				current = create_tok(create_redir_arr(prompt[i]), TOKEN_RIDIRECTION_LESS);
				add_token(&head, current);	
				i++;
			}
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
			add_token(&head, current);
			free(buffer);
		}
	}
	return head;	
}

void free_token(t_lexer *head)
{
	t_lexer *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->data);
		free(tmp);
	}
}