/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:48:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/11 01:14:12 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"
/*
***		Mini SHELL
*** 
***
*** to do  
***	
***		PROMP 
***		HISTORY
***		PWD
***		'' -> handle single quote
***		"" -> handle double qoute
***		rederections
***		pipes
***		enviroment variables
***		$ -> handle dollar sign
***		This is the blue_print of the Minishell
***
*/

int	main(int ac, char *av[], char *envp[])
{
	t_msh	*minish;

	minish = init_minishell(ac, av, envp);
	prompt(minish);
}
