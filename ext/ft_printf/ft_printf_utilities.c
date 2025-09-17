/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:24:30 by matmagal          #+#    #+#             */
/*   Updated: 2025/05/12 19:00:27 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnumber(int nb)
{
	long long	n;
	int			len;

	n = nb;
	len = 0;
	if (n < 0)
	{
		len += write(1, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		len += ft_printnumber(n / 10);
		len += ft_printnumber(n % 10);
	}
	if (n < 10)
		len += ft_printchar(n + 48);
	return (len);
}

int	ft_printaddress(unsigned long int nb)
{
	int		len;

	len = 0;
	if (nb >= 16)
	{
		len += ft_printaddress(nb / 16);
		len += ft_printaddress(nb % 16);
	}
	if (nb < 16)
	{
		if (nb < 10)
			len += ft_printchar(nb + 48);
		else
			len += ft_printchar(nb + 87);
	}
	return (len);
}

int	ft_printundec(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb >= 10)
	{
		len += ft_printundec(nb / 10);
		len += ft_printundec(nb % 10);
	}
	if (nb < 10)
		len += ft_printchar(nb + 48);
	return (len);
}

int	ft_printhex(unsigned int nb, int s)
{
	int	len;

	len = 0;
	if (nb >= 16)
	{
		len += ft_printhex(nb / 16, s);
		len += ft_printhex(nb % 16, s);
	}
	if (nb < 16)
	{
		if (nb < 10)
			len += ft_printchar(nb + 48);
		else
		{
			if (s == 1)
				len += ft_printchar(nb + 87);
			else
				len += ft_printchar(nb + 55);
		}
	}
	return (len);
}

int	ft_printstr(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		len += write(1, &str[i], 1);
		i++;
	}
	return (len);
}
