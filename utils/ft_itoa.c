/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:32 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/07 14:32:00 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i ;

	i = 0;
	while (s1 && s2 && s1[i] == s2[i] && i < n)
		i++;
	return (s2[i] - s1[i]);
}

int	len_nb(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		count++;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int nb)
{
	char	*nbr;
	int		len;

	len = len_nb(nb);
	nbr = malloc(sizeof(char) * (len + 1));
	if (!nbr)
		return (NULL);
	nbr[len] = 0;
	while (--len >= 0)
	{
		nbr[len] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (nbr);
}
