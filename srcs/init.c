/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 15:33:25 by William           #+#    #+#             */
/*   Updated: 2018/02/16 11:58:52 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"

/*
** Initialization of the list variable.
*/

t_opt_list			*init_options_list(t_def *option_defs, size_t size)
{
	t_opt_list		*options_list;

	options_list = (t_opt_list *)malloc(sizeof(*options_list));
	options_list->option_defs = option_defs;
	options_list->size = size;
	return (options_list);
}

/*
** Initialization of the option definitions variable.
*/

t_def				*init_option_defs(size_t size)
{
	t_def			*option_defs;
	size_t			i;

	option_defs = (t_def *)malloc(sizeof(*option_defs) * (size));
	i = -1;
	while (++i < size)
		option_defs[i] = add_def(NULL, NULL, OPT_INIT);
	return (option_defs);
}

/*
** Add a definition variable.
*/

t_def				add_def(char *name, char *alias, t_type type)
{
	t_def			def;

	def.name = name;
	def.alias = alias;
	def.type = type;
	def.multiple = 0;
	def.description = NULL;
	def.label = NULL;
	return (def);
}
