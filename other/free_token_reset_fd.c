/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_reset_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:10:57 by rbrune            #+#    #+#             */
/*   Updated: 2023/01/13 12:15:09 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	reset_std(t_shellstruct *shellstruct)
{
	close (0);
	dup2(shellstruct->in, 0);
	close (1);
	dup2(shellstruct->out, 1);
}

void	free_token_list(t_list *list)
{
	t_list	*tmp;

	while (list->next)
	{
		tmp = list;
		free (((t_tokenlist *)list->content)->str);
		free (((t_tokenlist *)list->content));
		list = list->next;
		free (tmp);
	}
	free (list);
}

int	backslash_semicolom(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			return (print_errors(131), 1);
		}
		if (str[i] == ';')
		{
			return (print_errors(131), 1);
		}
		i++;
	}
	return (0);
}

int	unclosed_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while ((str[i] != '\'') && (str[i]))
				i++;
			if (!str[i])
				return (print_errors(131), 1);
		}
		if (str[i] == '\"')
		{
			i++;
			while ((str[i] != '\"') && (str[i]))
				i++;
			if (!str[i])
				return (print_errors(131), 1);
		}
		i++;
	}
	return (backslash_semicolom(str));
}
