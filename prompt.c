/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:37:16 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 20:37:17 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishelll.h"

char *create_prompt(void)
{
    char *prompt;
    
    prompt = malloc(13);
        if (!prompt)
        {
            perror("alocation of prompt memory has faild\n");
            return NULL;
        }
    ft_strlcpy(prompt, "my_shell~>", 11);
    return prompt;
}