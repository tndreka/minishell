/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:13:02 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/14 13:50:44 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

bool	trip_to_table_pipe(t_lexer *token, t_table *table, t_msh *msh)
{
	t_table		*new_node;
	t_table		*current;

	(void)msh;
	//printf("here at pipe function\n");
	check_valid_pipe(token, table);
	//printf("before malloc\n");
	current = table;
	while (current && current->next)
		current = current->next;
	//printf("after loop\n");
	new_node = malloc(sizeof(t_table));
	if (new_node == NULL)
		return (false);
	//printf("after malloc\n");
	new_node->leftpipe = true;
	new_node->rightpipe = false;
	new_node->next = NULL;
	new_node->command = NULL;
	//printf("after new node\n");
	if (current)
	{
		current->rightpipe = true;
		current->next = new_node;
	}
	else
		table = new_node;
	//printf("after if\n");
	return (true);
}

bool	check_valid_pipe(t_lexer *token, t_table *table)
{
	if (token->type == PIPE && token->next->type != COMMAND)
		return (false);
	else if (token->type == PIPE && !table)
		return (false);
	else if (token->type == PIPE && !token->next)
		return (false);
	return (true);
}
