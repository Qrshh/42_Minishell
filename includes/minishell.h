/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:06:36 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/14 19:04:20 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

typedef enum e_token
{
	WORD,
	PIPE,
	RIGHT,
	DOUBLE_RIGHT,
	LEFT,
	DOUBLE_LEFT,
}t_token;

typedef struct s_word 
{
	char 			*str;
	t_token			token;
	int				index;
	struct s_word 	*next;
	struct s_word 	*previous;
}				t_word;

typedef struct s_cmd
{
	t_word		*list;
	struct s_cmd	*pipe;
	struct s_cmd	*previous;
}				t_cmd;

typedef struct s_all
{
	char		*input;
	char		**splited_input;
	t_word		*list;
}				t_all;



// INTIALISATION
void			shell_loop(t_all *all, char **env);

// UTILS ALL FUNCTIONS
int				reset_all(t_all *all);
void			init_all(t_all *all);
void			free_tab(char **tab);
void    		skip_whitespaces(char *input, int *i);


//UTILS INPUT
char 			*read_and_trim_input(void);

// EXECUTION
void			execute_command(char *cmd, char **env);

int				check_syntax(char *input);
int 			check_semicolon(char *input);
int				has_unclosed_quotes(const char *input);
int				has_logical_operator(const char *input);
int				pipe_checker(const char *input);
void			update_quotes_count(char c, int *s_quotes, int *d_quotes);
int				is_space(char c);

//TOKENISATION

//LEXING
t_word  		*init_lex(char *str, t_token token);
void		    handle_single_quote(char *input, int *i, t_word **head, t_word **current, char quote);
void		    handle_operator(char *input, int *i, t_word **head, t_word **current, char operator);
void    		handle_word(char *input, int *i, t_word **head, t_word **current, t_all *all);
int 			word_len(char *input, int i);
int 			is_operator(char c);

//SIGNALS
void    		init_signals(void);
void		    handle_sigint(int signal);
void		    handle_sigquit(int signal);

//TESTS
void			print_list(t_all *all);


#endif
