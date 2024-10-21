/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 22:23:57 by ijaber            #+#    #+#             */
/*   Updated: 2024/09/24 15:02:38 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (s == NULL)
		substr = NULL;
	else
	{
		substr = gc_malloc(sizeof(char) * (len + 1));
		if (!substr)
			return (NULL);
		ft_strlcpy(substr, (char *)s + start, len + 1);
	}
	return (substr);
}
/*
int	main(void)
{
	printf("new sous string :%s\n", ft_substr("Bonjour comment ca va?", 2, 3));
}
*/