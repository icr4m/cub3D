/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 23:20:07 by ijaber            #+#    #+#             */
/*   Updated: 2024/05/20 15:21:41 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;

	result = NULL;
	c = (char)c;
	while (*s != '\0')
	{
		if (*s == c)
			result = ((char *)s);
		s++;
	}
	if (c == '\0')
		result = ((char *)s);
	return (result);
}

/*
int	main(int ac, char **av)
{
	if (ac == 2)
	{
		printf("test :%s", ft_strrchr(av[1], '0'));
	}
}
*/