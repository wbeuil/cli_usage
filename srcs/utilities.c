/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: William <wbeuil@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 12:07:02 by William           #+#    #+#             */
/*   Updated: 2018/02/20 12:55:15 by William          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cli_usage.h"
#include <stdio.h>

/*
** Free all argv variables.
*/

void				free_array(char **array)
{
	int				i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

/*
** Print an empty line.
*/

void				empty_line(void)
{
	printf("\n\n");
}

/*
** Print an error message for the failure of memory allocation.
*/

void				fail_malloc(void)
{
	fprintf(stderr, "error: Failed to allocate memory\n");
	exit(EXIT_FAILURE);
}
