/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:41:49 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 16:23:07 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_printf(char const *str, ...)
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
			count += ft_r_type(str[i + 1], arg);
			i += 2;
		}
		else
		{
			ft_putchar(str[i]);
			i++;
			count++;
		}
	}
	va_end(arg);
	return (count);
}
