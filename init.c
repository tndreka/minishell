#include "minishelll.h"

int init_shell(char **enviroment)
{
    t_shell msh;
    msh.env =  dub_env(enviroment);
    if (!msh.env)
    {
        printf("failed to dublicate the enviroment");
        return 1;
    }
    return(0);
}