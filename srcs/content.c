/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:10:01 by William           #+#    #+#             */
/*   Updated: 2018/02/22 16:27:01 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <string.h>

/*
** Add an array of string with a special format when we have a section
** with multiples lines.
** content = "First line\nSecond Line"
*/

char				*multiple_lines(char *content, size_t size_column)
{
	size_t			i;
	char			*tmp;
	char			**lines;

	i = -1;
	tmp = NULL;
	if (!(lines = strsplit(content, '\n')))
		fail_malloc();
	while (lines[++i])
	{
		if (!strchr(lines[i], ' '))
			tmp = join_content(tmp, single_word(lines[i], size_column));
		else
		{
			tmp = join_content(tmp, multiple_words(lines[i], size_column));
			if (lines[i + 1])
				tmp = new_line(tmp);
		}
	}
	free_array(lines);
	return (tmp);
}

/*
** Concatenate all the words given the array and the size_column.
*/

static char			*concatenated_words(char *content, size_t size_column, char **words)
{
	size_t			i;
	size_t			len;
	size_t			size;
	char			*tmp;

	i = -1;
	size = 0;
	tmp = NULL;
	while (words[++i])
	{
		len = strlen(words[i]);
		if (len + size > size_column - PADDING)
		{
			tmp = new_line(tmp);
			tmp = add_padding(tmp, MAXWIDTH - size_column + 2);
			size = 0;
		}
		tmp = add_word(tmp, strdup(words[i]));
		size += (len + 1);
	}
	if (!tmp && content && len == 0)
		if (!(tmp = strdup(content)))
			fail_malloc();
	return (tmp);
}

/*
** Word wrap with multiple words so that it will be displayed
** in multiple lines.
*/

char				*multiple_words(char *content, size_t size_column)
{
	char			**words;
	char			*tmp;

	if (!(words = strsplit(content, ' ')))
		fail_malloc();
	tmp = concatenated_words(content, size_column, words);
	free_array(words);
	return (tmp);
}

/*
** If there is only one word, we need to cut it after the 80th
** character.
*/

char				*single_word(char *content, size_t size_column)
{
	size_t			start;
	size_t			size;
	size_t			len;
	char			*tmp;

	start = 0;
	tmp = NULL;
	len = strlen(content);
	while (start < len)
	{
		size = MIN(size_column - PADDING, len - start);
		tmp = add_word(tmp, strndup(content + start, size));
		start += size;
		if (start < len)
		{
			tmp = new_line(tmp);
			tmp = add_padding(tmp, MAXWIDTH - size_column + 2);
		}
	}
	if (!tmp && content && len == 0)
		if (!(tmp = strdup(content)))
			fail_malloc();
	return (tmp);
}
