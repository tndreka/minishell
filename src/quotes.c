/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:13:14 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/03 22:36:40 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_sh.h"

char *handle_quote(char *prompt)
{

	char *end;
	char *string;

	end = ft_strchr(prompt, 34);
    string = malloc(ft_strlen(prompt));
    if(!string)
    {
        perror("failed to allocate memory for the new string\n");
        return NULL;
    }
    if (prompt && end)
    {
        ft_memmove(string, prompt, end - prompt);
        string[end - prompt] = '\0';
    }
    else
    {
        perror("failed to find quotes || to move the string inside of quotes in to the result");
        return  NULL;
    }
    return(string);
}


//int main()
//{
//	char prompt;
//	size_t i = 0;
//
//	printf("Enter your input: ");
//	scanf("%s" , &prompt);
//	if(!prompt)
//	{
//		printf("Enter the input again");
//		scanf("%s" , &prompt);
//	}
//
//	printf("%s", handle_quote(&prompt));
//    return 0;
//}