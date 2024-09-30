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