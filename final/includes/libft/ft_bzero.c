/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:32:41 by temil-da          #+#    #+#             */
/*   Updated: 2024/03/08 16:51:44 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			a;

	a = 0;
	ptr = s;
	if (n == 0)
	{
		return ;
	}
	while (a < n)
	{
		*ptr = '\0';
		ptr++;
		a++;
	}
}