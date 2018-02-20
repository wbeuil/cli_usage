/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 11:27:05 by William           #+#    #+#             */
/*   Updated: 2018/02/20 12:35:54 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cli_usage.h"

/*
** Initialize options definitions to print an options' list.
*/

static t_def		*new_option_definitions(int size)
{
	t_def			*option_defs;

	option_defs = init_option_defs(size);
	option_defs[0] = add_def("help", "h", OPT_NULL);
	option_defs[0].description = "Display this usage guide.";
	option_defs[1] = add_def("src", NULL, OPT_STRING);
	option_defs[1].multiple = 1;
	option_defs[1].description = "The input files to process.";
	option_defs[1].label = "file ...";
	option_defs[2] = add_def("timeout", "t", OPT_INTEGER);
	option_defs[2].description = "Timeout value in ms.";
	option_defs[2].label = "ms";
	return (option_defs);
}

/*
** Initialize all the sections before calling commande line
** usage.
*/

int					main(void)
{
	t_section		*sections;
	size_t			size;
	t_def			*option_defs;
	t_opt_list		*options_list;

	sections = NULL;
	size = 3;
	option_defs = new_option_definitions(size);
	options_list = init_options_list(option_defs, size);
	add_section(&sections, "A typical app", "Generates something important. \
This is a rather long, but ultimately inconsequential description \
intended solely to demonstrate description appearance.", NULL);
/*	add_section(&sections, "A typical app", "Generates something important. "
							"This is a rather long, but ultimately inconsequential "
							"description intended solely to demonstrate description appearance.", NULL);*/
	add_section(&sections, "Options", NULL, options_list);
	command_line_usage(sections);
	return (0);
}