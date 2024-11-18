/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:13:00 by temil-da          #+#    #+#             */
/*   Updated: 2024/11/18 02:23:26 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

char *handle_content(char **content, t_mini *msh);
void free_and_assign(char **dst, char *src);
char *get_env_value(t_mini *minish, const char *var_name);
char *expand_var(t_mini *minish, const char *content, int *i);

#include <stdlib.h>
#include <string.h>

// Assuming these functions are provided
// char *ft_strndup(const char *s, size_t n);
// char *ft_strdup(const char *s);
// char *ft_strjoin(char const *s1, char const *s2);
// char *ft_itoa(int n);
// char *ft_getenv(t_mini *minish, const char *name);
// int ft_isalnum(int c);
// int ft_strcmp(const char *s1, const char *s2);

bool exp_env_vars(char **content, t_mini *msh)
{
    char *expanded_string;

    while (1)
    {
        expanded_string = handle_content(content, msh);
        if (ft_strcmp(*content, expanded_string) == 0)
        {
            free(expanded_string);
            break;
        }
        free_and_assign(content, expanded_string);
    }
    return true;
}

char *handle_content(char **content, t_mini *msh)
{
    char *expanded_string;
    char *env;
    char *temp;
    int i;
    int last_pos;

    i = 0;
    last_pos = 0;
    expanded_string = ft_strdup("");

    while ((*content)[i])
    {
        if ((*content)[i] == '$')
        {
            temp = ft_strndup(*content + last_pos, i - last_pos);
            free_and_assign(&expanded_string, ft_strjoin(expanded_string, temp));
            free(temp);

            i++;
            if ((*content)[i] == '?')
            {
                env = ft_itoa(msh->exit_code);
                i++;
            }
            else
            {
                env = expand_var(msh, *content, &i);
            }

            if (env)
            {
                free_and_assign(&expanded_string, ft_strjoin(expanded_string, env));
                free(env);
            }

            last_pos = i;
        }
        else
        {
            i++;
        }
    }

    if (last_pos < i)
    {
        temp = ft_strdup(*content + last_pos);
        free_and_assign(&expanded_string, ft_strjoin(expanded_string, temp));
        free(temp);
    }

    return expanded_string;
}

void free_and_assign(char **dst, char *src)
{
    free(*dst);
    *dst = src;
}

char *expand_var(t_mini *minish, const char *content, int *i)
{
    int start = *i;
    int len = 0;
    char *var_name;
    char *env_value;

    while (ft_isalnum(content[*i + len]) || content[*i + len] == '_')
    {
        len++;
    }

    var_name = ft_strndup(content + start, len);
    env_value = get_env_value(minish, var_name);
    free(var_name);

    *i += len;
    return env_value;
}

char *get_env_value(t_mini *minish, const char *var_name)
{
    if (strcmp(var_name, "?") == 0)
    {
        return ft_itoa(minish->exit_code);
    }
    return ft_getenv(minish, var_name);
}

//=========================================================
// bool exp_env_vars(char **content, t_mini *msh)
// {
// 	char *expanded_string;
// 	char *prefix;
// 	//char *env_exit_code;
// 	int i = 0;	

// 	(void)msh;
// 	expanded_string = ft_strdup("");
// 	while((*content)[i])
// 	{
// 		while ((*content)[i] && (*content)[i] != '$')
// 		{
// 			i++;
// 		}
// 		prefix = ft_strndup(*content, i);
// 		expanded_string = ft_strjoin(expanded_string, prefix);
// 		free(prefix);
			
// 	}
// 	return (true);
// }
//==============================================================================
// char	*check_and_expand_env(char **content, int *i, t_mini *minish)
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

// char	*check_string(char **content, t_mini *minish)
// {
// 	int		i;
// 	char	*expanded_string;
// 	char	*env;

// 	i = 0;
// 	env = NULL;
// 	expanded_string = NULL;
// 	while ((*content)[i] && (*content)[i] != '$')
// 		i++;
// 	if (!(*content)[i])
// 		return (NULL);
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
// 	return (expanded_string);
// }

// void	exp_env_vars(char **content, t_mini *minish)
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

bool	heredoc_loop(char *delimiter, int fd)
{
	char	*line;

	line = NULL;
	line = readline("heredoc> ");
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		line = NULL;
		return (false);
	}
	write(fd, line, strlen(line));
	write(fd, "\n", 1);
	free(line);
	line = NULL;
	return (true);
}
//==============================================================================