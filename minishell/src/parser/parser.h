/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 07:59:23 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/19 01:11:08 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_minishell	t_minishell;
typedef struct s_env		t_env;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_COMMAND,
	TOKEN_FILE,
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				quotes;
}				t_token;

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*prev;
	struct s_token_list	*next;
}				t_token_list;

typedef struct s_rebuild_info
{
	int	prefix_len;
	int	start;
	int	new_token_len;
}				t_rebuild_info;

t_token_list	*tokenizer(t_minishell *minishell);
int				split_input(t_minishell *minishell);
void			parse_tokens(t_minishell *minishell, t_token_list *tmp);
void			add_token_to_list(t_token_list **token_list,
					t_token *current_token);
int				single_quotes(t_minishell *minishell,
					int *i, t_token **current_token);
int				double_quotes(t_minishell *minishell,
					int *i, t_token **current_token);
int				money_money(t_minishell *minishell, char **tmp);
void			remove_quotes_from_input(t_minishell *minishell,
					int j_pos, int i_pos, char quote);
int				merge_with_previous_token(t_minishell *minishell,
					t_token **current_token);
int				handle_after_quote_text(t_minishell *minishell,
					int *i, int j);
char			*replace_tmp(char *tmp, int *j, char *status);
int				is_that_word(t_minishell *ms,
					int *i, t_token **tok, int *counter);
int				process_quote_content(t_minishell *minishell,
					int *i, int *start);
int				handle_quote_merging(t_minishell *minishell,
					int *i, t_token **tok, int j);
int				handle_dollar_in_quotes(t_minishell *minishell,
					int *i, int *start);
void			append_to_last_token(t_minishell *minishell,
					const char *result);
int				rebuild_input_update_index(t_minishell *minishell,
					t_rebuild_info info, int *index);
char			*collect_after_quot(const char *input,
					int start_idx, int *out_end_pos);
int				is_redirection(char *value);

#endif
