/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/13 12:08:16 by bde-meij      #+#    #+#                 */
/*   Updated: 2023/01/18 10:32:44 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	print_more_errors(int error_code)
{
	if (error_code == 126)
		ft_putstr_fd("BigHell: Permission denied\n", 2);
	if (error_code == 127)
		ft_putstr_fd("BigHell: Command or Executable not found\n", 2);
	if (error_code == 128)
		ft_putstr_fd("BigHell: Invalid argument to exit\n", 2);
	if (error_code == 130)
		ft_putstr_fd("BigHell: Error: Script terminated by Control-C\n", 2);
	if (error_code == 131)
		ft_putstr_fd("BigHell: Error: Invalid input\n", 2);
	if (error_code == 138)
		ft_putstr_fd("BigHell: Error: Child did not exit\n", 2);
}

void	print_errors(int error_code)
{
	g_exit_code = error_code;
	if (error_code == -1)
	{
		ft_putstr_fd("BigHell: Permission denied\n", 2);
		g_exit_code = 1;
	}
	else if (error_code == -2)
	{
		ft_putstr_fd("BigHell: No such file or directory\n", 2);
		g_exit_code = 1;
	}
	else if (error_code == 1)
		ft_putstr_fd("Error\n", 2);
	if (error_code == 2)
		ft_putstr_fd("Misuse of shell builtins\n", 2);
	if (error_code == 10)
		ft_putstr_fd("Error: No child process\n", 2);
	if (error_code == 12)
		ft_putstr_fd("Error: Malloc fail\n", 2);
	if (error_code == 32)
		ft_putstr_fd("Error: Broken pipe\n", 2);
	print_more_errors(error_code);
}
