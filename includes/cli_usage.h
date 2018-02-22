/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_usage.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 11:31:38 by William           #+#    #+#             */
/*   Updated: 2018/02/22 16:19:56 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_USAGE_H
# define CLI_USAGE_H

# include <stdlib.h>

# define MAXWIDTH		80
# define PADDING		3
# define MIN(x, y)		x > y ? y : x

/*
** Enum and Structures
*/

typedef enum			e_type
{
	OPT_INIT			= -1,
	OPT_NULL			= 0,
	OPT_BOOLEAN			= 1,
	OPT_INTEGER			= 2,
	OPT_STRING			= 3
}						t_type;

typedef struct			s_def
{
	char				*name;
	char				*alias;
	enum e_type			type;
	int					multiple;
	char				*description;
	char				*label;
}						t_def;

typedef struct			s_opt_list
{
	t_def				*option_defs;
	size_t				size;
}						t_opt_list;

typedef struct			s_section
{
	char				*header;
	char				*content;
	t_opt_list			*options_list;
	struct s_section	*next;
}						t_section;

/*
** Main function
*/

char					*command_line_usage(t_section *sections);

/*
** Utilities functions
*/

void					fail_malloc(void);
void					free_array(char **array);
char					**strsplit(char const *s, char c);

/*
** Sections functions
*/

void					add_section(t_section **sections, char *header,
									char *content, t_opt_list *options_list);
size_t					length_sections(t_section **sections);
void					free_sections(t_section **sections);


/*
** Section functions
*/

char					*join_content(char *content, char *new);
char					*add_content(char *section_content, char *content, size_t size_column);
char					*add_options_list(t_section *section, char *options_list, char **options);
char					*add_header(t_section *section);

/*
** Content functions
*/

char					*single_word(char *content, size_t size_column);
char					*multiple_words(char *content, size_t size_column);
char					*multiple_lines(char *content, size_t size_column);

/*
** Content utilities functions
*/

char					*new_line(char *content);
char					*empty_line(char *content);
char					*add_padding(char *content, size_t padding);
char					*add_word(char *content, char *new);

/*
** Init functions
*/

t_opt_list				*init_options_list(t_def *option_defs, size_t size);
t_def					add_def(char *name, char *alias, t_type type);
t_def					*init_option_defs(size_t size);

/*
** Options list functions
*/

char					**options_rows(t_opt_list *options_list);
size_t					max_length(char **rows);

#endif
