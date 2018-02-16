/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 16:10:14 by William           #+#    #+#             */
/*   Updated: 2018/02/16 12:10:33 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <string.h>

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

static char			*concatenated_string(char *format, char *name, char *alias, char *type)
{
	if (alias)
	{
		strcpy(format, "-");
		strcat(format, alias);
		strcat(format, ", --");
	}
	else
		strcpy(format, "--");
	strcat(format, name);
	strcat(format, " ");
	if (strlen(type) > 0)
		strcat(format, "[");
	strcat(format, type);
	if (strlen(type) > 0)
		strcat(format, "]");
	return (format);
}

static char			*format_string(char *name, char *alias, char *type)
{
	char			*format;
	size_t			size;

	if (!name)
		name = "undefined";
	size = alias ? (strlen(alias) + strlen(name) + strlen(type) + 6)
	: (strlen(name) + strlen(type) + 3);
	if (strlen(type) > 0)
		size += 2;
	format = (char *)malloc(sizeof(*format) * (size + 1));
	format[size] = '\0';
	concatenated_string(format, name, alias, type);
	return (format);
}

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

char				**options_rows(t_opt_list *options_list)
{
	t_def			*defs;
	char			**rows;
	char			*type;
	size_t			i;

	rows = (char **)malloc(sizeof(*rows) * (options_list->size + 1));
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
	}
	return (rows);
}