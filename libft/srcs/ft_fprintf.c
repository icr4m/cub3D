/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:18:37 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 16:43:35 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fprintf(int fd, char const *str, ...)
{
	size_t	count;
	va_list	arg;
	size_t	i;

	i = 0;
	count = 0;
	va_start(arg, str);
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count += ft_r_type_fd(str[i + 1], arg, fd);
			i += 2;
		}
		else
		{
			ft_putchar_fd(str[i], fd);
			i++;
			count++;
		}
	}
	va_end(arg);
	return (count);
}
