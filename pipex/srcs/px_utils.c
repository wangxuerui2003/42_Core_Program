/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:20:51 by wxuerui           #+#    #+#             */
/*   Updated: 2022/10/15 16:21:43 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_header.h"

void	finish(char **envp, t_pipe *pipex)
{
	dup2(pipex->pipe[READ], STDIN_FILENO);
	dup2(pipex->fd_out, STDOUT_FILENO);
	execute_command(envp, pipex);
	close(pipex->fd_in);
	close(pipex->fd_out);
	close(pipex->pipe[READ]);
	close(pipex->pipe[WRITE]);
}

char	*get_command_path(char **command, char **envp, t_pipe *pipex)
{
	char	*full_path;
	char	**paths;
	char	*cmd_path;
	int		i;

	(void)pipex;
	if (access(command[0], F_OK) == 0)
		return (command[0]);
	i = -1;
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	paths = ft_split(*envp + 5, ':');
	i = -1;
	while (paths[++i] != NULL)
	{
		cmd_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(cmd_path, command[0]);
		free(cmd_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	ft_free2darr((void **)paths);
	return (NULL);
}

void	execute_command(char **envp, t_pipe *pipex)
{
	char	**command;
	char	*path;

	command = ft_split((char *)pipex->commands->content, ' ');
	path = get_command_path(command, envp, pipex);
	if (path == NULL)
	{
		ft_putstr_fd(command[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (execve(path, command, envp) == -1)
	{
		err_exit(ERR_EXECVE, OPTION_PERROR);
	}
	ft_free2darr((void **)command);
	free(path);
}

void	px_process(char **envp, t_pipe *pipex)
{
	int		temp_fd;
	pid_t	child;

	temp_fd = -1;
	while (pipex->commands->next != NULL)
	{
		pipe(pipex->pipe);
		child = fork();
		if (child == 0)
		{
			if (temp_fd != -1)
				dup2(temp_fd, STDIN_FILENO);
			else
				dup2(pipex->fd_in, STDIN_FILENO);
			dup2(pipex->pipe[WRITE], STDOUT_FILENO);
			execute_command(envp, pipex);
		}
		if (temp_fd != -1)
			close(temp_fd);
		close(pipex->pipe[WRITE]);
		temp_fd = pipex->pipe[READ];
		pipex->commands = pipex->commands->next;
	}
	if (pipex->heredoc == 1)
		unlink("hd");
}
