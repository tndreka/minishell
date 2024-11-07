/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pompt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baylozzi <baylozzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:58 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/05 13:38:05 by baylozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

/*
	Here its where we start our shell loop//
	1->checking if the input comes wrom a interactiv terminal
	2-> the input its saved in prompt
*/
void prompt(t_msh *msh)
{
    char	*prompt;
    if (!isatty(STDIN_FILENO))
        return ;
    while (1)
    {
        prompt = readline("Minishell~ ");
        if (prompt == NULL)
            break ;
        minishell_parser(prompt, msh);
        if (minish->table && handle_redirections(minish) != -1)
        {
            if (!minish->table->rightpipe && check_builtin(minish))
                executor(minish);
            else
                mini_main(minish);
        }
        restore_redirections(minish);
        if (minish->table_head)
            free_table(minish);
    }
    free_mini(minish, false);
    return (0);
}