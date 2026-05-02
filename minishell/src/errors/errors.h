/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:05:54 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:08:05 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_CMD_NOT_FOUND		127
# define ERR_NUM_ARG_REQ		255
# define ERR_NO_FILE			127
# define ERR_PERMISSION_DENIED	126
# define ERR_INVALID_ARG		2
# define ERR_SYNTAX				258
# define ERR_FILESYSTEM			1

typedef struct s_minishell	t_minishell;

int	report_error(t_minishell *minishell, const char *msg, int code);
int	report_cmd_not_found(t_minishell *minishell, const char *cmd);
int	report_num_arg_req(t_minishell *minishell, const char *cmd, int len);
int	report_no_such_file(t_minishell *minishell, const char *cmd);
int	report_perm_denied(t_minishell *minishell, const char *cmd);
int	report_is_a_directory(t_minishell *minishell, const char *cmd);
int	report_not_valid(t_minishell *minishell, const char *cmd);

#endif