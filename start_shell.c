#include "minishelll.h"

void shell_loop(t_shell *msh)
{

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
        if( ft_strncmp(msh->input, "exit", 4) == 0 )
        {
            
            free(msh->input);
            free(msh->prompt);
            break ;
        }
        if (msh->input)
            add_history(msh->input);
        printf("print command line : %s\n", msh->input);        
        free(msh->input);
        if(msh->prompt)
            free(msh->prompt);
    }
}

