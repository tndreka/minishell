/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:44:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/17 17:38:26 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Taulant Ndreka on 07/11/2024.
//

#include "../include/mini_sh.h"


// void	exp_env_vars(char **content, t_msh *minish)
// {
// 	char	*expanded_string;

// 	expanded_string = NULL;
// 	while (1)
// 	{
// 		expanded_string = check_string(content, minish);
// 		if (!expanded_string)
// 			break ;
// 		else
// 		{
// 			free(*content);
// 			(*content) = ft_strdup(expanded_string);
// 			free(expanded_string);
// 			expanded_string = NULL;
// 		}
// 	}
// }
bool	exp_env_vars(char **content, t_msh *minish)
{
    int     i = 0;
    int     start = 0;
    char    *expanded_string = ft_strdup("");
    char    *env_value = NULL;
    char    *temp = NULL;
    
	printf("HERE\n");
    while ((*content)[i])  
    {
		 printf("Content: %s, Index: %d\n", *content, i);
		 fflush(stdout);
        while ((*content)[i] && (*content)[i] != '$')  // Look for '$' sign
            i++;
        
        if (!(*content)[i])  // If no more '$' signs are found, break out of the loop
            break;

        // Append the non-variable part to the expanded string
        temp = ft_strndup(*content, i);
        expanded_string = ft_strjoin(expanded_string, temp);
        free(temp);

        i++;  // Move past '$'

        // Check if it is '$?' for the exit code
        if ((*content)[i] == '?')
        {
			          printf("Detected $?\n");
            env_value = ft_itoa(minish->exit_code);  // Convert exit code to string
            expanded_string = ft_strjoin(expanded_string, env_value);
            free(env_value);  // Free the exit code string
            i++;  // Skip past the '?'
            continue;
        }
			
        // Otherwise, process an environment variable (e.g., $USER)
        start = i;
        while ((*content)[i] && (isalnum((*content)[i]) || (*content)[i] == '_'))  // Find the variable name
            i++;
        
        char *var_name = ft_strndup(*content + start, i - start);  // Extract the variable name
		 printf("Variable Name: %s\n", var_name);  // Debug print
        env_value = ft_getenv(minish, var_name);  // Get its value from the environment
        free(var_name);  // Free the variable name

        if (env_value)
        {
			  printf("Found Env Var Value: %s\n", env_value);
            expanded_string = ft_strjoin(expanded_string, env_value);  // Append the value to the expanded string
            free(env_value);  // Free the value
        }
		else{
			printf("env varnot found");
		}
    }

    // Append any remaining part of the content after the last '$'
    if ((*content)[i])
    {
        temp = ft_strjoin(expanded_string, *content + i);
        free(expanded_string);
        expanded_string = temp;
    }

    // Update the content with the expanded string and clean up
    free(*content);
    *content = expanded_string;
    
    return true;
}

//void	append_remainder(char **expanded_string, char **content, int pos)
// {
// 	char	*temp;

// 	//printf("append_remainder ==> before appending, expanded_string: %s, content: %s, pos: %d\n", *expanded_string, *content, pos);
// 	temp = ft_strdup(*expanded_string);
// 	free(*expanded_string);
// 	*expanded_string = ft_strjoin(temp, (*content) + pos);
// 	free(temp);
// 	temp = NULL;
// 	//printf("append_remainder ==> after appending, expanded_string: %s\n", *expanded_string);
// }

// void	replace_varname_wtih_var(char **expanded_string, char **env)
// {
// 	char	*temp;

// 	//printf("replace_varname_wtih_var ==> before replacing, expanded_string: %s, env: %s\n", *expanded_string, *env);
// 	temp = ft_strdup(*expanded_string);
// 	free(*expanded_string);
// 	*expanded_string = ft_strjoin(temp, *env);
// 	free(temp);
// 	free(*env);
// 	*env = NULL;
// 	temp = NULL;
// 	//printf("replace_varname_wtih_var ==> after replacing, expanded_string: %s\n", *expanded_string);
// }

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

char	*ft_getenv(t_msh *mini, char *env)
{
	size_t	i;
	int		len;
	char	*var;

	len = ft_strlen(env);
	i = -1;
	var = NULL;
	//printf("ft_getenv ==> looking for env variable: %s\n", env);
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], env, len) == 0 && mini->env[i][len] == '=')
		{
			var = ft_strdup(mini->env[i] + (len + 1));
			//printf("ft_getenv ==> found env variable: %s, value: %s\n", env, var);
			return (var);
		}
	}
	//printf("ft_getenv ==> env variable not found: %s\n", env);
	return (var);
}

char	**copy_env(char **envp)
{
	char	**cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	cpy = malloc(sizeof(char *) * (i + 1));
	cpy[i] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
		{
			cpy[j] = ft_strdup(envp[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	return (cpy);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n < 1)
		return (0);
	while (*s1 == *s2 && *s1 && *s2 && --n)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2 || n == 0)
		return (0);
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
// char	*check_and_expand_env(char **content, int *i, t_msh *minish)
// {
// 	int		j;
// 	char	*temp;
// 	char	*temp2;

// 	j = 0;
// 	temp = NULL;
// 	while ((*content)[*i])
// 	{
// 		if (ft_isalnum((*content)[*i]) == 1 || (*content)[*i] == '_')
// 		{
// 			(*i)++;
// 			j++;
// 		}
// 		else
// 			break ;
// 	}
// 	temp2 = ft_strndup((*content) + ((*i) - j), j);
// 	temp = ft_getenv(minish, temp2);
// 	free(temp2);
// 	temp2 = NULL;
// 	return (temp);
// }

// char	*check_string(char **content, t_msh *minish)
// {
// 	int		i;
// 	char	*expanded_string;
// 	char	*env;

// 	i = 0;
// 	env = NULL;
// 	expanded_string = NULL;
// //	 printf("check_string ==> starting\n");
// 	while ((*content)[i] && (*content)[i] != '$')
// 		i++;
// 	if (!(*content)[i])
// 	{
// 		printf("check_string ==> no $ found\n");
// 		return (NULL);
// 	}
// 	expanded_string = ft_strndup(*content, i);
// 	i++;
// 	if ((*content)[i] == '?')
// 	{
// 		env = ft_itoa(minish->exit_code);
// 		i++;
// 	}
// 	else
// 		env = check_and_expand_env(content, &i, minish);
// 	if (env)
// 		replace_varname_wtih_var(&expanded_string, &env);
// 	if ((*content)[i])
// 		append_remainder(&expanded_string, content, i);
// //	printf("check_string ==> returning expanded string: %s\n", expanded_string);
// 	return (expanded_string);
// }

// bool exp_env_vars(char **content, t_msh *msh)
// {
// 	char *expanded_string;
// 	char *prefix;
// 	char *env_ecit_code;
// 	char *variable_name;
// 	char *get_value;
// 	int i = 0;
// 	int start = 0;	

// 	(void )msh;
// 	expanded_string = ft_strdup("");
// 	while(*content[i])
// 	{
// 		while (*content[i] && *content[i] != '$')
// 			i++;
// 		if (!*content[i])
// 			break;
// 		prefix = ft_strndup(*content, i);
// 		expanded_string = ft_strjoin(expanded_string, prefix);
// 		free(prefix); // free prefix
// 		if (*content[i] == '?'){
// 			env_ecit_code = ft_itoa(msh->exit_code);
// 		expanded_string = ft_strjoin(expanded_string, env_ecit_code);
// 		i = i + 2;
// 		continue;
// 		}
// 		if (*content[i] == '$')
// 		{
// 			start = i + 1;
// 			i++;
// 			while(isalnum(*content[i]) || *content[i] == '_')
// 				i++;
// 			variable_name = ft_strndup(*content + start, i - start);
// 			get_value = ft_getenv(msh, variable_name);
// 			free(variable_name);
// 			if (get_value)
// 			{
// 				expanded_string = ft_strjoin(expanded_string, get_value);
// 				free(get_value);
// 			}
// 		}
// 		if (content[i])
// 		{
// 			expanded_string = ft_strjoin(expanded_string, *content + i);
// 		}		
// 	}
// 	free(*content);
// 	content = &expanded_string;
// 	return (true);
// }


// bool exp_env_vars(char **content, t_msh *msh)
// {
//     char *expanded_string = NULL;
//     char *prefix = NULL;
//     char *variable_name = NULL;
//     char *get_value = NULL;
//     char *env_exit_code = NULL;
//     int start = 0;
//     int i = 0;

//     expanded_string = ft_strdup("");
//     while ((*content)[i])
//     {
//         while ((*content)[i] && (*content)[i] != '$')
//             i++;
//         if (!(*content)[i])
//             break;
//         prefix = ft_strndup(*content, i);
// 		printf("Prefix before $: '%s'\n", prefix);
//         char *temp = ft_strjoin(expanded_string, prefix);
//         free(expanded_string);
//         expanded_string = temp;
//         free(prefix);
//         i++;
//         if ((*content)[i] == '?')
//         {
//             env_exit_code = ft_itoa(msh->exit_code);
//              printf("Exit code: '%s'\n", env_exit_code);
// 			temp = ft_strjoin(expanded_string, env_exit_code);
//             free(expanded_string);
//             expanded_string = temp;
//             free(env_exit_code);
//             i++;
//         }
//         else if ((*content)[i] == '$')
//         {
//             i++;
//             start = i;
//             while ((*content)[i] && (isalnum((*content)[i]) || (*content)[i] == '_'))
//                 i++;
//             variable_name = ft_strndup(*content + start, i - start);
// 			       printf("Extracted variable name: '%s'\n", variable_name);
//             get_value = ft_getenv(msh, variable_name);
//             free(variable_name);
//             if (get_value)
//             {
// 				 printf("Found value for '%s': '%s'\n", variable_name, get_value);
//                 temp = ft_strjoin(expanded_string, get_value);
//                 free(expanded_string);
//                 expanded_string = temp;
//                 free(get_value);
//             }
// 			else {
//                 printf("No value found for '%s', appending as is\n", variable_name);
//                 // If variable is not found, append $ and the variable name
//                 temp = ft_strjoin(expanded_string, "$");
//                 free(expanded_string);
//                 expanded_string = temp;
//                 temp = ft_strjoin(expanded_string, variable_name);
//                 free(expanded_string);
//                 expanded_string = temp;
//             }
//         }
//     }
//     if ((*content)[i])
//     {
// 		printf("Appending remaining content: '%s'\n", *content + i);
//         char *temp = ft_strjoin(expanded_string, *content + i);
//         free(expanded_string);
//         expanded_string = temp;
//     }
// 	printf("Final expanded string: '%s'\n", expanded_string);
//     free(*content);
//     *content = expanded_string;
//     return true;
// }
// // bool exp_env_vars(char **content, t_msh *msh)
// // {
// //     char *expanded_string;
// //     char *prefix;
// //     char *env_exit_code;
// //     char *variable_name;
// //     char *get_value;
// //     int i = 0;
// //     int start;

// //     expanded_string = ft_strdup("");
// //     if (!expanded_string)
// //         return false;

// //     while ((*content)[i])
// //     {
// //         // Copy part before the next '$'
// //         start = i;
// //         while ((*content)[i] && (*content)[i] != '$')
//             i++;
//         if (i > start)
//         {
//             prefix = ft_strndup((*content) + start, i - start);
//             if (!prefix)
//             {
//                 free(expanded_string);
//                 return false;
//             }
//             expanded_string = ft_strjoin(expanded_string, prefix);
//             free(prefix);
//             if (!expanded_string)
//                 return false;
//         }

//         if (!(*content)[i])
//             break;

//         // Handle special case for $?
//         if ((*content)[i] == '$' && (*content)[i + 1] == '?')
//         {
//             env_exit_code = ft_itoa(msh->exit_code);
//             expanded_string = ft_strjoin(expanded_string, env_exit_code);
//             i += 2;
//             free(env_exit_code);
//             if (!expanded_string)
//                 return false;
//         }
//         // Handle general case for $VAR
//         else if ((*content)[i] == '$')
//         {
//             i++;
//             start = i;
//             while (isalnum((*content)[i]) || (*content)[i] == '_')
//                 i++;
//             variable_name = ft_strndup((*content) + start, i - start);
//             if (!variable_name)
//             {
//                 free(expanded_string);
//                 return false;
//             }
//             get_value = ft_getenv(msh, variable_name);
//             free(variable_name);
//             if (get_value)
//             {
//                 expanded_string = ft_strjoin(expanded_string, get_value);
//                 free(get_value);
//                 if (!expanded_string)
//                     return false;
//             }
//         }
//     }

//     // Append the remainder of the string if any
//     if ((*content)[i])
//     {
//         expanded_string = ft_strjoin(expanded_string, (*content) + i);
//         if (!expanded_string)
//             return false;
//     }

//     free(*content);
//     *content = expanded_string;
//     return true;
// }
