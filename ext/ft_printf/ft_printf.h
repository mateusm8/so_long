/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:13:14 by matmagal          #+#    #+#             */
/*   Updated: 2025/05/19 19:19:02 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printnumber(int nb);
int	ft_printaddress(unsigned long int nb);
int	ft_printundec(unsigned int nb);
int	ft_printhex(unsigned int nb, int s);
int	ft_printstr(char *str);
int	ft_printchar(char c);
int	ft_type_check(char c, va_list *lst_args, unsigned long int num, int len);
int	ft_printf(const char *format, ...);

#endif
