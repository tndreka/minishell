#include "minishelll.h"

void start_shell(t_shell *msh)
{
    t_shell msh;
    char cwd[1042]; //buffer per direktorin aktuale
    char prompt = "my_shell~";

    while (1)
    {
        //Marr direktorin aktuale
        if (getcwd(cwd, sizeof(cwd) != NULL))
        {
            /* code */
        }
        
    }
    

}

