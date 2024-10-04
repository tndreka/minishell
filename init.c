/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:37:31 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 20:37:32 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishelll.h"

int init_shell(t_shell *msh, char **enviroment)
{
        printf("Starting environment duplication...\n");
    msh->env =  dub_env(enviroment);
    if (!msh->env)
    {
        printf("failed to dublicate the enviroment");
        return 1;
    }
        printf(" environment duplication succesful...\n");
    return(0);
}