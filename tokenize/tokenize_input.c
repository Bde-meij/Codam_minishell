/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:57:30 by bde-meij          #+#    #+#             */
/*   Updated: 2023/06/15 15:02:00 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	find_tokens(t_shellstruct *shellstruct, int token_num);
void	find_here_doc_n_out_append(int *tokenarr);
void	find_in_out_files(int *tokenarr);
void	find_quoted(t_shellstruct *shellstruct);

int	check_in_out_shenanigans(t_shellstruct *shellstruct, int in_out_op, int i)
{
	if ((in_out_op == INFILE_OP) && \
		(shellstruct->tokenarr[i] == OUTFILE_OP))
		return (print_errors(258), 1);
	if ((in_out_op == OUTFILE_OP) && \
		(shellstruct->tokenarr[i] == INFILE_OP))
		return (print_errors(258), 1);
	return (0);
}

int	find_unexpected_token(t_shellstruct *shellstruct, int in_out_op)
{
	size_t	i;
	size_t	tempi;

	i = 0;
	while (shellstruct->tokenarr[i])
	{
		tempi = i;
		while (shellstruct->tokenarr[i] == in_out_op && i < shellstruct->line_len)
		{
			i++;
			if (check_in_out_shenanigans(shellstruct, in_out_op, i))
				return (1);
			while (shellstruct->tokenarr[i] == SPACES)
			{
				tempi++;
				i++;
			}
		}
		if ((i - tempi) > 2)
			return (print_errors(258), 1);
		i++;
	}
	return (0);
}

void	find_cmds(int *tokenarr, int i)
{
	int	flag;
	int	it_is_written;

	flag = CMD;
	it_is_written = NO;
	while (tokenarr[i])
	{
		if (tokenarr[i] < 0)
		{
			tokenarr[i] = flag;
			if (flag == CMD)
				it_is_written = YES;
		}
		if ((it_is_written == YES) && (tokenarr[i + 1] > 0) && \
			(tokenarr[i + 1] != QUOTE) && (tokenarr[i + 1] != DOUBLE_QUOTE))
			flag = CMD_OPTION;
		if (tokenarr[i] == PIPE)
		{
			flag = CMD;
			it_is_written = NO;
		}
		i++;
	}
}

int	tokenize_input(t_shellstruct *shellstruct)
{
	size_t	i;

	i = 0;
	while (i < shellstruct->line_len)
	{
		shellstruct->tokenarr[i] = -1;
		i++;
	}
	i = 0;
	while (shellstruct->compare_str[i])
	{
		find_tokens(shellstruct, i);
		i++;
	}
	find_quoted(shellstruct);
	if (find_unexpected_token(shellstruct, INFILE_OP) || \
		find_unexpected_token(shellstruct, OUTFILE_OP))
		return (1);
	find_here_doc_n_out_append(shellstruct->tokenarr);
	find_in_out_files(shellstruct->tokenarr);
	find_cmds(shellstruct->tokenarr, 0);
	return (0);
}
