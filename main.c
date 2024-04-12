/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 12:40:31 by rbrune            #+#    #+#             */
/*   Updated: 2023/03/07 14:54:04 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellhead.h"

int	g_exit_code;

int	unclosed_quotes(char *str);
int	check_blank(char *str);

int	count_pipes(t_shellstruct *shellstruct)
{
	t_list	*tmp;
	int		n_pipes;

	tmp = shellstruct->head_token;
	n_pipes = 1;
	while (shellstruct->head_token->next)
	{
		if (((t_tokenlist *)shellstruct->head_token->content)->token == PIPE)
			n_pipes++;
		shellstruct->head_token = shellstruct->head_token->next;
	}
	shellstruct->head_token = tmp;
	return (n_pipes);
}

int	lexer(t_shellstruct *shellstruct, char *str)
{
	if (unclosed_quotes(str))
	{
		free(str);
		return (131);
	}
	shellstruct->compare_str = " <>|\'\" ";
	shellstruct->line = str;
	add_history(shellstruct->line);
	if (ft_strcmp(str, "\"\"") == 0 || ft_strcmp(str, "\'\'") == 0)
		return (print_errors(127), 127);
	shellstruct->line = parse_dollar_sign(shellstruct->line, shellstruct);
	if (check_blank(shellstruct->line))
		return (1);
	if (!*shellstruct->line)
		return (1);
	shellstruct->line_len = ft_strlen(shellstruct->line);
	shellstruct->tokenarr = protec(malloc((shellstruct->line_len + 1) * sizeof(int)));
	shellstruct->tokenarr[shellstruct->line_len] = '\0';
	tokenize_input(shellstruct);
	enlist(shellstruct, 0);
	shellstruct->n_pipes = count_pipes(shellstruct);
	free(shellstruct->tokenarr);
	return (0);
}

int	instructor(t_shellstruct *shellstruct, char *str)
{
	if (str == NULL)
	{
		printf("BigHell: ");
		printf("\x1b[1A");
		printf("exit\n");
		exit(0);
	}
	if (str[0] < 32)
	{
		free(str);
		return (0);
	}
	if (lexer(shellstruct, str))
		return (0);
	cmd_exe(shellstruct);
	free(shellstruct->line);
	return (0);
}

int	main(int ac, char *av[], char **envp)
{
	struct termios	term_struct;
	t_shellstruct		shellstruct;

	(void)ac;
	(void)av;
	g_exit_code = 0;
	shellstruct.new_env = NULL;
	shellstruct.in = dup(0);
	shellstruct.out = dup(1);
	tcgetattr(STDIN_FILENO, &term_struct);
	tcgetattr(STDOUT_FILENO, &term_struct);
	tcgetattr(STDERR_FILENO, &term_struct);
	term_struct.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
	make_envp_list(envp, &shellstruct);
	signal(SIGINT, general_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		instructor(&shellstruct, readline("BigHell: "));
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &term_struct);
		tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term_struct);
		tcsetattr(STDERR_FILENO, TCSAFLUSH, &term_struct);
	}
}
