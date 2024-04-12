/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:33:03 by rbrune        #+#    #+#                 */
/*   Updated: 2023/01/10 13:33:38 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 65 || str[i] > 122 || (str[i] > 90 && str[i] < 97))
			if (str[i] != 95)
				return (1);
		i++;
	}
	return (0);
}

void	ft_free_old_env_array(char **old_env)
{
	int	i;

	i = 0;
	if (old_env)
	{
		while (old_env[i])
		{
			free (old_env[i]);
			i++;
		}
		free (old_env);
	}
}

t_envlist	*make_content_list(char **envp, int i)
{
	t_envlist	*envp_list;
	char		**split_envp;

	envp_list = protec(malloc(sizeof(t_envlist)));
	split_envp = protec(ft_split(envp[i], '='));
	envp_list->full_str = protec(ft_strdup(envp[i]));
	envp_list->left_part = protec(ft_strdup(split_envp[0]));
	if (split_envp[1])
		envp_list->right_part = protec(ft_strdup(split_envp[1]));
	free_dubarray(split_envp);
	return (envp_list);
}

void	make_envp_list(char **envp, t_shellstruct *shellstruct)
{
	int		i;

	i = 0;
	shellstruct->current_path = NULL;
	shellstruct->head_envp = NULL;
	i++;
	while (envp[i])
		ft_lstadd_back(&shellstruct->head_envp, \
		protec(ft_lstnew(make_content_list(envp, i++))));
	shellstruct->new_env = make_array_envp(shellstruct);
}

int	check_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] != '\'' && str[i] != '\"')
		{
			return (0);
		}
		i++;
	}
	free(str);
	return (1);
}
