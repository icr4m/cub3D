/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:48:25 by ijaber            #+#    #+#             */
/*   Updated: 2024/03/24 14:21:57 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	tmp_c;
	unsigned char	*tmp_s;

	tmp_c = (unsigned char)c;
	tmp_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (tmp_s[i] == tmp_c)
			return ((void *)&tmp_s[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("test :%p\n", ft_memchr(av[1], 'o', 20));
	}
}
*/