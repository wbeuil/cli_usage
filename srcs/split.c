/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 14:08:09 by William           #+#    #+#             */
/*   Updated: 2018/02/16 12:40:24 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"

static int	is_delimited(char letter, char c)
{
	if (letter == c)
		return (1);
	return (0);
}

static char	**fill_table(char **tab, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (is_delimited(s[i], c))
		i++;
	while (s[i])
	{
		if (!(is_delimited(s[i], c)))
			tab[j][k++] = s[i];
		i++;
		if ((is_delimited(s[i], c) || s[i] == '\0')
			&& !(is_delimited(s[i - 1], c)))
		{
			tab[j++][k] = '\0';
			k = 0;
		}
	}
	return (tab);
}

static char	**malloc_word(char **tab, char const *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (is_delimited(s[i], c))
		i++;
	while (s[i])
	{
		if (!(is_delimited(s[i], c)))
			k++;
		i++;
		if ((is_delimited(s[i], c) || s[i] == '\0')
			&& !(is_delimited(s[i - 1], c)))
		{
			tab[j++] = (char *)malloc(sizeof(**tab) * (k + 1));
			k = 0;
		}
	}
	return (tab);
}

static int	count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (is_delimited(s[i], c))
		i++;
	while (s[i])
	{
		i++;
		if ((is_delimited(s[i], c) || s[i] == '\0')
			&& !(is_delimited(s[i - 1], c)))
			count++;
	}
	return (count);
}

char		**strsplit(char const *s, char c)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	tab = (char **)malloc(sizeof(*tab) * (count + 1));
	tab[count] = NULL;
	tab = malloc_word(tab, s, c);
	tab = fill_table(tab, s, c);
	return (tab);
}
