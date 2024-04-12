/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:39:57 by bde-meij          #+#    #+#             */
/*   Updated: 2022/12/07 13:34:19 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shellhead.h"

void	process_signal(int sig)
{
	(void) sig;
	g_exit_code = 130;
	printf("\n");
}

void	quit_process_signal(int sig)
{
	printf("Quit: %d\n", sig);
}

void	quit_here_doc_signal(int sig)
{
	printf("Quit: %d\n", sig);
	exit(131);
}

void	ctrl_c_herdoc(int sig)
{
	(void) sig;
	printf("\n");
	exit(1);
}

void	general_signal(int i)
{
	(void)i;
	printf("\n");
	g_exit_code = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
