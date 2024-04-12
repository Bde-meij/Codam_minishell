/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:05:06 by rbrune        #+#    #+#                 */
/*   Updated: 2023/01/03 11:22:26 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	echo_print(char **cmd_tmp, int i)
{
	while (cmd_tmp[i])
	{
		if (cmd_tmp[i + 1] == NULL)
			printf("%s", cmd_tmp[i]);
		else
			printf("%s ", cmd_tmp[i]);
		i++;
	}
}

int	ft_echo(char **cmd_tmp)
{	
	int		i;

	i = 1;
	if (ft_strcmp("echo", cmd_tmp[0]) == 0)
	{
		if (cmd_tmp[1])
		{
			if (ft_strcmp("-n", cmd_tmp[i]) == 0)
			{
				i++;
				echo_print(cmd_tmp, i);
			}
			else
			{
				echo_print(cmd_tmp, i);
				printf("\n");
			}
			free_dubarray (cmd_tmp);
			g_exit_code = 0;
			return (1);
		}
		printf("\n");
	}
	return (0);
}
