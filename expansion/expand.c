/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 13:02:47 by rbrune        #+#    #+#                 */
/*   Updated: 2023/01/16 13:55:15 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

char	*expand_exit_code(char *tmp_str, \
char *input, size_t *i);
char	*delete_dollar_str(char *new_input, \
char *old_input, size_t start_index);
char	*add_expanded_str(char *expand_str, \
char *new_input, size_t *i, size_t j);
char	*make_expand_str(char *old_input, size_t i, \
size_t *j);
int		search_for_quote(char *input, int i);

char	*fill_new_input(char *new_input, char *old_input, \
char *expand_str, size_t start_index)
{
	size_t	i;
	int		quote_flag;

	i = 0;
	while (old_input[i] != '$' && old_input[i])
	{
		new_input[i] = old_input[i];
		i++;
	}
	quote_flag = search_for_quote(new_input, i);
	new_input = add_expanded_str(expand_str, new_input, &i, quote_flag);
	if (ft_strlen(old_input) > start_index)
	{
		while (old_input[start_index])
		{
			new_input[i] = old_input[start_index];
			i++;
			start_index++;
		}
	}
	new_input[i] = '\0';
	return (new_input);
}

char	*expand(char *input, size_t *j, size_t *i, t_shellstruct *shellstruct)
{
	char	*new_input;
	char	*tmp_str;

	new_input = NULL;
	tmp_str = make_expand_str(input, *i, j);
	if (ft_strcmp("?", tmp_str) == 0)
		return (expand_exit_code(tmp_str, input, i));
	else if (check_expand(tmp_str, shellstruct))
	{
		new_input = protec(ft_calloc(sizeof(char), ft_strlen(input) + 1));
		new_input = delete_dollar_str(new_input, input, \
		ft_strlen(tmp_str) + 1);
		*i = 0;
	}
	else
	{
		new_input = protec(ft_calloc(sizeof(char), ft_strlen(input) + \
		ft_strlen(((t_envlist *)shellstruct->head_envp->content)->right_part) + 2));
		new_input = fill_new_input(new_input, input, \
		((t_envlist *)shellstruct->head_envp->content)->right_part, (*j + *i));
		*i = 0;
	}
	free (tmp_str);
	free (input);
	return (new_input);
}

char	*search_for_expand(char *input, size_t *i, t_shellstruct *shellstruct)
{
	size_t	j;
	t_list	*tmp_head;

	tmp_head = shellstruct->head_envp;
	input = expand(input, &j, i, shellstruct);
	shellstruct->head_envp = tmp_head;
	return (input);
}

void	check_quoted_expand(char *input, size_t *i, int *dub_quote_flag)
{
	if (input[*i] == '\"' && *dub_quote_flag == 0)
	{
		*dub_quote_flag = 1;
		(*i)++;
	}
	if (input[*i] == '\"' && *dub_quote_flag == 1)
	{
		*dub_quote_flag = 0;
		(*i)++;
	}
	if (input[*i] == '\'' && *dub_quote_flag == 0)
	{
		(*i)++;
		while (input[*i] != '\'' && input[*i])
			(*i)++;
	}
}

char	*parse_dollar_sign(char *input, t_shellstruct *shellstruct)
{
	size_t	i;
	int		dub_quote_flag;

	i = 0;
	dub_quote_flag = 0;
	while (input[i])
	{
		check_quoted_expand(input, &i, &dub_quote_flag);
		if (input[i] == '$')
			input = search_for_expand(input, &i, shellstruct);
		if (!input[i])
			break ;
		i++;
	}
	return (input);
}
