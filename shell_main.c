/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:37:11 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 20:49:19 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishelll.h"

int main (int ac, char **av, char **enviroment)
{
    t_shell msh;
    (void)av;
    if (  ac > 1)
    {
        printf ("keni dhene me shume argumente\n");
    }
    else
    {
        //printf("vazhdoni me krijimin e shell\n");
        if (init_shell ( &msh, enviroment) != 0)
        {
            printf("failed to initialize\n");
            return 1;
        }
        shell_loop(&msh);
        free_env(msh.env);
    }
    return 0;
}