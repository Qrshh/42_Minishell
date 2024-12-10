/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/09 17:12:28 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/18 17:21:59 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_list(t_word *list)
{
	int		count;
	t_word	*temp;

	count = 0;
	temp = list;
	while (temp && ft_strcmp(temp->str, "|") != 0)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	count_pipes(t_word *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->token == PIPE)
			count++;
		list = list->next;
	}
	return (count);
}

void	manage_fds(t_cmd *cmd, int *fd_in, int pipefd[2])
{
	if(cmd->nb_pipes == 0)
		close(pipefd[0]);
	close(pipefd[1]);
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = pipefd[0];
}

void	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) < 0)
		exit(EXIT_FAILURE);
}
