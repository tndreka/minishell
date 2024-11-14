/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tndreka <tndreka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:44:48 by tndreka           #+#    #+#             */
/*   Updated: 2024/11/14 19:40:49 by tndreka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Taulant Ndreka on 07/11/2024.
//

#include "../include/mini_sh.h"

bool	expand_env_vars(char **content, t_msh *minish)
{
	char	*expanded_string;

	expanded_string = NULL;
	while (1)
	{
		printf("epand_env_vars ==> checking the string\n");
		expanded_string = check_string(content, minish);
		if (!expanded_string)
		{
			printf("no more env vars to expand\n");
			break ;
		}
		else
		{
			if (!expanded_string)
			{
				printf("Error: Memory allocation faild\n");
				return (false);
			}
			printf("EXPANDIN STRING +++++++\n");
			printf("expanded_string: %s\n", expanded_string);
			free(*content);
			(*content) = ft_strdup(expanded_string);
			if (!(*content))
			{
				printf("22222222==== >Error: Memory allocation faild 222222222\n");
				free(expanded_string);
				return (false);
			}
			free(expanded_string);
			expanded_string = NULL;
		}
	}
	return (true);
}
void	append_remainder(char **expanded_string, char **content, int pos)
{
	char	*temp;

	 printf("append_remainder ==> before appending, expanded_string: %s, content: %s, pos: %d\n", *expanded_string, *content, pos);
	temp = ft_strdup(*expanded_string);
	free(*expanded_string);
	*expanded_string = ft_strjoin(temp, (*content) + pos);
	free(temp);
	temp = NULL;
	printf("append_remainder ==> after appending, expanded_string: %s\n", *expanded_string);
}

void	replace_varname_wtih_var(char **expanded_string, char **env)
{
	char	*temp;

	 printf("replace_varname_wtih_var ==> before replacing, expanded_string: %s, env: %s\n", *expanded_string, *env);
	temp = ft_strdup(*expanded_string);
	free(*expanded_string);
	*expanded_string = ft_strjoin(temp, *env);
	free(temp);
	free(*env);
	*env = NULL;
	temp = NULL;
	printf("replace_varname_wtih_var ==> after replacing, expanded_string: %s\n", *expanded_string);
}

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
	 printf("ft_getenv ==> looking for env variable: %s\n", env);
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], env, len) == 0 && mini->env[i][len] == '=')
		{
			var = ft_strdup(mini->env[i] + (len + 1));
			printf("ft_getenv ==> found env variable: %s, value: %s\n", env, var);
			return (var);
		}
	}
	 printf("ft_getenv ==> env variable not found: %s\n", env);
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

char	*check_and_expand_env(char **content, int *i, t_msh *minish)
{
	int		j;
	char	*temp;
	char	*temp2;

	j = 0;
	temp = NULL;
	while ((*content)[*i])
	{
		if (ft_isalnum((*content)[*i]) == 1 || (*content)[*i] == '_')
		{
			(*i)++;
			j++;
		}
		else
			break ;
	}
	temp2 = ft_strndup((*content) + ((*i) - j), j);
	temp = ft_getenv(minish, temp2);
	free(temp2);
	temp2 = NULL;
	return (temp);
}

char	*check_string(char **content, t_msh *minish)
{
	int		i;
	char	*expanded_string;
	char	*env;

	i = 0;
	env = NULL;
	expanded_string = NULL;
	 printf("check_string ==> starting\n");
	while ((*content)[i] && (*content)[i] != '$')
		i++;
	if (!(*content)[i])
	{
		printf("check_string ==> no $ found\n");
		return (NULL);
	}
	expanded_string = ft_strndup(*content, i);
	i++;
	if ((*content)[i] == '?')
	{
		env = ft_itoa(minish->exit_code);
		i++;
	}
	else
		env = check_and_expand_env(content, &i, minish);
	if (env)
		replace_varname_wtih_var(&expanded_string, &env);
	if ((*content)[i])
		append_remainder(&expanded_string, content, i);
	printf("check_string ==> returning expanded string: %s\n", expanded_string);
	return (expanded_string);
}
