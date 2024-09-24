/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:06:36 by abesneux          #+#    #+#             */
/*   Updated: 2024/09/24 13:18:35 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

# define PATH_MAX 4096

typedef enum e_token
{
	WORD,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	RIGHT,
	DOUBLE_RIGHT,
	LEFT,
	DOUBLE_LEFT,
}						t_token;

typedef struct s_environement
{
	char				**env_cpy;
}						t_env;

typedef struct s_word
{
	char				*str;
	t_token				token;
	int					index;
	struct s_word		*next;
	struct s_word		*previous;
}						t_word;

typedef struct s_cmd
{
	t_word				*list;
	char				**args;
	struct s_cmd		*pipe;
	struct s_cmd		*previous;
}						t_cmd;

typedef struct s_all
{
	char				*input;
	char				**splited_input;
	t_word				*list;
}						t_all;

extern int				g_exit_status;

// INTIALISATION
void					shell_loop(t_all *all, t_env *env);

// UTILS ALL FUNCTIONS
int						reset_all(t_all *all);
void					init_all(t_all *all);
void					free_tab(char **tab);
void					skip_whitespaces(char *input, int *i);

// UTILS INPUT
char					*read_and_trim_input(void);

// EXECUTION
void					execute_command(t_cmd *cmd, t_env *env);
void					pre_execute(t_word *list, t_env *env);
char					*getpath(char *cmd, char **env);
int						execute_builtin(t_cmd *cmd, t_env *env);
int						is_a_builtin(char *cmd);
char					**copy_env(char **main_env);
int						check_syntax(char *input);
int						has_unclosed_quotes(const char *input);
int						has_logical_operator(const char *input);
int						pipe_checker(const char *input);
void					update_quotes_count(char c, int *s_quotes,
							int *d_quotes);
int						is_space(char c);
char					**list_to_array(t_word *list);
t_cmd					*init_cmd(t_cmd *cmd, t_word *list);
int						count_list(t_word *list);

// TOKENISATION

// LEXING
t_word					*init_lex(char *str, t_token token);
void					handle_single_quote(char *input, int *i, t_word **head,
							t_word **current);
void					handle_operator(char *input, int *i, t_word **head,
							t_word **current);
void					handle_word(char *input, int *i, t_word **head,
							t_word **current);
int						word_len(char *input, int i);
int						is_operator(char c);

// SIGNALS
void					init_signals(void);
void					handle_sigint(int signal);
void					handle_sigquit(int signal);

// BUILTINS
int						my_exit(t_cmd *cmd);
int						my_export(t_cmd *cmd, t_env *env);
int						my_cd(t_cmd *cmd);
int						my_echo(t_cmd *cmd);
int						my_pwd(t_cmd *cmd);
int						my_env(t_cmd *cmd, t_env *env);
int						my_unset(t_cmd *cmd, t_env *env);
void					sort_tab(char **env_cpy);
int						count_tab(char **env_cpy);
// TESTS
void					print_list(t_all *all);

#endif
