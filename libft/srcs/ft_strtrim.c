/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:07:57 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/24 15:02:24 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size_result;
	char	*result;

	if (!set || !s1)
		return (ft_strdup(""));
	while (*s1 != '\0')
	{
		if (ft_checkset((char)*s1, set))
			s1++;
		else
			break ;
	}
	size_result = ft_strlen(s1);
	while (size_result > 0)
	{
		if (ft_checkset(s1[size_result - 1], set))
			size_result--;
		else
			break ;
	}
	result = gc_malloc(sizeof(char) * (size_result + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, (char *)s1, size_result + 1);
	return (result);
}
/*
int	main(int ac, char **av)
{
	(void)ac;
	printf("string after trim :%s", ft_strtrim(av[1], av[2]));
}
*/