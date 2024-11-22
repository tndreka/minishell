/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:43:06 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/22 18:52:21 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

// t_lexer	*lexer(char *prompt, t_mini *msh)
// {
// 	t_lexer			*head;
// 	t_lexer			*current;
// 	t_lexer_params	param;
// 	int				i;

// 	param.prompt = prompt;
// 	param.head = &head;
// 	param.current = &current;
// 	param.i = &i;
// 	param.msh = msh;
// 	head = NULL;
// 	current = NULL;
// 	i = 0;
// 	if (prompt[0] != '\0')
// 		add_history(prompt);
// 	handle_token(&param);
// 	while (prompt[i])
// 	{
// 		while (prompt[i] && ft_isspace(prompt[i]))
// 			i++;
// 		handle_token(&param);
// 		if (prompt[i])
// 			i++;
// 	}
// 	return (head);
// }

t_lexer	*process_input(char *line, t_mini *mini)
{
	t_lexer		*token_lst_head;
	char		*content;
	int			quote_type;
	t_token		type;

	token_lst_head = NULL;
	quote_type = 0;
	if (line[0] != '\0')
		add_history(line);
	content = get_next_token(line, &quote_type, mini);
	while (content != NULL)
	{
		if (content[0] == '\0')
		{
			free_tkn_lst(token_lst_head);
			return (NULL);
		}
		type = identify_token(content, quote_type);
		add_tkn_to_lst(&token_lst_head, content, type);
		free(content);
		content = get_next_token(line, &quote_type, mini);
	}
	return (token_lst_head);
}

char	*get_next_token(char *line, int *quote_type, t_mini *mini)
{
	static int	index = 0;
	int			start;
	char		*token;

	start = index;
	token = NULL;
	while (line[index] && ft_isspace(line[index]))
		index++;
	if (line[index] == '"' || line[index] == '\'')
		token = handle_quote(mini, quote_type, &index, line);
	else
	{
		start = index;
		while (line[index] && !ft_isspace(line[index]))
			index++;
		if (index > start)
			token = ft_strndup(line + start, index - start);
		else
			index = 0;
	}
	return (token);
}

char	*handle_quote(t_mini *mini, int *quote_type, int *index, char *line)
{
	char	quote;
	int		start;
	char	*token;

	set_quote_type(quote_type, line[*index]);
	quote = line[(*index)++];
	start = *index;
	token = NULL;
	while (line[*index] && line[*index] != quote)
		(*index)++;
	if (line[*index] == quote)
	{
		token = ft_strndup(line + start, (*index) - start);
		(*index)++;
		return (token);
	}
	else
	{
		write_err(mini, 16, NULL);
		*index = 0;
		return ("\0");
	}
}

void	add_tkn_to_lst(t_lexer **list_head, char *content, t_token token)
{
	t_lexer	*new_token;
	t_lexer	*current;

	current = NULL;
	new_token = create_new_node(content, token);
	if (!new_token)
		return ;
	if (*list_head == NULL)
		*list_head = new_token;
	else
	{
		current = *list_head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}
