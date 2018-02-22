/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 12:02:53 by William           #+#    #+#             */
/*   Updated: 2018/02/22 15:59:36 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <string.h>

/*
** An options' list section comprises a header and two columns
** displaying details of the available options.
*/

static char			*options_list_section(t_section *section)
{
	char			**options;
	char			*options_list;

	options_list = NULL;
	if (section->header)
	{
		options_list = add_header(section);
		options_list = empty_line(options_list);
	}
	if (section->options_list)
	{
		if (!(options = options_rows(section->options_list)))
			fail_malloc();
		options_list = add_options_list(section, options_list, options);
		free_array(options);
		options_list = empty_line(options_list);
	}
	return (options_list);
}

/*
** A content section comprises a header and one or more lines of content.
*/

static char			*content_section(t_section *section)
{
	char			*content;

	content = NULL;
	if (section->header)
	{
		content = add_header(section);
		content = empty_line(content);
	}
	if (section->content)
	{
		content = add_content(section->content, content, MAXWIDTH);
		content = empty_line(content);
	}
	return (content);
}

/*
** Generates a usage guide suitable for a command line app.
** Print a section depending on whether it's an options' list
** or not.
*/

char				*command_line_usage(t_section *sections)
{
	char			*usage;
	char			*tmp;
	t_section		*sec;

	usage = NULL;
	if (sections && length_sections(&sections) > 0)
	{
		if (!(usage = strdup("\n")))
			fail_malloc();
		sec = sections;
		while (sec)
		{
			if (sec->options_list)
				tmp = options_list_section(sec);
			else
				tmp = content_section(sec);
			usage = join_content(usage, tmp);
			sec = sec->next;
		}
		free_sections(&sections);
	}
	if (!usage && !(usage = strdup("undefined\n")))
		fail_malloc();
	return (usage);
}