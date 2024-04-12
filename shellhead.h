/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shellhead.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-meij <bde-meij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 12:41:04 by rbrune            #+#    #+#             */
/*   Updated: 2023/03/07 14:55:12 by bde-meij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef shellstruct_H
# define shellstruct_H

// Printf
# include <stdio.h>
// Free
# include <stdlib.h>
// Write
# include <unistd.h>
// Readline
# include <readline/readline.h>
# include <readline/history.h>
// Signal
# include <signal.h>
// Libft
# include "libft/libft.h"
// Strerror
# include <string.h>
// Directory's
# include <dirent.h>
// Termios
# include <termios.h>
//open_close
# include <sys/wait.h>
# include <fcntl.h>

# define INFILE_OP 1
# define OUTFILE_OP 2
# define PIPE 3
# define QUOTE 4
# define DOUBLE_QUOTE 5
# define SPACES 6
# define B_SLASH 7
# define HERE_DOC_OP 11
# define OUT_APPEND_OP 22
# define INFILE 10
# define OUTFILE 20
# define HERE_DOC 110
# define OUTFILE_WITH_APPEND 220
# define WORD -2
# define SINGLE_QUOTED_STR -3
# define DOUBLE_QUOTED_STR -4
# define CMD 50
# define CMD_OPTION 51
# define YES 100
# define NO -100

extern int	g_exit_code;

typedef struct s_envlist
{
	char				*full_str;
	char				*left_part;
	char				*right_part;
}t_envlist;

typedef struct s_tokenlist
{
	char				*str;
	int					token;
}t_tokenlist;

typedef struct s_shellstruct
{
	char				*line;
	char				**new_env;
	char				*current_path;
	int					n_pipes;
	int					pipe_section;
	char				*compare_str;
	int					*tokenarr;
	int					in;
	int					out;
	size_t				line_len;
	struct s_list		*head_token;
	struct s_list		*head_envp;
}t_shellstruct;

// in_out_put
void		unlink_heredocs(t_shellstruct *shellstruct);
void		make_heredocs(t_shellstruct *shellstruct);
int			open_outfiles(t_shellstruct *shellstruct);
int			open_infiles(t_shellstruct *shellstruct);

// tokenize
char		*parse_dollar_sign(char *input, t_shellstruct *shellstruct);
int			check_expand(char *tmp_str, t_shellstruct *shellstruct);
int			tokenize_input(t_shellstruct *shellstruct);
void		enlist(t_shellstruct *shellstruct, int i);

// utilities
void		skip_space(t_shellstruct *shellstruct, size_t *i, size_t *n, \
				int *check_spc);
char		*cmd_env_path(char *cmd, t_shellstruct *shellstruct, int i);
char		**search_cmd(t_shellstruct *shellstruct, int nth_instance);
void		rl_replace_line(const char *text, int clear_undo);
void		add_content_list(t_envlist *envp_list, char *var);
void		make_envp_list(char **envp, t_shellstruct *shellstruct);
char		*search_list(t_shellstruct *shellstruct, int look_for);
char		**make_array_envp(t_shellstruct *shellstruct);
void		ft_free_old_env_array(char **old_env);
void		free_dubarray(char **dubarray);
void		free_token_list(t_list *list);
void		reset_std(t_shellstruct *shellstruct);
void		print_errors(int error_code);
void		*protec(void *ptr);
int			guard_fork(int i);
int			guard_fd(int i);

// execute
void		command_loop(t_shellstruct *shellstruct, int pipe_in, int pipe_out[2]);
void		last_cmd(t_shellstruct *shellstruct, int pipe_in, int *pid);
char		**search_cmd(t_shellstruct *shellstruct, int nth_instance);
void		first_cmd(t_shellstruct *shellstruct, int pipe_out[2]);
int			cmd_exe(t_shellstruct *shellstruct);

// builtins
int			add_envp(t_shellstruct *shellstruct, char **cmd_tmp, int i, t_list *tmp);
int			_export(t_shellstruct *shellstruct, char **cmd_tmp);
int			unset(t_shellstruct *shellstruct, char **cmd_tmp);
int			env(t_shellstruct *shellstruct, char **cmd_tmp);
int			cd(t_shellstruct *shellstruct, char **cmd_tmp);
int			check_if_builtin(t_shellstruct *shellstruct);
int			builtins(t_shellstruct *shellstruct);
int			ft_echo(char **cmd_tmp);
t_envlist	*add_envlist(char *var);

// signals
void		quit_process_signal(int sig);
void		process_signal(int sig);
void		general_signal(int i);

#endif