/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/20 20:06:36 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/20 18:25:44 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PATH_MAX 4096
# define ARENA_SIZE 50000

typedef struct s_arena
{
	char	*memory;
	size_t	used;
	size_t	size;
}	t_arena;

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
	V_ENV,
}	t_token;

typedef struct s_environement
{
	char	**env_cpy;
	int		equal;
	char	*name;
	char	*value;
}	t_env;

typedef struct s_word
{
	char			*str;
	t_token			token;
	int				index;
	bool			has_space_before;
	bool			has_space_after;
	struct s_word	*next;
	struct s_word	*previous;
}	t_word;

typedef struct s_token_list
{
	t_word	*head;
	t_word	*current;
}	t_token_list;

typedef struct s_cmd
{
	char			*input;
	t_word			*list;
	char			**args;
	char			**post_pipe;
	int				old_out;
	int				old_inf;
	int				nb_pipes;
	struct s_cmd	*next;	
	struct s_cmd	*previous;	
}	t_cmd;

extern int	g_exit_status;

// INTIALISATION
void	shell_loop(t_cmd *cmd, t_env *env, t_arena *arena);

// UTILS cmd FUNCTIONS
int		reset_cmd(t_cmd *cmd); // refaire
void	init_cmd_1(t_cmd *cmd);
void	free_tab(char **tab);
void	skip_whitespaces(char *input, int *i);
int		is_token_redir(t_word *list);
int		count_pipes(t_word *list);
void	free_cmd(t_cmd *cmd);
void	free_env(t_env *env);
void	free_list(t_word *list);

// UTILS INPUT
char	*read_and_trim_input(t_arena *arena);

// EXECUTION
void	execute_command(t_cmd *cmd, t_env *env, t_arena *arena);
void	pre_execute(t_cmd *cmd, t_env *env, char *input, t_arena *arena);
char	*getpath(char *cmd, char **env, t_arena *arena);
int		execute_builtin(t_cmd *cmd, t_env *env, t_arena *arena);
int		is_a_builtin(char *cmd);
char	**copy_env(char **main_env, t_arena *arena);
int		check_syntax(t_cmd *cmd);
int		has_unclosed_quotes(const char *input);
int		has_logical_operator(const char *input);
int		pipe_checker(const char *input);
void	update_quotes_count(char c, int *s_quotes, int *d_quotes);
int		is_space(char c);
int		is_a_sep(char const *set, char c);
char	**list_to_array(t_word *list, t_arena *arena);
t_cmd	*init_cmd(t_cmd *cmd, t_arena *arena);
int		count_list(t_word *list);
int		handle_operator_exec(t_cmd *cmd, t_arena *arena);
void	simple_exec(t_cmd *cmd, t_env *env, char *path, t_arena *arena);
void	handle_parent_process(int *fd_in, int pipefd[2]);
void	handle_child_process(t_cmd *cmd, t_env *env, int pipefd[2],
			t_arena *arena);
void	prepare_next_pipe(t_cmd *cmd, t_arena *arena);
void	exec(t_cmd *cmd, t_env *env, t_arena *arena);

t_word	*handle_dollar(t_cmd *cmd, t_env *env, t_arena *arena);
void	heredoc_handler(int signum);
void	sigaction_handle(void);
int		handle_heredoc(t_word *list, t_arena *arena);
int		check_space_before(char *input, int *i);
int		check_space_after(char *input, int i);
int		redir_heredoc(t_word *list);
void	restore_sigint(void);
void	sigaction_handle(void);
void	wait_children(pid_t *pids, int i);
int		handle_single_pipe(t_cmd *cmd, t_env *env,
			pid_t *pid, t_arena *arena);
void	manage_fds(int *fd_in, int pipefd[2]);
void	setup_pipe(int pipefd[2]);

// TOKENISATION

// LEXING
t_word	*init_lex(char *str, t_token token, int flag[2], t_arena *arena);
void	handle_single_quote(char *input, int *i, t_token_list *tokens,
			t_arena *arena);
void	handle_double_quote(char *input, int *i, t_token_list *tokens,
			t_arena *arena);
void	handle_operator(char *input, int *i, t_token_list *tokens,
			t_arena *arena);
void	handle_word(char *input, int *i, t_token_list *tokens, t_arena *arena);
void	handle_env(char *input, int *i, t_token_list *tokens, t_arena *arena);
int		word_len(char *input, int i);
void	add_to_list(t_word **head, t_word **current, t_word *new_node);
int		is_operator(char c);
void	merge_quoted_tokens(t_word **head, t_arena *arena);

// SIGNALS
void	init_signals(void);
void	handle_sigint(int signal);
void	handle_sigquit(int signal);

// BUILTINS
int		my_exit(t_cmd *cmd, t_env *env, t_arena *arena);
int		my_export(t_cmd *cmd, t_env *env, t_arena *arena);
int		my_cd(t_cmd *cmd, t_env *env, t_arena *arena);
int		my_echo(t_cmd *cmd);
int		my_pwd(void);
int		my_env(t_cmd *cmd, t_env *env);
int		my_unset(t_cmd *cmd, t_env *env, t_arena *arena);
void	sort_tab(char **env_cpy);
int		count_tab(char **env_cpy);
int		is_valid_name(char *name, int name_len);
int		update_or_create_var(t_env *env, char **env_cpy, t_arena *arena);
char	*create_env_var_string(t_env *env, char *name, char *value,
			t_arena *arena);
int		extract_name_value(char *arg, t_env *env, t_arena *arena);
char	*merge_content(t_word *current, t_arena *arena);
char	*find_var_value(t_env *env, char *var_name);

void	arena_init(t_arena *arena, size_t size);
void	free_arena(t_arena *arena);
void	*arena_alloc(t_arena *arena, size_t size);

//UTILS
char	*aft_strtrim(char const *s1, char const *set, t_arena *arena);
char	*aft_strdup(const char *src, t_arena *arena);
char	*aft_strndup(char *str, unsigned int n, t_arena *arena);
char	*aft_substr(char const *s, unsigned int start, size_t len,
			t_arena *arena);
char	*aft_strjoin(char const *s1, char const *s2, t_arena *arena);
char	*aft_itoa(int n, t_arena *arena);

#endif
