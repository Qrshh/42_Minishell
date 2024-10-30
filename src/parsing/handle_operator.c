/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:28:53 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/30 19:44:31 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_outfile(t_word *list)
{
	int	fd;

	fd = -1;
	if (list->token == RIGHT)
	{
		if(!is_operator(list->next->str[0]))
			fd = open(list->next->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
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

int	handle_operator_exec(t_cmd *cmd)
{
	t_word	*current;
	int 	i;
	char 	*tmp;

	i = 0;
	current = cmd->list;
	cmd->post_pipe = malloc(sizeof(char *) * (cmd->nb_pipes + 1));
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
			ft_printf("test");
			current = current->next;
			tmp = ft_strdup("");  // Initialise tmp comme une chaîne vide

			// Construire la commande jusqu’au prochain PIPE ou la fin de la liste
			while (current && current->token != PIPE)
			{
				char *temp = ft_strjoin(tmp, current->str);
				tmp = temp;  // Réassigner la nouvelle concaténation à tmp

				current = current->next;
				if (current && current->token != PIPE)  // Ajout d'un espace entre les mots
				{
					temp = ft_strjoin(tmp, " ");
					free(tmp);
					tmp = temp;
				}
			}

			cmd->post_pipe[i++] = tmp;  // Ajouter la commande complète dans post_pipe
			tmp = NULL;  // Réinitialiser tmp pour la prochaine commande
		}
		cmd->post_pipe[i] = NULL;
		current = current->next;
	}
	return (0);
}

