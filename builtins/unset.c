/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:07:43 by rbrune        #+#    #+#                 */
/*   Updated: 2022/12/09 12:52:33 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

int	del_list_begin(t_shellstruct *shellstruct, t_list *tmp_head)
{
	shellstruct->head_envp = shellstruct->head_envp->next;
	free(((t_envlist *)shellstruct->head_envp->content)->full_str);
	free(((t_envlist *)shellstruct->head_envp->content)->left_part);
	free(((t_envlist *)shellstruct->head_envp->content)->right_part);
	free(((t_envlist *)shellstruct->head_envp->content));
	free(tmp_head);
	shellstruct->new_env = make_array_envp(shellstruct);
	return (1);
}

int	del_list_mid_and_end(t_shellstruct *shellstruct, t_list	*tmp_head)
{
	t_list	*tmp;

	tmp = NULL;
	if (!shellstruct->head_envp->next->next)
	{
		free(((t_envlist *)shellstruct->head_envp->next->content)->full_str);
		free(((t_envlist *)shellstruct->head_envp->next->content)->left_part);
		free(((t_envlist *)shellstruct->head_envp->next->content)->right_part);
		free(((t_envlist *)shellstruct->head_envp->next->content));
		free(shellstruct->head_envp->next);
		shellstruct->head_envp->next = NULL;
	}
	else
	{
		tmp = shellstruct->head_envp->next->next;
		free(((t_envlist *)shellstruct->head_envp->next->content)->full_str);
		free(((t_envlist *)shellstruct->head_envp->next->content)->left_part);
		free(((t_envlist *)shellstruct->head_envp->next->content)->right_part);
		free(((t_envlist *)shellstruct->head_envp->next->content));
		free(shellstruct->head_envp->next);
		shellstruct->head_envp->next = tmp;
	}
	shellstruct->head_envp = tmp_head;
	shellstruct->new_env = make_array_envp(shellstruct);
	return (1);
}

void	del_list(t_shellstruct *shellstruct, char**cmd_tmp, int i, t_list *tmp_head)
{
	while (cmd_tmp[i])
	{
		if (ft_strcmp(((t_envlist *)shellstruct->head_envp->content) \
		->left_part, cmd_tmp[i]) == 0)
			del_list_begin(shellstruct, tmp_head);
		while (shellstruct->head_envp->next)
		{
			if (ft_strcmp(((t_envlist *)shellstruct->head_envp->next->content) \
			->left_part, cmd_tmp[i]) == 0)
				del_list_mid_and_end(shellstruct, tmp_head);
			shellstruct->head_envp = shellstruct->head_envp->next;
		}		
		shellstruct->head_envp = tmp_head;
		i++;
	}
}

int	unset(t_shellstruct *shellstruct, char **cmd_tmp)
{
	t_list	*tmp_head;
	int		i;

	i = 1;
	tmp_head = shellstruct->head_envp;
	if (ft_strcmp("unset", cmd_tmp[0]) == 0)
	{
		del_list(shellstruct, cmd_tmp, i, tmp_head);
		free_dubarray (cmd_tmp);
		g_exit_code = 0;
		return (1);
	}
	return (0);
}
