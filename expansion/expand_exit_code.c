/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_exit_code.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 12:41:55 by rbrune        #+#    #+#                 */
/*   Updated: 2022/12/09 12:45:59 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

char	*fill_new_input(char *new_input, char *old_input, \
char *expand_str, size_t start_index);

char	*expand_exit_code(char *tmp_str, \
char *input, size_t *i)
{
	char	*new_input;
	char	*expand_str;

	expand_str = protec(ft_itoa(g_exit_code));
	new_input = protec(malloc(sizeof(char) * \
	ft_strlen(input) + ft_strlen(expand_str) + 2));
	new_input = fill_new_input(new_input, input, \
	expand_str, ft_strlen(tmp_str) + *i + 1);
	(*i) = 0;
	free (tmp_str);
	free(expand_str);
	free(input);
	return (new_input);
}
