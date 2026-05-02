/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:17:15 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:07:36 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef ECHOCTL
#  define ECHOCTL 0x00000040
# endif

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "parser.h"
# include "environment.h"
# include "executor.h"
# include "errors/errors.h"
# include "builtins/builtins.h"
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>

typedef struct s_token_list		t_token_list;
typedef struct s_env			t_env;
typedef struct s_red_files		t_red_files;
typedef struct s_rebuild_info	t_rebuild_info;

typedef struct s_count
{
	int	pipe_count;
	int	redir_in_count;
	int	redir_out_count;
	int	append_count;
	int	heredoc_count;
}	t_count;

typedef struct s_minishell
{
	char			*input;
	t_env			*envp;
	char			**tokens;
	int				exit_status;
	char			**export;
	t_token_list	*token_list;
	t_count			*count;
}		t_minishell;

void		ft_ctrl_c(int sig);
t_env		*init_env(char **envp);
void		init_signal(void);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
int			is_numeric(const char *str);
int			calloc_minishell(t_minishell *minishell);
int			execute_command(t_minishell *minishell);
void		reset_counts(t_minishell *minishell);
void		set_ignore_signals(void);
void		set_default_signals(void);
void		simple_signal_handler(int sign);
void		heredoc_sigint_handler(int signo);
int			check_signal(void);
int			has_redirect(t_minishell *minishell);
int			has_heredoc(t_minishell *minishell);
int			is_tmp_redirect(t_token_list *tmp);
void		skip_spaces(const char *input, int *idx);
t_minishell	*get_data(void);
void		set_data(t_minishell *ms);

#endif