/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:37:40 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 20:37:41 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishelll.h"

char **dub_env(char **enviroment)
{
    char **new_env;
    size_t i;

    i = 0;
    //hapi i pare numrojme variablat
    if (!enviroment)
    {
        printf("no enviroment\n");
    }
    while (enviroment[i])
    {
        i++;
    }
    //alokojme memorie per enviromentin e ri
    new_env = malloc ((i + 1) * sizeof(char *));
    if (!new_env)
    {
        printf("alokimi i memorjes deshtoi");
        return NULL;
    }
    //kopjojme enviroment ne nje loop
    size_t j = 0;
    while (j < i)
    {
        new_env[j] = ft_strdup(enviroment[j]);
        if (!new_env)
        {
            printf("kopjimi i enviroment deshtoi");
            //beji free memorjes se alokuar
            while (j > 0)
            {
                free(new_env[j]);
                j--;
            }
            free(new_env);
            return(NULL);
        }
        j++;
    }
    new_env[j] = NULL;
    return(new_env);
}

void free_env(char **env)
{
    size_t i;

    i = 0;
    if (!env)
        return ;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}