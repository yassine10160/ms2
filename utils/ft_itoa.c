/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:40:32 by dorianmazar       #+#    #+#             */
/*   Updated: 2025/05/05 14:18:12 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// int main()
// {
// 	char *dest;
// 	dest = ft_itoa(2500);
// 	// printf("len: %d\n", len_nb(255));
// 	printf("itoa: %s\n", dest);
// }