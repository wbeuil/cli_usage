/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:17:55 by William           #+#    #+#             */
/*   Updated: 2018/02/22 16:18:41 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <string.h>

/*
** Add word to a previous allocated content if there is one.
** Otherwise create one.
*/

char				*add_word(char *content, char *new)
{
	size_t			size;

	if (!new)
		fail_malloc();
	if (!content)
		return (add_word(strdup("  "), new));
	size = strlen(content) + strlen(new) + 1;
	if (!(content = (char *)realloc(content, sizeof(*content) * (size + 1))))
		fail_malloc();
	strcat(content, new);
	free(new);
	strcat(content, " ");
	return (content);
}

/*
** After a new line, add spaces for padding.
*/

char				*add_padding(char *content, size_t padding)
{
	size_t			size;
	size_t			i;

	if (content)
	{
		size = strlen(content) + padding;
		if (!(content = (char *)realloc(content, sizeof(*content) * (size + 1))))
			fail_malloc();
		i = -1;
		while (++i < padding)
			strcat(content, " ");
	}
	return (content);
}

/*
** Add a new line at the end.
*/

char				*new_line(char *content)
{
	size_t			size;

	if (content)
	{
		size = strlen(content) + strlen("\n");
		if (!(content = (char *)realloc(content, sizeof(*content) * (size + 1))))
			fail_malloc();
		strcat(content, "\n");
	}
	return (content);
}

/*
** Add an empty line.
*/

char				*empty_line(char *content)
{
	size_t			size;

	if (content)
	{
		size = strlen(content) + strlen("\n\n");
		if (!(content = (char *)realloc(content, sizeof(*content) * (size + 1))))
			fail_malloc();
		strcat(content, "\n\n");
	}
	return (content);
}