/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazakov <mazakov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:10:10 by mazakov           #+#    #+#             */
/*   Updated: 2025/05/09 16:16:27 by mazakov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alphanum(char c)
{
	if (is_digit(c) || is_alpha(c))
		return (1);
	return (0);
}

void	is_in_quote(char c, int *sq, int *dq)
{
	if (c == '\'' && (*dq % 2) == 0)
		*sq = *sq + 1;
	if (c == '\"' && (*sq % 2) == 0)
		*dq = *dq + 1;
}

int	pos_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
