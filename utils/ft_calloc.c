/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmazari <dmazari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:14:28 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/05/05 14:17:50 by dmazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;
	size_t	i;

	if (size != 0 && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	dest = malloc((nmemb * size) * sizeof(void));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		*(unsigned char *)(dest + i) = 0;
		i++;
	}
	return (dest);
}
