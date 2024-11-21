/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:09:14 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/21 17:54:37 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

bool	token_to_table(t_lexer **token, t_table **table, t_msh *msh);
bool	trip_to_table_pipe(t_lexer *token, t_table *table, t_msh *msh);
bool	check_valid_pipe(t_lexer *token, t_table *table);
void 	print_table_commands(t_table *table);

void	minishell_parser(char *prompt, t_msh *msh)
{
	t_lexer	*token;
	//t_lexer	*head;
	t_table	*table;

	(void)msh;
	token = lexer(prompt);
	if(token)
	{
		print_token(token);
	}
	table = NULL;
	if (!token)
		return ;
	// while (token)
	// {
	// 	if(token_to_table(&token, &table, msh) == false)
	// 	{
	// 		printf("Error\n");
	// 		return ;
	// 	}
	// 	token = token->next;
	// }
	msh->table = table;
	msh->table_head = table;
	//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~printing table commands ********\n");
	print_table_commands(table);
	//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ finishing printing table commands ********\n");


}

bool	token_to_table(t_lexer **token, t_table **table, t_msh *msh)
{
	t_lexer	*temp;

	temp = *token;
	if (temp->type == PIPE)
	{
		printf("before adding pipe to table\n");
		if (trip_to_table_pipe(*token, *table, msh) == false)
		{
			printf("false pipe");
			return (false);
		}
		printf("token pipe added to table\n");
		//printf("here3\n");
	}
	else if (temp->type == COMMAND)
	{
	//	printf("=++++++++++++++++++ INSIDE IF COMMAND +++++++++++++++++++\n");
		if (trip_to_table_commad(*token, *table, msh) == false)
		{
	//		printf("!!!!!!!!!! COMMAND false main table function !!!!!!!!!!!!!\n");
			return (false);
			// printf("here444444444\n");
		}
	//	printf("@@@@@@@@@@@@@@@@ token command added to table @@@@@@@@@@@@@@@\n");
		// printf("here555555555\n");
	}
	//printf("=============== true ==========!!\n");
	return (true);
}

void print_table_commands(t_table *table)
{
    t_table *current = table;
	//printf("PRINTING TABLE CMMANDS\n");
    while (current)
    {
	//	printf("PRINTING TABLE CMMANDS debug\n");
        if (current->command)
        {
     //       printf("Command: %s\n", current->command->content);
        }
        current = current->next;
    }
}