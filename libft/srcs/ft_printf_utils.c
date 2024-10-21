/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaber <ijaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:03:37 by ijaber            #+#    #+#             */
/*   Updated: 2024/10/02 16:22:46 by ijaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_r_type(char c, va_list arg)
{
	if (c == 'c')
		return (ft_putchar(va_arg(arg, int)));
	if (c == 's')
		return (ft_putstr(va_arg(arg, char *)));
	if (c == 'p')
	{
		return (ft_p(va_arg(arg, void *)));
	}
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(arg, int)));
	if (c == 'u')
		return (ft_print_nb(va_arg(arg, int)));
	if (c == 'x')
		return (ft_putnbr_base((unsigned int)(va_arg(arg, int)), HEXA_LOWER));
	if (c == 'X')
		return (ft_putnbr_base((unsigned int)(va_arg(arg, int)), HEXA_UPPER));
	if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

size_t	ft_p(void *ptr)
{
	if (ptr == NULL)
		return (ft_putstr("(nil)"));
	else
		return (ft_putstr("0x") + ft_putnbr_base((long)ptr, HEXA_LOWER));
}
