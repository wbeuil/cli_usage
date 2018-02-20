/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 12:02:53 by William           #+#    #+#             */
/*   Updated: 2018/02/20 12:45:57 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <stdio.h>

/*
** An options' list section comprises a header and two columns
** displaying details of the available options.
*/

static void			options_list_section(t_section *section)
{
	char			**options;

	if (section->header)
	{
		printf("\e[1;4m%s\e[0m", section->header);
		empty_line();
	}
	if (!(options = options_rows(section->options_list)))
		fail_malloc();
	print_options(section->options_list, options);
	free_array(options);
	empty_line();
}

/*
** A content section comprises a header and one or more lines of content.
*/

static void			content_section(t_section *section)
{
	if (section->header)
	{
		printf("\e[1;4m%s\e[0m", section->header);
		empty_line();
	}
	if (section->content)
	{
		word_wrap(section->content, MAXWIDTH);
		empty_line();
	}
}

/*
** Generates a usage guide suitable for a command line app.
** Print a section depending on whether it's an options' list
** or not.
*/

void				command_line_usage(t_section *sections)
{
	t_section		*sec;

	if (sections && length_sections(&sections) > 0)
	{
		sec = sections;
		printf("\n");
		while (sec)
		{
			if (sec->options_list)
				options_list_section(sec);
			else
				content_section(sec);
			sec = sec->next;
		}
		free_sections(&sections);
	}
}