/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
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

void process_pipe(t_cmd *cmd, t_env *env)
{
    pid_t  *pids;
    int    pipefd[2];
    int    fd_in;
    int    i;

    pids = malloc((cmd->nb_pipes + 1) * sizeof(pid_t));
    if (!pids)
        return;
    fd_in = 0;
    i = 0;
    while (cmd->nb_pipes >= 0)
    {
        prepare_next_pipe(cmd);
        if (pipe(pipefd) < 0)
            return;
        pids[i] = fork();
        if (pids[i] < 0)
            return;
        if (pids[i] == 0)
            handle_child_process(cmd, env, pipefd, fd_in);
		close(pipefd[1]);
		if(fd_in != 0)
			close(fd_in);
		fd_in = pipefd[0];
        cmd->args = cmd->post_pipe;
        cmd->nb_pipes--;
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        int status;
        waitpid(pids[j], &status, 0);
        if (WIFEXITED(status))
            g_exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_exit_status = 128 + WTERMSIG(status);
    }
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
		builtin_exec(cmd, env, path);
	signal(SIGQUIT, SIG_IGN);
}
