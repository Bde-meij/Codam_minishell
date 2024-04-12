/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:23:13 by bde-meij          #+#    #+#             */
/*   Updated: 2023/01/13 12:12:13 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

int	validate_string(char **paths)
{
	int	i;

	i = 0;
	while (access(paths[i], X_OK) != 0)
	{
		if (!paths[i])
			break ;
		i++;
	}
	return (i);
}

char	**paths_strjoin(char **paths, char *command)
{
	char	*free_me;
	int		i;

	i = 0;
	while (paths[i])
	{
		free_me = paths[i];
		paths[i] = protec(ft_strjoin(paths[i], "/"));
		free(free_me);
		free_me = paths[i];
		paths[i] = protec(ft_strjoin(paths[i], command));
		free(free_me);
		i++;
	}
	return (paths);
}

char	*cmd_env_path(char *cmd, t_shellstruct *shellstruct, int i)
{
	char	**darray;
	char	*env_path;

	env_path = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (ft_strncmp(shellstruct->new_env[i], "PATH=", 5) != 0)
	{
		i++;
		if (!shellstruct->new_env[i])
		{
			print_errors(127);
			exit(127);
		}
	}
	darray = protec(ft_split(shellstruct->new_env[i], ':'));
	darray = paths_strjoin(darray, cmd);
	i = validate_string(darray);
	if (darray[i])
		env_path = ft_strdup(darray[i]);
	free_dubarray(darray);
	return (env_path);
}
