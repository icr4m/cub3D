/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:55:50 by ijaber            #+#    #+#             */
/*   Updated: 2024/05/20 16:07:39 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	x;

	x = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (x);
}
/*
int	main(void)
{
	char			src[] = "Hello, world!";
	char			dest1[20];
	char			dest2[20];
	unsigned int	custom_result;
	size_t			official_result;

	// Using custom ft_strlcpy function
	custom_result = ft_strlcpy(dest1, src, 7);
	printf("Custom ft_strlcpy: Copied %d characters, Result: %s\n",
		custom_result, dest1);
	// Using official strlcpy function
	dest2[0] = '\0'; // Reset destination buffer
	official_result = strlcpy(dest2, src, 7);
	printf("Official strlcpy: Copied %zu characters, Result: %s\n",
		official_result, dest2);
	return (0);
}
*/
