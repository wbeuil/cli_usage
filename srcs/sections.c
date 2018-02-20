/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 12:02:18 by William           #+#    #+#             */
/*   Updated: 2018/02/20 12:50:50 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"

/*
** Free each section whithin the sections variable.
*/

void				free_sections(t_section **sections)
{
	if (!sections || !(*sections))
		return ;
	if ((*sections)->next)
		free_sections(&(*sections)->next);
	if ((*sections)->options_list)
	{
		if ((*sections)->options_list->option_defs)
			free((*sections)->options_list->option_defs);
		free((*sections)->options_list);
	}
	free(*sections);
}

/*
** Return the size of the sections variable.
*/

size_t				length_sections(t_section **sections)
{
	size_t			i;
	t_section		*sec;

	i = 0;
	sec = *sections;
	while (sec)
	{
		i++;
		sec = sec->next;
	}
	return (i);
}

/*
** Initialization of a new section variable.
*/

static t_section	*new_section(char *header, char *content, t_opt_list *options_list)
{
	t_section		*section;

	if (!(section = (t_section *)malloc(sizeof(*section))))
		return (NULL);
	section->header = header;
	section->content = content;
	section->options_list = options_list;
	section->next = NULL;
	return (section);
}

/*
** Depending on the length of the sections, if there is already a section
** add a new one at the end of the chained list or simply create
** one otherwise. 
*/

void				add_section(t_section **sections, char *header, char *content, t_opt_list *options_list)
{
	t_section		*section;

	if (length_sections(sections) > 0)
	{
		section = *sections;
		while (section->next)
			section = section->next;
		if (!(section->next = new_section(header, content, options_list)))
			fail_malloc();
	}
	else
		if (!(*sections = new_section(header, content, options_list)))
			fail_malloc();
}
