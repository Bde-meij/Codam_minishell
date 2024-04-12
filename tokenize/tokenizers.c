/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:07:58 by bde-meij          #+#    #+#             */
/*   Updated: 2022/12/08 10:22:41 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	find_tokens(t_shellstruct *shellstruct, int token_num)
{
	int	i;

	i = 0;
	while (shellstruct->line[i])
	{
		if (shellstruct->line[i] == shellstruct->compare_str[token_num])
			shellstruct->tokenarr[i] = token_num;
		else if (shellstruct->tokenarr[i] == -1)
			shellstruct->tokenarr[i] = WORD;
		i++;
	}
}

void	find_quoted(t_shellstruct *shellstruct)
{
	size_t	i;

	i = 0;
	while (shellstruct->line[i])
	{
		if (shellstruct->line[i] == '\'')
		{
			i++;
			while (shellstruct->line[i] != '\'' && i < shellstruct->line_len)
			{
				shellstruct->tokenarr[i] = SINGLE_QUOTED_STR;
				i++;
			}
		}
		if (shellstruct->line[i] == '\"')
		{
			i++;
			while ((shellstruct->line[i] != '\"') && i < shellstruct->line_len)
			{
				shellstruct->tokenarr[i] = DOUBLE_QUOTED_STR;
				i++;
			}
		}
		i++;
	}
}

void	find_here_doc_n_out_append(int *tokenarr)
{
	int	i;

	i = 0;
	while (tokenarr[i])
	{
		if ((tokenarr[i] == OUTFILE_OP) && (tokenarr[i + 1] == OUTFILE_OP))
		{
			tokenarr[i] = OUT_APPEND_OP;
			tokenarr[i + 1] = OUT_APPEND_OP;
			i += 2;
		}
		if ((tokenarr[i] == INFILE_OP) && (tokenarr[i + 1] == INFILE_OP))
		{
			tokenarr[i] = HERE_DOC_OP;
			tokenarr[i + 1] = HERE_DOC_OP;
			i += 2;
		}
		i++;
	}
}

void	find_in_out_files(int *tokenarr)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (tokenarr[i])
	{
		if ((tokenarr[i] == INFILE_OP) || (tokenarr[i] == OUTFILE_OP) || \
			(tokenarr[i] == HERE_DOC_OP) || (tokenarr[i] == OUT_APPEND_OP))
		{
			tmp = tokenarr[i] * 10;
			i++;
			while ((tokenarr[i] > 0) && (tokenarr[i]))
				i++;
			while ((tokenarr[i] < 0) && (tokenarr[i]))
			{
				tokenarr[i] = tmp;
				i++;
			}
		}
		if (tokenarr[i])
			i++;
	}
}
