/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 13:00:17 by rbrune        #+#    #+#                 */
/*   Updated: 2023/01/16 14:51:55 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	edit_pwds_two(t_shellstruct *shellstruct, char *tmp_str, t_list	*tmp)
{
	while (shellstruct->head_envp)
	{
		if (ft_strcmp(((t_envlist *)shellstruct->head_envp->content)->left_part, \
			"OLDPWD") == 0)
		{
			tmp_str = ft_strjoin("OLDPWD=", shellstruct->current_path);
			free(((t_envlist *)shellstruct->head_envp->content)->full_str);
			free(((t_envlist *)shellstruct->head_envp->content)->left_part);
			free(((t_envlist *)shellstruct->head_envp->content)->right_part);
			add_content_list(shellstruct->head_envp->content, tmp_str);
			shellstruct->head_envp = tmp;
			shellstruct->new_env = make_array_envp(shellstruct);
			free(tmp_str);
			break ;
		}
		shellstruct->head_envp = shellstruct->head_envp->next;
	}
	shellstruct->head_envp = tmp;
}

void	free_env_list_content(t_shellstruct *shellstruct)
{
	free(((t_envlist *)shellstruct->head_envp->content)->full_str);
	free(((t_envlist *)shellstruct->head_envp->content)->left_part);
	free(((t_envlist *)shellstruct->head_envp->content)->right_part);
}

int	edit_pwds(t_shellstruct *shellstruct)
{
	t_list	*tmp;
	char	*tmp_str;
	char	*tmp_path;

	tmp_str = NULL;
	tmp = shellstruct->head_envp;
	while (shellstruct->head_envp)
	{
		if (ft_strcmp(((t_envlist *)shellstruct->head_envp->content)->left_part, \
			"PWD") == 0)
		{
			tmp_path = getcwd(NULL, 0);
			tmp_str = ft_strjoin("PWD=", tmp_path);
			free_env_list_content(shellstruct);
			add_content_list(shellstruct->head_envp->content, tmp_str);
			shellstruct->new_env = make_array_envp(shellstruct);
			free (tmp_str);
			free(tmp_path);
			break ;
		}
		shellstruct->head_envp = shellstruct->head_envp->next;
	}
	shellstruct->head_envp = tmp;
	edit_pwds_two(shellstruct, tmp_str, tmp);
	return (0);
}

int	cd(t_shellstruct *shellstruct, char **cmd_tmp)
{
	free(shellstruct->current_path);
	shellstruct->current_path = getcwd(NULL, 8);
	if (ft_strcmp("cd", cmd_tmp[0]) == 0)
	{
		if (!cmd_tmp[1])
		{
			printf("Invalid input, give argument\n");
			g_exit_code = 1;
			return (1);
		}
		if (chdir(cmd_tmp[1]))
		{
			printf("%s: No such file or directory\n", cmd_tmp[1]);
			g_exit_code = 1;
			return (1);
		}
		edit_pwds(shellstruct);
		g_exit_code = 0;
		return (1);
	}
	return (0);
}
