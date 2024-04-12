/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_empty_var.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 12:43:51 by rbrune        #+#    #+#                 */
/*   Updated: 2023/01/16 14:49:16 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

char	*delete_dollar_str(char *new_input, char *old_input, size_t start_index)
{
	size_t	i;

	i = 0;
	while (old_input[i] != '$' && old_input[i])
	{
		new_input[i] = old_input[i];
		i++;
	}
	while (old_input[i + start_index])
	{
		new_input[i] = old_input[i + start_index];
		i++;
	}
	new_input[i] = '\0';
	return (new_input);
}

int	search_for_quote(char *input, int i)
{
	int	quote_flag;

	quote_flag = 0;
	while (i > 0)
	{
		if ((input[i] == '\'' || input[i] == '\"'))
			quote_flag = !quote_flag;
		i--;
	}
	return (quote_flag);
}
