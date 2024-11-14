/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:30:21 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/14 14:16:01 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

void print_table_commands(t_table *table);


bool	trip_to_table_commad(t_lexer *token, t_table *table, t_msh *msh)
{
	t_lexer		*temp;
	t_table		*new_node;
	int			cmd_len;

	(void)msh;
	temp = token;
	printf("here at count command function\n");
	if (count_allocate_commands(&temp, &new_node, &cmd_len) == false)
	{
		printf("false count allocate\n");
		return(false);
	}
	printf("before the function to add command to the table\n");
	if (add_command_in_table(new_node, table, cmd_len, token) == false)
	{
		printf("false add command to TABBLE\n");
		return(false);
	}
	printf("EVERYTHING IS OK\n");
	return (true);
}

bool	count_allocate_commands(t_lexer **temp, t_table **new_node,
					int *cmd_len)
{
	printf("here INSIDE count allocate function\n");
	*cmd_len = 0;
	printf("before while\n");
	while ((*temp) && (*temp)->type == COMMAND)
	{
		(*cmd_len)++;
		(*temp) = (*temp)->next;
	}
	printf("after while\n");
	printf("cmd_len = %d\n", *cmd_len);
	printf("before malloc\n");
	(*new_node) = malloc(sizeof(t_table));
	if (!(*new_node)){
		printf("after malloc false\n");
		return (false);}
	printf("alloc new_node\n");
	(*new_node)->command = malloc(sizeof(char *) * ((*cmd_len) + 1));
	if (!(*new_node)->command)
	{
		printf("after malloc false\n");
		free(new_node);
		return (false);
	}
	printf ("malloc success\n");
	(*new_node)->next = NULL;
	(*new_node)->rightpipe = false;
	(*new_node)->leftpipe = false;
	(*new_node)->cmd_head = NULL;
	printf("==================  TRUE ++++ count & malloc SUCCESS ==================\n");
	return (true);
}

bool	add_command_in_table(t_table *new_node, t_table *table, int cmd_len, t_lexer *token)
{
	t_lexer		*tempo = NULL;
	t_table		*current;
	int			i;

	i = 0;
	tempo = token;
	if (tempo)
	{
		print_token(tempo);
	}
	printf("----------------here at add command to table function----------------------\n");
	printf("cmd_len = %d\n", cmd_len);
	printf("before while\n");
	while (tempo && tempo->next && i < cmd_len)
	{
		printf("\n");
		printf("inside while\n");
		new_node->command[i].content = ft_strdup(tempo->data);
		printf("the DATA iis : %s\n", tempo->data);
		printf("the CONTENT is : %s\n", new_node->command[i].content);
		if (!new_node->command[i].content)
        {
            // Free previously allocated memory in case of failure
            while (i > 0)
            {
				free(new_node->command[--i].content);
            }
            free(new_node->command);
            free(new_node);
			printf("false strdup\n");
            return (false);
        }
	//	new_node->command[i].next = NULL;
		tempo = tempo->next;
		i++;
	}
	printf("====== after while ===========\n");
	new_node->command[i].content = NULL;
	printf("====== before if =========\n");
	if (table)
	{
		current = table;
            printf(" *********** Command: **************%s\n", current->command->content);
		while (current->next)
		{
			current = current->next;

		}
		current->next = new_node;
		printf("~~~~~~~~~~~~~~~~~~~~ after while of putting to table ~~~~~~~~~~~~~~~~~~~~\n");
	}
	else
	{
		printf("======= before while of putting to table ------- \n");
		table = new_node;
		printf("======= after while of putting to table ------- %s\n", new_node->command->content);
		printf("======= after if of putting to table ------ %s\n", table[0].command->content);
	}
	printf("++++++++++ TRUE ++++ add command to table SUCCESS +++++++++++\n");
	printf("---------- PRINTING TABLE CMMANDS ----------- \n");
	print_table_commands(table);
	return (true);
}


