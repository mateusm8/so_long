/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:18:46 by matmagal          #+#    #+#             */
/*   Updated: 2025/08/31 19:19:07 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(char c)
{
	int	len;

	len = write(1, &c, 1);
	return (len);
}

int	ft_type_check(char c, va_list *lst_args, unsigned long int num, int len)
{
	if (c == 'c')
		len += ft_printchar(va_arg(*lst_args, int));
	if (c == '%')
		len += write(1, "%", 1);
	if (c == 'd' || c == 'i')
		len += ft_printnumber(va_arg(*lst_args, int));
	if (c == 'u')
		len += ft_printundec(va_arg(*lst_args, unsigned int));
	if (c == 'x')
		len += ft_printhex(va_arg(*lst_args, unsigned int), 1);
	if (c == 'X')
		len += ft_printhex(va_arg(*lst_args, unsigned int), 2);
	if (c == 'p')
	{
		num = va_arg(*lst_args, unsigned long int);
		if (!num)
			return (ft_printstr("(nil)"));
		len += write(1, "0x", 2);
		len += ft_printaddress(num);
	}
	if (c == 's')
		len += ft_printstr(va_arg(*lst_args, char *));
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	lst_args;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!format)
		return (-1);
	va_start(lst_args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i])
				len += ft_type_check(format[i], &lst_args, 0, 0);
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(lst_args);
	return (len);
}
