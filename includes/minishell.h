/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:06:36 by abesneux          #+#    #+#             */
/*   Updated: 2024/06/12 15:26:30 by abesneux         ###   ########.fr       */
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

typedef struct s_all
{
	char	*input;
	char	*pwd;
}			t_all;

// INTIALISATION
void		shell_loop(t_all *all);

// UTILS ALL FUNCTIONS
int			reset_all(t_all *all);
void		init_all(t_all *all);

// EXECUTION
void		execute_command(char *cmd, char **env);

int			check_syntax(const char *input);
int			has_unclosed_quotes(const char *input);
int         has_logical_operator(const char *input);
int         pipe_checker(const char *input);
void        update_quotes_count(char c, int *s_quotes, int *d_quotes);
int         is_space(char c);

#endif
