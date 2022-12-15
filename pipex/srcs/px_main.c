/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:02:53 by wxuerui           #+#    #+#             */
/*   Updated: 2022/10/15 16:21:53 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "px_header.h"

void	err_exit(char *err_msg, int option)
{
	if (option == OPTION_PERROR)
		perror(err_msg);
	else
		ft_putstr_fd(err_msg, STDERR_FILENO);
	exit(1);
}

void	get_fds(int ac, char **av, t_pipe *pipex)
{
	pipex->heredoc = -1;
	pipex->hd_eof = NULL;
	if (ft_strlen(av[1]) == 8 && ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		pipex->fd_in = open("hd", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->fd_in == -1)
			err_exit(ERR_HEREDOC, OPTION_OTHER);
		pipex->heredoc = 1;
		pipex->hd_eof = av[2];
	}
	else
	{
		pipex->fd_in = open(av[1], O_RDONLY);
		if (pipex->fd_in == -1)
			err_exit(ERR_INFILE, OPTION_PERROR);
	}
	if (pipex->heredoc == -1)
		pipex->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		pipex->fd_out = open(av[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (pipex->fd_out == -1)
		err_exit(ERR_OUTFILE, OPTION_PERROR);
}

void	here_doc(t_pipe *pipex)
{
	char	*line;
	int		num_commands;
	int		i;

	num_commands = ft_lstsize(pipex->commands);
	while (1)
	{
		i = -1;
		while (++i < num_commands - 1)
			ft_putstr_fd("pipe ", STDOUT_FILENO);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (ft_strlen(line) == ft_strlen(pipex->hd_eof) + 1
			&& ft_strncmp(line, pipex->hd_eof, ft_strlen(pipex->hd_eof)) == 0)
			break ;
		ft_putstr_fd(line, pipex->fd_in);
		free(line);
	}
	free(line);
	close(pipex->fd_in);
	pipex->fd_in = open("hd", O_RDONLY);
	if (pipex->fd_in == -1)
		err_exit(ERR_HEREDOC, OPTION_OTHER);
}

void	px_prepare(int ac, char **av, t_pipe *pipex)
{
	int	i;

	get_fds(ac, av, pipex);
	i = 2;
	if (pipex->heredoc != -1)
		i++;
	pipex->commands = ft_lstnew((void *)(av[i]));
	while (++i < ac - 1)
		ft_lstadd_back(&(pipex->commands), ft_lstnew((void *)(av[i])));
	pipex->lst_head = pipex->commands;
	if (pipex->heredoc != -1)
		here_doc(pipex);
}

int	main(int ac, char **av, char **envp)
{
	t_pipe	pipex;

	if (ac < 5)
		err_exit(ERR_USAGE, OPTION_OTHER);
	px_prepare(ac, av, &pipex);
	px_process(envp, &pipex);
	finish(envp, &pipex);
	return (0);
}
