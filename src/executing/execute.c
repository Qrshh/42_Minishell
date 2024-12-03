/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/08 22:06:12 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/20 17:42:32 by abesneux         ###   ########.fr       */
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

	path = getpath(cmd->args[0], env->env_cpy);
	if (!path || execve(path, cmd->args, env->env_cpy) == -1)
	{
		printf("Command not found\n");
		free(path);
		free_cmd(cmd);
		free_env(env);
		exit(127);
	}
}

void	process_pipe(t_cmd *cmd, t_env *env)
{
	pid_t	*pids;
	int		pipefd[2];
	int		i;

	pids = malloc((cmd->nb_pipes + 1) * sizeof(pid_t));
	if (!pids)
		return ;
	i = 0;
	while (cmd->nb_pipes >= 0)
	{
		if (handle_single_pipe(cmd, env, pipefd, &pids[i]) < 0)
			return ;
		cmd->args = cmd->post_pipe;
		cmd->nb_pipes--;
		i++;
	}
	wait_children(pids, i);
	free(pids);
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
		simple_exec(cmd, env, path);
	signal(SIGQUIT, SIG_IGN);
}
