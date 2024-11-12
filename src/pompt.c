/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pompt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:58 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/11 14:40:21 by tndreka          ###   ########.fr       */
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
		// dont break from the minishell loop put error //
		//check_valid_input(prompt); ==> //to do --> check if the input is valid// check fot oprn pipe or ony pipe
		minishell_parser(prompt, msh);
		if (msh->table && handle_redirections(msh) != -1)
		{
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

// void check_valid_input(char *prompt)
// {
// 	int i;

// 	i = 0;
// 	while (prompt[i] != '\0')
// 	{
// 		while (isspace(prompt[i]))
// 			i++;
// 		if (prompt[i] == '|')
// 			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
// }