/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:31:13 by dazzali           #+#    #+#             */
/*   Updated: 2024/12/19 18:45:10 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

static int	islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isalpha(int c)
{
	return (isupper(c) || islower(c));
}
