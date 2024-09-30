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