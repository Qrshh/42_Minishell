/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:28:53 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/21 13:09:16 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_pipe(t_cmd *cmd, t_env *env, t_word *current)
{
    int pipefd[2];
    static int i = 0;
    int fd_in = STDIN_FILENO;

    if (pipe(pipefd) == -1) {
        perror("Erreur lors de la création du pipe");
        return (1);
    }

    // Première commande (ls)
    cmd->pid[i] = fork();
    if (cmd->pid[i] < 0) {
        perror("Erreur lors du fork");
        return (1);
    } else if (cmd->pid[i] == 0) { // Processus enfant
        if (current->previous && dup2(fd_in, STDIN_FILENO) == -1) {
            perror("Erreur dup2 fd_in");
            exit(1);
        }
        close(pipefd[0]); // Ferme le côté lecture du pipe
        if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
            perror("Erreur dup2 pipefd[1]");
            exit(1);
        }
        close(pipefd[1]); // Ferme le côté écriture après duplication
		execute_command(cmd, env);
    }
    // Fermer le côté écriture dans le parent
    close(pipefd[1]);
    // Deuxième commande (wc -l)
    cmd->pid[++i] = fork();
    if (cmd->pid[i] < 0) {
        perror("Erreur lors du fork");
        return (1);
    } else if (cmd->pid[i] == 0) { // Processus enfant
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("Erreur dup2 pipefd[0]");
            exit(1);
        }
        close(pipefd[0]); // Ferme le côté lecture après duplication
		cmd->args = cmd->post_pipe;
		cmd->post_pipe = NULL;
		execute_command(cmd, env);
    }
    close(pipefd[0]); // Ferme le côté lecture dans le parent
    waitpid(cmd->pid[0], NULL, 0);
    waitpid(cmd->pid[1], NULL, 0);
    return (0);
}

int	handle_outfile(t_word *list)
{
	int	fd;

	fd = -1;
	if (list->token == RIGHT)
		fd = open(list->next->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (list->token == DOUBLE_RIGHT)
		fd = open(list->next->str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("outfile : error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("pipe : error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	handle_infile(t_word *list)
{
	int	fd;

	fd = -1;
	if (list->token == LEFT)
		fd = open(list->next->str, O_RDONLY);
	if (fd < 0)
		return ((ft_putstr_fd("infile : error\n", STDERR_FILENO), 1));
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
		return ((ft_putstr_fd("pipe : error\n", STDERR_FILENO), 1));
	if (fd >= 0)
		close(fd);
	return (0);
}

int	handle_operator_exec(t_cmd *cmd, t_env *env)
{
	t_word	*current;

	current = cmd->list;
	while (current)
	{
		if (current->token == RIGHT || current->token == DOUBLE_RIGHT)
		{
			if (handle_outfile(current))
				return (1);
		}
		else if (current->token == LEFT)
		{
			if (handle_infile(current))
				return (1);
		}
		else if (current->token == DOUBLE_LEFT)
		{
			if (handle_heredoc(current->next->str))
				return (1);
			if (redir_heredoc())
				return (1);
		}
		else if (current->token == PIPE)
		{
			cmd->post_pipe = list_to_array(current->next);
			if(handle_pipe(cmd, env, current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}
