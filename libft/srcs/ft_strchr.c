/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 22:23:57 by ijaber            #+#    #+#             */
/*   Updated: 2024/05/16 16:16:43 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = (char)c;
	while (*s != '\0' && *s != c)
		s++;
	if (c == *s)
		return ((char *)s);
	return (NULL);
}
/*
int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("test :%s", ft_strchr(av[1], 'o'));
	}
}
*/
