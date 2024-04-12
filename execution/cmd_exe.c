/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:52:07 by bde-meij          #+#    #+#             */
/*   Updated: 2023/01/13 12:51:35 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

int	check_if_builtin(t_shellstruct *shellstruct)
{
	char	**cmd_tmp;

	cmd_tmp = search_cmd(shellstruct, shellstruct->pipe_section);
	if (!cmd_tmp[0])
		return (free_dubarray(cmd_tmp), 0);
	if ((ft_strcmp("pwd", cmd_tmp[0]) == 0) || \
		(ft_strcmp("env", cmd_tmp[0]) == 0) || \
		(ft_strcmp("exit", cmd_tmp[0]) == 0) || \
		(ft_strcmp("unset", cmd_tmp[0]) == 0) || \
		(ft_strcmp("export", cmd_tmp[0]) == 0) || \
		(ft_strcmp("echo", cmd_tmp[0]) == 0) || \
		(ft_strcmp("cd", cmd_tmp[0]) == 0))
		return (free_dubarray(cmd_tmp), 1);
	return (free_dubarray(cmd_tmp), 0);
}

int	engage_children(t_shellstruct *shellstruct, pid_t *pid)
{
	int			sd[2][2];
	int			rd_write;

	rd_write = 0;
	while (shellstruct->pipe_section <= shellstruct->n_pipes)
	{
		if (shellstruct->pipe_section < shellstruct->n_pipes)
			guard_fd(pipe(sd[rd_write]));
		if (shellstruct->pipe_section == 1 && shellstruct->n_pipes > 1)
			first_cmd(shellstruct, sd[rd_write]);
		else if (shellstruct->pipe_section < shellstruct->n_pipes)
			command_loop(shellstruct, \
			sd[!rd_write][0], sd[rd_write]);
		else
			last_cmd(shellstruct, sd[!rd_write][0], pid);
		rd_write = !rd_write;
		shellstruct->pipe_section++;
	}
	return (0);
}

int	pipex(t_shellstruct *shellstruct)
{
	int			wstatus;
	pid_t		pid;
	sig_t		process_sig[2];

	wstatus = 0;
	process_sig[0] = signal(SIGINT, process_signal);
	process_sig[1] = signal(SIGQUIT, quit_process_signal);
	wstatus = engage_children(shellstruct, &pid);
	waitpid(pid, &wstatus, 0);
	while (shellstruct->n_pipes - 1 > 0)
	{
		wait(NULL);
		shellstruct->n_pipes--;
	}
	signal(SIGINT, process_sig[0]);
	signal(SIGQUIT, process_sig[1]);
	if (wstatus == 1)
		return (1);
	if (wstatus == 2)
		return (130);
	if (wstatus == 3)
		return (131);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (print_errors(138), 138);
}

int	cmd_exe(t_shellstruct *shellstruct)
{
	shellstruct->pipe_section = 1;
	signal(SIGINT, SIG_IGN);
	make_heredocs(shellstruct);
	signal(SIGINT, general_signal);
	signal(SIGQUIT, SIG_IGN);
	if (shellstruct->n_pipes >= 2)
		g_exit_code = pipex(shellstruct);
	else if (check_if_builtin(shellstruct))
	{
		if (open_infiles(shellstruct) == 0 && open_outfiles(shellstruct) == 0)
			builtins(shellstruct);
	}
	else
		g_exit_code = pipex(shellstruct);
	reset_std(shellstruct);
	unlink_heredocs(shellstruct);
	free_token_list(shellstruct->head_token);
	return (0);
}
