/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:10:01 by William           #+#    #+#             */
/*   Updated: 2018/02/16 12:17:38 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <string.h>
#include <stdio.h>

void					print_options(t_opt_list *options_list, char **options)
{
	t_def			*defs;
	size_t			option_width;
	size_t			i;

	option_width = max_length(options);
	i = -1;
	defs = options_list->option_defs;
	while (++i < options_list->size)
	{
		printf("  %-*s ", (int)option_width, options[i]);
		if (defs[i].description)
			word_wrap(defs[i].description, MAXWIDTH - (option_width + PADDING));
		if (i + 1 < options_list->size)
			printf("\n");
	}
}

static void				new_line_padding(size_t padding)
{
	size_t				i;

	i = -1;
	while (++i < padding)
		printf(" ");
}

static void				multiple_words(char *content, size_t size_column)
{
	size_t				i;
	size_t				size;
	size_t				len;
	char				**words;

	words = strsplit(content, ' ');
	i = -1;
	size = 2;
	printf("  ");
	while (words[++i])
	{
		len = strlen(words[i]);
		if (len + size > size_column - PADDING)
		{
			printf("\n  ");
			new_line_padding(MAXWIDTH - size_column);
			size = 2;
		}
		printf("%s ", words[i]);
		size += (len + 1);
	}
	free_array(words);
}

static void				single_word(char *content, size_t size_column)
{
	size_t				start;
	size_t				size;
	size_t				len;
	char				*line;

	start = 0;
	len = strlen(content);
	while (start < len)
	{
		size = MIN(size_column - PADDING, len - start);
		line = strndup(content + start, size);
		printf("  %s ", line);
		free(line);
		start += size;
		if (start < len)
		{
			printf("\n");
			new_line_padding(MAXWIDTH - size_column);
		}
	}
}

void					word_wrap(char *content, size_t size_column)
{
	size_t				i;
	char				**lines;

	if (!strchr(content, ' ') && !strchr(content, '\n'))
		single_word(content, size_column);
	else if (strchr(content, '\n'))
	{
		lines = strsplit(content, '\n');
		i = -1;
		while (lines[++i])
		{
			if (!strchr(lines[i], ' '))
				single_word(lines[i], size_column);
			else
			{
				multiple_words(lines[i], size_column);
				if (lines[i + 1])
					printf("\n");
			}
		}
		free_array(lines);
	}
	else
		multiple_words(content, size_column);
}