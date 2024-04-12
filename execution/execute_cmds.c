/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:44:43 by rbrune            #+#    #+#             */
/*   Updated: 2023/01/18 11:48:40 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	execute_cmd(t_shellstruct *shellstruct)
{
	char	**command;
	char	*command_path;

	if (open_infiles(shellstruct))
		exit (1);
	if (open_outfiles(shellstruct))
		exit (1);
	command = search_cmd(shellstruct, shellstruct->pipe_section);
	if (!command[0])
		exit(0);
	if (check_if_builtin(shellstruct))
	{
		builtins(shellstruct);
		exit (0);
	}
	command_path = cmd_env_path(command[0], shellstruct, 0);
	execve(command_path, command, shellstruct->new_env);
	if (access(command[0], F_OK) == 0 && access(command[0], X_OK) < 0)
	{
		print_errors(126);
		exit(126);
	}
	print_errors(127);
	exit(127);
}

void	first_cmd(t_shellstruct *shellstruct, int pipe_out[2])
{
	pid_t	sid;

	sid = guard_fork(fork());
	if (sid == 0)
	{
		dup2(pipe_out[1], 1);
		close(pipe_out[1]);
		close(pipe_out[0]);
		execute_cmd(shellstruct);
	}
	close(pipe_out[1]);
}

void	command_loop(t_shellstruct *shellstruct, int pipe_in, int pipe_out[2])
{
	pid_t	sid;

	sid = guard_fork(fork());
	if (sid == 0)
	{
		dup2(pipe_out[1], 1);
		dup2(pipe_in, 0);
		close(pipe_in);
		close(pipe_out[1]);
		close(pipe_out[0]);
		execute_cmd(shellstruct);
	}
	close(pipe_in);
	close(pipe_out[1]);
}

void	last_cmd(t_shellstruct *shellstruct, int pipe_in, int *pid)
{
	*pid = guard_fork(fork());
	if (*pid == 0)
	{
		dup2(pipe_in, 0);
		execute_cmd(shellstruct);
	}
	close(pipe_in);
}
