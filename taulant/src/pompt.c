/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pompt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:58 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/14 13:51:15 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

/*
	Here its where we start our shell loop//
	1->checking if the input comes wrom a interactiv terminal
	2-> the input its saved in prompt
*/
void	prompt(t_msh *msh)
{
	char	*prompt;

	if (!isatty(STDIN_FILENO))
		return ;
	while (1)
	{
		prompt = readline("Minishell~ ");
		// if (prompt == NULL)
		// {
		// 	break ;
		// }
		minishell_parser(prompt, msh);
		printf("after parser\n");
		if (msh->table && handle_redirections(msh) != -1)
		{
			printf("before execution\n");
			if (!msh->table->rightpipe && check_builtin(msh))
				executor(msh);
			else
				mini_main(msh);
		}
		restore_redirections(msh);
		if (msh->table_head)
			free_table(msh);
	}
	free_mini(msh, false);
}

//		}}
//		tokens = lexer(prompt);
// free tokens
//		if(tokens)
//		{
//			print_token(tokens);
//			free_token(tokens);
//		}
//		if(ft_strncmp(prompt, "env", 4) == 0) // print the env
//		{
//			while (msh->env[i])
//			{
//				printf("%s\n", msh->env[i]);
//				i++;
//			}
//		}