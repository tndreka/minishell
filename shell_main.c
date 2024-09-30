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
        //free(msh.prompt);
    }
    return 0;
}