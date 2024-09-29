#include "minishelll.h"

char **dub_env(char **enviroment)
{
    char **new_env;
    size_t i;

    i = 0;
    //hapi i pare numrojme variablat
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
        new_env[j] = NULL;
    }
    return(new_env);
}