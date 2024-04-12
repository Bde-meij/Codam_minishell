/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   in_out_files.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 10:52:07 by bde-meij      #+#    #+#                 */
/*   Updated: 2023/01/16 16:43:52 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	file_section(t_shellstruct *shellstruct)
{
	int	i;

	i = 1;
	while (shellstruct->head_token->next)
	{
		if (i == shellstruct->pipe_section)
			break ;
		if (((t_tokenlist *)shellstruct->head_token->content)->token == PIPE)
			i++;
		shellstruct->head_token = shellstruct->head_token->next;
	}
}

int	check_acces_close_fd(t_shellstruct *shellstruct, int tmp_token, int *fd)
{
	if ((access(((t_tokenlist *)shellstruct->head_token->content)->str, \
		R_OK) != 0) && tmp_token == INFILE)
	{
		if (access(((t_tokenlist *)shellstruct->head_token->content)->str, \
			F_OK) == 0)
			print_errors(-1);
		else
			print_errors(-2);
		close(*fd);
		return (1);
	}
	close(*fd);
	return (0);
}

int	open_infiles(t_shellstruct *shellstruct)
{
	t_list	*tmp;
	int		fd;
	int		tmp_token;

	tmp_token = 0;
	fd = -1;
	tmp = shellstruct->head_token;
	file_section(shellstruct);
	while (shellstruct->head_token->next)
	{
		tmp_token = ((t_tokenlist *)shellstruct->head_token->content)->token;
		if (tmp_token == PIPE)
			break ;
		if (tmp_token == INFILE || tmp_token == HERE_DOC)
		{
			if (check_acces_close_fd(shellstruct, tmp_token, &fd))
				return (1);
			fd = open(((t_tokenlist *)shellstruct->head_token->content)->str, 'x');
		}
		shellstruct->head_token = shellstruct->head_token->next;
	}
	shellstruct->head_token = tmp;
	if (fd != -1)
		dup2(fd, 0);
	return (0);
}

int	open_close_logic(int tmp_token, char *tmp_str, int *fd)
{
	if (tmp_token == OUTFILE_WITH_APPEND || tmp_token == OUTFILE)
		close(*fd);
	if (tmp_token == OUTFILE_WITH_APPEND)
	{
		*fd = open(tmp_str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if ((*fd < 0) && (access(tmp_str, F_OK) == 0))
			return (print_errors(-1), 1);
	}
	if (tmp_token == OUTFILE)
	{
		*fd = open(tmp_str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if ((*fd < 0) && (access(tmp_str, F_OK) == 0))
			return (print_errors(-1), 1);
	}
	return (0);
}

int	open_outfiles(t_shellstruct *shellstruct)
{
	t_list	*tmp;
	int		tmp_token;
	int		fd;

	fd = -1;
	tmp = shellstruct->head_token;
	file_section(shellstruct);
	while (shellstruct->head_token->next)
	{
		tmp_token = ((t_tokenlist *)shellstruct->head_token->content)->token;
		if (tmp_token == PIPE)
			break ;
		if (open_close_logic(tmp_token, \
		((t_tokenlist *)shellstruct->head_token->content)->str, &fd))
		{
			shellstruct->head_token = tmp;
			return (1);
		}
		shellstruct->head_token = shellstruct->head_token->next;
	}
	shellstruct->head_token = tmp;
	if (fd != -1)
		dup2(fd, 1);
	return (0);
}
