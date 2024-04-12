/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:29:22 by rbrune            #+#    #+#             */
/*   Updated: 2023/01/18 11:53:56 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

int	check_for_valid_ident(char **cmd, int *i);

int	replace_env_arg(t_shellstruct *shellstruct, char **cmd, int i, t_list *tmp)
{
	free(((t_envlist *)shellstruct->head_envp->content)->full_str);
	free(((t_envlist *)shellstruct->head_envp->content)->left_part);
	free(((t_envlist *)shellstruct->head_envp->content)->right_part);
	add_content_list(shellstruct->head_envp->content, cmd[i]);
	shellstruct->head_envp = tmp;
	return (1);
}

void	add_content_list(t_envlist *envp_list, char *var)
{
	char		**split_var;

	split_var = protec(ft_split(var, '='));
	envp_list->full_str = protec(ft_strdup(var));
	envp_list->left_part = protec(ft_strdup(split_var[0]));
	if (split_var[1])
	{
		envp_list->right_part = protec(ft_strdup(split_var[1]));
	}
	else
		envp_list->right_part = NULL;
	free_dubarray(split_var);
}

char	**copy_env_to_darray(t_shellstruct *shellstruct, char **new_env)
{
	int	i;

	i = 0;
	while (shellstruct->head_envp)
	{
		new_env[i] = protec(ft_strdup(((t_envlist *) \
		shellstruct->head_envp->content)->full_str));
		shellstruct->head_envp = shellstruct->head_envp->next;
		i++;
	}
	return (new_env);
}

char	**make_array_envp(t_shellstruct *shellstruct)
{
	char	**new_env;
	int		i;
	t_list	*tmp;

	tmp = shellstruct->head_envp;
	i = 0;
	ft_free_old_env_array(shellstruct->new_env);
	while (shellstruct->head_envp)
	{
		shellstruct->head_envp = shellstruct->head_envp->next;
		i++;
	}
	shellstruct->head_envp = tmp;
	new_env = protec(malloc(sizeof(char **) * (i + 1)));
	new_env[i] = NULL;
	new_env = copy_env_to_darray(shellstruct, new_env);
	shellstruct->head_envp = tmp;
	return (new_env);
}

int	add_envp(t_shellstruct *shellstruct, char **cmd, int i, t_list *tmp)
{
	char	**splt_chk_str;
	int		flag;

	while (cmd[i])
	{
		flag = 0;
		splt_chk_str = protec(ft_split(cmd[i], '='));
		while (shellstruct->head_envp)
		{
			if (ft_strcmp(((t_envlist *)shellstruct->head_envp-> \
			content)->left_part, splt_chk_str[0]) == 0)
			{
				replace_env_arg(shellstruct, cmd, i, tmp);
				flag = 1;
				break ;
			}
			shellstruct->head_envp = shellstruct->head_envp->next;
		}
		shellstruct->head_envp = tmp;
		if (!cmd[i])
			break ;
		if (!check_for_valid_ident(cmd, &i) && flag == 0)
		{
			ft_lstadd_back(&shellstruct->head_envp, protec \
			(ft_lstnew(add_envlist(cmd[i]))));
		}
		free_dubarray(splt_chk_str);
		i++;
	}
	shellstruct->head_envp = tmp;
	shellstruct->new_env = make_array_envp(shellstruct);
	return (0);
}
