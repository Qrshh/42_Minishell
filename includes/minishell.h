/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:06:36 by abesneux          #+#    #+#             */
/*   Updated: 2024/08/09 21:46:42 by abesneux         ###   ########.fr       */
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

typedef enum e_token
{
	WORD,
	PIPE,
	RIGHT,
	DOUBLE_RIGHT,
	LEFT,
	DOUBLE_LEFT,
}t_token;

// INTIALISATION
void			shell_loop(t_all *all);

// UTILS ALL FUNCTIONS
int				reset_all(t_all *all);
void			init_all(t_all *all);
void			free_tab(char **tab);
int			    ft_isspace(char c);
t_word			*check_space(t_word *list);

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
int 			is_operator(char c);

//SIGNALS
void    		init_signals(void);
void		    handle_sigint(int signal);
void		    handle_sigquit(int signal);

//TESTS
void    print_list(t_word *list);


#endif
