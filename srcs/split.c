/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 14:08:09 by William           #+#    #+#             */
/*   Updated: 2018/02/20 12:54:39 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"

/*
** Find if the character is our delimiter.
*/

static int	is_delimited(char letter, char c)
{
	if (letter == c)
		return (1);
	return (0);
}

/*
** Simply fill the array of string with each character.
*/

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

/*
** Allocate memory depending on the number of characters.
*/

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
			if (!(tab[j++] = (char *)malloc(sizeof(**tab) * (k + 1))))
				return (NULL);
			k = 0;
		}
	}
	return (tab);
}

/*
** Count the number of words delimited by a character.
*/

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

/*
** Split string depending on a character.
*/

char		**strsplit(char const *s, char c)
{
	int		count;
	char	**tab;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * (count + 1))))
		return (NULL);
	tab[count] = NULL;
	if (!(tab = malloc_word(tab, s, c)))
		return (NULL);
	tab = fill_table(tab, s, c);
	return (tab);
}
