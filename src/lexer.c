/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:08:19 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/11 01:26:26 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

void redirection(const char *prompt, t_lexer *current,
				 t_lexer **head, int *i);
void redirection_less(const char *prompt, t_lexer **head,
					  t_lexer **current, int *i);
void double_qoute(char *prompt, t_lexer **head, t_lexer **current, int *i);
void create_command(char *prompt, t_lexer **head, t_lexer **current, int *i);

t_lexer *tokenize_prompt(char *prompt)
{
	t_lexer *head;
	t_lexer *current;
	int i;

	head = NULL;
	current = NULL;
	i = 0;
	while (prompt[i])
	{
		while (prompt[i] && ft_isspace(prompt[i]))
			i++;
		if (prompt[i] == '|')
		{
			current = create_tok("|", PIPE);
			add_token(&head, current);
			i++;
		}
		else if (prompt[i] == '\"')
			double_qoute(prompt, &head, &current, &i);
		else if (prompt[i] == '>')
			redirection(prompt, current, &head, &i);
		else if (prompt[i] == '<')
			redirection_less(prompt, &head, &current, &i);
		else if (prompt[i])
			create_command(prompt, &head, &current, &i);
	}
	return head;
}

void	create_command(char *prompt, t_lexer **head, t_lexer **current, int *i)
{
	size_t len = 0;
	char *buffer;
	while (prompt[(*i)] && !ft_isspace(prompt[(*i)]) && prompt[(*i)] != '|' && prompt[(*i)] != '<' && prompt[(*i)] != '>')
	{
		len++;
		(*i)++;
	}
	buffer = malloc((len + 1) * sizeof(char));
	if (!buffer)
	{
		perror("malloc for buffer at lexer() FAILED !!");
		return;
	}
	ft_strncpy(buffer, prompt + ((*i) - len), len);
	buffer[len] = '\0';
	(*current) = create_tok(buffer, COMMAND);
	add_token(head, (*current));
	free(buffer);
}

void double_qoute(char *prompt, t_lexer **head, t_lexer **current, int *i)
{
	i++;
	char *tmp;
	char *quote_end;
	quote_end = ft_strchr((&prompt[(*i)]), '\"');
	if (quote_end)
	{

		tmp = handle_quote(&prompt[(*i)]);
		(*current) = create_tok(tmp, DOUBLE_QUOTE);
		add_token(head, (*current));
		free(tmp);
		(*i) = quote_end - prompt + 1;
	}
}

void redirection_less(const char *prompt, t_lexer **head, t_lexer **current, int *i)
{
	if (prompt[(*i) + 1] == '<')
	{
		(*current) = create_tok(create_redir_arr(prompt[(*i)]), HEREDOC);
		add_token(head, (*current));
		(*i) += 2;
	}
	else
	{
		(*current) = create_tok(create_redir_arr(prompt[(*i)]), REDIRIN);
		add_token(head, (*current));
		(*i)++;
	}
}

void redirection(const char *prompt, t_lexer *current, t_lexer **head, int *i)
{
	if (prompt[(*i) + 1] == '>')
	{
		current = create_tok(create_redir_arr(prompt[(*i)]), APPEND);
		add_token(head, current);
		(*i) += 2;
	}
	else
	{
		current = create_tok(create_redir_arr(prompt[(*i)]), REDIROUT);
		add_token(head, current);
		(*i)++;
	}
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
