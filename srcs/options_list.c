/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 16:10:14 by William           #+#    #+#             */
/*   Updated: 2018/02/20 12:48:18 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <string.h>

/*
** Find the maximum length the option column has depending on
** the size of the formated string.
*/

size_t				max_length(char **rows)
{
	size_t			i;
	size_t			len;
	size_t			maxlen;

	i = -1;
	maxlen = 0;
	while (rows[++i])
	{
		len = strlen(rows[i]);
		if (maxlen < len)
			maxlen = len;
	}
	return (maxlen);
}

/*
** Concatenate the string given the format.
*/

static char			*concatenated_string(char *format, char *name, char *alias, char *type)
{
	strcpy(format, "\e[1m");
	if (alias)
	{
		strcat(format, "-");
		strcat(format, alias);
		strcat(format, ", --");
	}
	else
		strcat(format, "--");
	strcat(format, name);
	strcat(format, "\e[0m");
	strcat(format, " ");
	if (strlen(type) > 0)
		strcat(format, "[");
	strcat(format, type);
	if (strlen(type) > 0)
		strcat(format, "]");
	return (format);
}

/*
** Calculat the size of the formated string, allocate memory
** and call the concatened function.
*/

static char			*format_string(char *name, char *alias, char *type)
{
	char			*format;
	size_t			size;

	if (!name)
		name = "undefined";
	size = alias ? (strlen(alias) + strlen(name) + strlen(type) + 6 + 8)
	: (strlen(name) + strlen(type) + 3 + 8);
	if (strlen(type) > 0)
		size += 2;
	if (!(format = (char *)malloc(sizeof(*format) * (size + 1))))
		return (NULL);
	format[size] = '\0';
	concatenated_string(format, name, alias, type);
	return (format);
}

/*
** We write a type label depending on the type of the option.
*/

static char			*type_label(t_def def)
{
	if (def.type)
	{
		if (def.type == OPT_BOOLEAN)
			return ("");
		else if (def.type == OPT_STRING)
		{
			if (def.multiple)
				return ("string ...");
			return ("string");
		}
		else
		{
			if (def.multiple)
				return ("int ...");
			return ("int");
		}
	}
	return ("");
}

/*
** For each options, we create a new row with a special format.
** -(alias), --(name) [type]
** and store them in an array.
*/

char				**options_rows(t_opt_list *options_list)
{
	t_def			*defs;
	char			**rows;
	char			*type;
	size_t			i;

	if (!(rows = (char **)malloc(sizeof(*rows) * (options_list->size + 1))))
		return (NULL);
	rows[options_list->size] = NULL;
	i = -1;
	defs = options_list->option_defs;
	while (++i < options_list->size)
	{
		type = defs[i].label ? defs[i].label : type_label(defs[i]);
		if (defs[i].alias)
			rows[i] = format_string(defs[i].name, defs[i].alias, type);
		else
			rows[i] = format_string(defs[i].name, NULL, type);
		if (!rows[i])
			return (NULL);
	}
	return (rows);
}