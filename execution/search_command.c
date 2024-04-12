/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 12:16:17 by bde-meij          #+#    #+#             */
/*   Updated: 2023/01/13 11:02:11 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

char	*search_list(t_shellstruct *shellstruct, int look_for)
{
	char	*found;
	t_list	*tmp;

	tmp = shellstruct->head_token;
	while (shellstruct->head_token->next)
	{
		if (((t_tokenlist *)shellstruct->head_token->content)->token == look_for)
		{
			found = ((t_tokenlist *)shellstruct->head_token->content)->str;
			shellstruct->head_token = tmp;
			return (found);
		}
		shellstruct->head_token = shellstruct->head_token->next;
	}
	shellstruct->head_token = tmp;
	return (NULL);
}

int	cmd_length(t_shellstruct *shellstruct, int nth_instance)
{
	t_list	*tmp;
	int		length;
	int		i;

	i = 1;
	length = 1;
	tmp = shellstruct->head_token;
	while ((shellstruct->head_token->next) && (i <= nth_instance))
	{
		if (((t_tokenlist *)shellstruct->head_token->content)->token == PIPE)
			i++;
		if (i == nth_instance && \
			(((t_tokenlist *)shellstruct->head_token->content)->token == CMD || \
			((t_tokenlist *)shellstruct->head_token->content)->token == CMD_OPTION))
			length++;
		shellstruct->head_token = shellstruct->head_token->next;
	}
	shellstruct->head_token = tmp;
	return (length);
}

char	**make_cmd_with_option(t_shellstruct *shellstruct, char **cmd)
{
	int	n;

	n = 1;
	cmd[0] = protec(ft_strdup \
	(((t_tokenlist *)shellstruct->head_token->content)->str));
	while (shellstruct->head_token->next)
	{
		if (((t_tokenlist *)shellstruct->head_token->content)->token == CMD_OPTION)
		{
			cmd[n] = protec(ft_strdup \
			(((t_tokenlist *)shellstruct->head_token->content)->str));
			n++;
		}
		if (((t_tokenlist *)shellstruct->head_token->content)->token == PIPE)
			break ;
		shellstruct->head_token = shellstruct->head_token->next;
	}
	return (cmd);
}

char	**search_cmd_loop(t_shellstruct *shellstruct, char **cmd, int nth_instance)
{
	int	i;

	i = 1;
	while (shellstruct->head_token->next)
	{
		if (((t_tokenlist *)shellstruct->head_token->content)->token == PIPE)
			i++;
		if ((i == nth_instance) && \
			(((t_tokenlist *)shellstruct->head_token->content)->token == CMD))
			return (make_cmd_with_option(shellstruct, cmd));
		if (shellstruct->head_token->next)
			shellstruct->head_token = shellstruct->head_token->next;
	}
	return (cmd);
}

char	**search_cmd(t_shellstruct *shellstruct, int nth_instance)
{
	char	**cmd;
	int		length;
	t_list	*tmp;
	
	tmp = shellstruct->head_token;
	length = cmd_length(shellstruct, nth_instance);
	cmd = protec(ft_calloc(sizeof(char *), length + 1));
	cmd[length] = NULL;
	cmd = search_cmd_loop(shellstruct, cmd, nth_instance);
	shellstruct->head_token = tmp;
	return (cmd);
}
