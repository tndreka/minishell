#include "minishelll.h"

int main (int ac, char **av, char **enviroment)
{
    t_shell msh;
    if (  ac > 1)
    {
        printf ("keni dhene me shume argumente\n");
    }
    else
    {
        //printf("vazhdoni me krijimin e shell\n");
        init_shell ( enviroment);
        shell_loop(&msh);
    }
    return 0;
}