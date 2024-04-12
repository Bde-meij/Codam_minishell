/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:04:07 by bde-meij          #+#    #+#             */
/*   Updated: 2023/01/10 16:15:23 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	quit_here_doc_signal(int sig);
void	ctrl_c_herdoc(int sig);

void	unlink_heredocs(t_shellstruct *shellstruct)
{
	t_list	*tmp;

	tmp = shellstruct->head_token;
	while (shellstruct->head_token->next)
	{
		if (((t_tokenlist *)shellstruct->head_token->content)->token == HERE_DOC)
			unlink(((t_tokenlist *)shellstruct->head_token->content)->str);
		shellstruct->head_token = shellstruct->head_token->next;
	}
	shellstruct->head_token = tmp;
}

char	*check_double(char *file_name)
{
	char	*tmp;

	tmp = NULL;
	while (access(file_name, F_OK) == 0)
	{
		tmp = file_name;
		file_name = ft_strjoin(file_name, "a");
		free(tmp);
	}
	return (file_name);
}

void	make_heredoc(char *delimiter, t_shellstruct *shellstruct)
{
	char	*doc;
	int		fd;
	char	*input;

	signal(SIGINT, ctrl_c_herdoc);
	signal(SIGQUIT, quit_here_doc_signal);
	fd = open(((t_tokenlist *)shellstruct->head_token->content)->str, \
		O_WRONLY | O_CREAT, 0644);
	while (1)
	{
		input = ft_strjoin_free_first_str(readline(">"), "\n");
		doc = parse_dollar_sign(input, shellstruct);
		if ((ft_strncmp(doc, delimiter, ft_strlen(delimiter)) == 0) && \
			(ft_strlen(delimiter) == ft_strlen(doc) - 1))
			break ;
		write(fd, doc, ft_strlen(doc));
		free(doc);
		doc = NULL;
	}
	free(doc);
	doc = NULL;
	close(fd);
	exit(0);
}

void	make_heredocs(t_shellstruct *shellstruct)
{
	t_list	*tmp;
	char	*delim;
	pid_t	pid;

	tmp = shellstruct->head_token;
	while (shellstruct->head_token->next)
	{
		if (((t_tokenlist *)shellstruct->head_token->content)->token == HERE_DOC)
		{
			delim = protec(ft_strdup(((t_tokenlist *)shellstruct->\
					head_token->content)->str));
			((t_tokenlist *)shellstruct->head_token->content)->str = \
			check_double(((t_tokenlist *)shellstruct->head_token->content)->str);
			pid = guard_fork(fork());
			if (pid == 0)
				make_heredoc(delim, shellstruct);
			waitpid(pid, NULL, 0);
			free(delim);
		}
		shellstruct->head_token = shellstruct->head_token->next;
	}
	shellstruct->head_token = tmp;
}
