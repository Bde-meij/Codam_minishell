/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_n_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:36:39 by bde-meij          #+#    #+#             */
/*   Updated: 2023/01/13 12:13:50 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

int	guard_fork(int i)
{
	if (i == -1)
	{
		print_errors(10);
		exit (10);
	}
	return (i);
}

void	*protec(void *ptr)
{
	if (ptr == NULL)
	{
		print_errors(12);
		exit (12);
	}
	return (ptr);
}

int	guard_fd(int i)
{
	if (i == -1)
	{
		print_errors(32);
		exit (32);
	}
	return (i);
}

void	free_dubarray(char **dubarray)
{
	int	i;

	i = 0;
	while (dubarray[i])
	{
		free(dubarray[i]);
		dubarray[i] = NULL;
		i++;
	}
	free(dubarray);
	dubarray = NULL;
}
