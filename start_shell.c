/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:37:05 by tndreka           #+#    #+#             */
/*   Updated: 2024/10/04 20:48:48 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishelll.h"

void shell_loop(t_shell *msh)
{
	t_token *tokens;
	size_t i = 0;
    while (1)
    {
        if(isatty(STDIN_FILENO))
        {
            msh->prompt = create_prompt();
            if(!msh->prompt)
            {
                perror("prompt loop failed\n");
                break;
            }

        }
        else
            msh->prompt = NULL;
        msh->input = readline(msh->prompt);
        if (msh->input == NULL) 
        {      
            free(msh->prompt);
            break ;
        }
		if(ft_strncmp(msh->prompt, "env", 4) == 0) // print the env 
		{
			while (msh->env[i])
			{
				printf("%s\n", msh->env);
				i++;
			}
		}
        if( ft_strncmp(msh->input, "exit", 4) == 0 )
        {
            
            free(msh->input);
            free(msh->prompt);
            break ;
        }
        if (msh->input)
            add_history(msh->input);
        //printf("print command line : %s\n", msh->input);        
		tokens = lexer(msh->input);
		if(tokens)
		{
			free_token(tokens);
		}
        free(msh->input);
        if(msh->prompt)
            free(msh->prompt);
    }
}

