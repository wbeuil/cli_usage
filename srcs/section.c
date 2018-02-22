/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:40:42 by William           #+#    #+#             */
/*   Updated: 2018/02/22 16:19:42 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <string.h>

/*
** Join two contents by reallocating the second content into the first
** one.
*/

char				*join_content(char *content, char *new)
{
	size_t			size;

	if (!new)
		return (NULL);
	if (!content)
		return (new);
	size = strlen(content) + strlen(new) + 1;
	if (!(content = (char *)realloc(content, sizeof(*content) * (size + 1))))
		fail_malloc();
	strcat(content, new);
	free(new);
	return (content);
}

/*
** If the content is higher than 80 characters, we need to split it
** into multiple lines. Finally add them to the section's content.
*/

char				*add_content(char *section_content, char *content, size_t size_column)
{
	char			*tmp;

	if (!strchr(section_content, ' ') && !strchr(section_content, '\n'))
		tmp = single_word(section_content, size_column);
	else if (strchr(section_content, '\n'))
		tmp = multiple_lines(section_content, size_column);
	else
		tmp = multiple_words(section_content, size_column);
	return (join_content(content, tmp));
}

/*
** Format the two columns option's definitions and option's description before
** adding them to the section's content.
*/

char				*add_options_list(t_section *section, char *options_list, char **options)
{
	size_t			i;
	size_t			option_width;
	char			*tmp;
	t_def			*defs;

	i = -1;
	tmp = NULL;
	option_width = max_length(options) - 9;
	defs = section->options_list->option_defs;
	while (++i < section->options_list->size)
	{
		tmp = add_word(tmp, strdup(options[i]));
		tmp = add_padding(tmp, (int)option_width - (strlen(options[i]) - 9));
		if (defs[i].description)
			tmp = add_content(defs[i].description, tmp, MAXWIDTH - option_width - PADDING);
		if (i + 1 < section->options_list->size)
		{
			tmp = new_line(tmp);
			tmp = add_padding(tmp, 2);
		}
	}
	return (join_content(options_list, tmp));
}

/*
** Add the header to the section's with an ansi style (bold and underline).
*/

char				*add_header(t_section *section)
{
	size_t			size;
	char			*header;

	size = strlen("\e[1;4m") + strlen(section->header) + strlen("\e[22;24m");
	if (!(header = (char *)malloc(sizeof(*header) * (size + 1))))
		fail_malloc();
	strcat(strcpy(header, "\e[1;4m"), section->header);
	strcat(header, "\e[22;24m");
	return (header);
}
