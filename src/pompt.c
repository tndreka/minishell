/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pompt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:58 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/10 16:47:09 by tndreka          ###   ########.fr       */
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
       // dont break from the minishell loop put error //
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

