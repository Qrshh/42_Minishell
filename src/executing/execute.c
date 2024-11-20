/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/20 15:09:53 by ozdemir          ###   ########.fr       */
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
	path = getpath(cmd->args[0], env->env_cpy);
	if (!path || execve(path, cmd->args, env->env_cpy) == -1)
	{
		perror("Command not found");
		exit(127);
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
	while (cmd->nb_pipes >= 0)
	{
		prepare_next_pipe(cmd);
		if (i <= cmd->nb_pipes && pipe(pipefd) < 0)
			return ;
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
			handle_child_process(cmd, env, pipefd, fd_in);
		else
			handle_parent_process(&fd_in, pipefd, pid);
		cmd->args = cmd->post_pipe;
		cmd->nb_pipes--;
	}
}

void	execute_command(t_cmd *cmd, t_env *env)
{
	char	*path;

	if (cmd->args[0] == NULL)
		return ;
	path = getpath(cmd->args[0], env->env_cpy);
	if (cmd && cmd->nb_pipes > 0)
		process_pipe(cmd, env);
	else
		builtin_exec(cmd, env, path);
	signal(SIGQUIT, SIG_IGN);
}
