/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rbrune <rbrune@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 16:09:12 by rbrune        #+#    #+#                 */
/*   Updated: 2023/01/16 16:07:10 by rbrune        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

int	ft_isdigit_str(char *str);
int	replace_env_arg(t_shellstruct *shellstruct, char **cmd, int i, int *flag);

t_envlist	*add_envlist(char *var)
{
	t_envlist	*envp_list;

	envp_list = protec(malloc(sizeof(t_envlist *) * 3));
	add_content_list(envp_list, var);
	return (envp_list);
}

int	check_for_valid_ident(char **cmd, int *i)
{
	char	**splt_chk_str;

	splt_chk_str = protec(ft_split(cmd[*i], '='));
	if (ft_isdigit_str(splt_chk_str[0]) == 1)
	{
		g_exit_code = 1;
		printf("%s: %s: not a valid identifier\n", \
		cmd[0], cmd[*i]);
		free_dubarray (splt_chk_str);
		return (1);
	}
	free_dubarray (splt_chk_str);
	return (0);
}

void	order_envp(t_shellstruct *shellstruct)
{
	int		i;
	char	*tmp_char;

	i = 0;
	while (shellstruct->new_env[i + 1])
	{
		if (ft_strcmp(shellstruct->new_env[i], shellstruct->new_env[i + 1]) > 0)
		{
			tmp_char = shellstruct->new_env[i + 1];
			shellstruct->new_env[i + 1] = shellstruct->new_env[i];
			shellstruct->new_env[i] = tmp_char;
			i = 0;
		}
		i++;
	}
	i = 0;
	while (ft_strcmp(shellstruct->new_env[i], shellstruct->new_env[i + 1]) > 0)
	{
		tmp_char = shellstruct->new_env[i + 1];
		shellstruct->new_env[i + 1] = shellstruct->new_env[i];
		shellstruct->new_env[i] = tmp_char;
		i++;
	}
}

void	print_export(t_shellstruct *shellstruct)
{
	int		i;

	order_envp(shellstruct);
	i = 0;
	while (shellstruct->new_env[i])
		printf("declare -x %s\n", shellstruct->new_env[i++]);
}

int	_export(t_shellstruct *shellstruct, char **cmd_tmp)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = shellstruct->head_envp;
	if (ft_strcmp("export", cmd_tmp[0]) == 0 && cmd_tmp[1] == NULL)
	{
		print_export(shellstruct);
		free_dubarray (cmd_tmp);
		g_exit_code = 0;
		return (1);
	}
	if (ft_strcmp("export", cmd_tmp[0]) == 0)
	{
		add_envp(shellstruct, cmd_tmp, i, tmp);
		free_dubarray (cmd_tmp);
		return (1);
	}
	return (0);
}
