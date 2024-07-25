/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:06:36 by abesneux          #+#    #+#             */
/*   Updated: 2024/07/25 17:37:43 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

typedef struct s_all
{
	char		*input;
	char		**splited_input;
	char		*pwd;
}				t_all;

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_PIPE,
	TOKEN_OPTION,
	TOKEN_INPUT_REDIRECT,
	TOKEN_OUTPUT_REDIRECT,
	TOKEN_APPEND_REDIRECT,
	TOKEN_DOUBLE_QUOTES,
	TOKEN_SINGLE_QUOTES,
	TOKEN_UNKNOWN
}				TokenType;

typedef struct s_token
{
	char		*value;
	TokenType	type;
}				t_token;

// INTIALISATION
void			shell_loop(t_all *all, t_token *tokens);

// UTILS ALL FUNCTIONS
int				reset_all(t_all *all);
void			init_all(t_all *all);
void			free_tab(char **tab);

//UTILS INPUT
char 			*read_and_trim_input(void);
char 			**split_input(char *input);
void 			process_command(char *command, t_token *tokens, t_all *all);

// EXECUTION
void			execute_command(char *cmd, char **env);

int				check_syntax(char **splited_input);
int 			check_semicolon(char *input);
int				has_unclosed_quotes(const char *input);
int				has_logical_operator(const char *input);
int				pipe_checker(const char *input);
void			update_quotes_count(char c, int *s_quotes, int *d_quotes);
int				is_space(char c);

//TOKENISATION
void			tokenize(t_all *all, t_token **tokens);
TokenType		identify_token(const char *input, int *length);
void		add_token(t_token **tokens, int *token_count, const char *value, TokenType type);

//SIGNALS
void    		init_signals(void);
void		    handle_sigint(int signal);


#endif
