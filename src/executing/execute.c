/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/14 15:45:14 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_join(char *path, char *bin)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (ft_strchr(path, 0) + ft_strchr(bin, 0)
				+ 2));
	i = -1;
	j = -1;
	while (path[++j])
		joined[++i] = path[j];
	joined[++i] = '/';
	j = -1;
	while (bin[++j])
		joined[++i] = bin[j];
	joined[++i] = 0;
	return (joined);
}

char	*getpath(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && ft_strchr(path, ':') > -1)
	{
		dir = ft_strndup(path, ft_strchr(path, ':'));
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strchr(path, ':') + 1;
	}
	return (cmd);
}

void	exec(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (is_a_builtin(cmd->args[0]))
	{
		g_exit_status = execute_builtin(cmd, env);
		return ;
	}
	else
	{
		path = getpath(cmd->args[0], env->env_cpy);
		execve(path, cmd->args, env->env_cpy);
	}
}

void	process_pipe(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		pipefd[2];
	int		fd_in;
	int		i;

	fd_in = 0;
	i = 0;
	while (i <= cmd->nb_pipes)
	{
		while (cmd->list && cmd->list->token != PIPE)
			cmd->list = cmd->list->next;
		if (cmd->list && cmd->list->token == PIPE)
		{
			cmd->post_pipe = list_to_array(cmd->list->next);
			cmd->list = cmd->list->next;
		}
		else
			cmd->post_pipe = NULL;
		if (i <= cmd->nb_pipes && pipe(pipefd) < 0)
			return ;
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			dup2(fd_in, STDIN_FILENO);
			if (i < cmd->nb_pipes)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			if (is_a_builtin(cmd->args[0]))
			{
				g_exit_status = execute_builtin(cmd, env);
				exit(g_exit_status);
			}
			else
				exec(cmd, env);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(pipefd[1]);
			fd_in = pipefd[0];
		}
		cmd->args = cmd->post_pipe;
		i++;
	}
}

void	execute_command(t_cmd *cmd, t_env *env)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (cmd->args[0] == NULL)
		return ;
	path = getpath(cmd->args[0], env->env_cpy);
	if (cmd && cmd->nb_pipes > 0)
	{
		process_pipe(cmd, env);
	}
	else
	{
		if (is_a_builtin(cmd->args[0]))
		{
			g_exit_status = execute_builtin(cmd, env);
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			execve(path, cmd->args, env->env_cpy);
			perror("Command not found");
			exit(127);
		}
		else if (pid < 0)
			perror("Erreur de fork");
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else
				g_exit_status = 128 + WTERMSIG(status);
		}
	}
}
