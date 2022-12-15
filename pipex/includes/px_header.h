/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:01:18 by wxuerui           #+#    #+#             */
/*   Updated: 2022/10/15 16:21:18 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_HEADER_H
# define PX_HEADER_H

# include "libft.h"
# include <string.h>

/* Error Messages */
# define ERR_USAGE "Usage: ./pipex infile cmd1 cmd2 outfile.\n"
# define ERR_HEREDOC "Heredoc error"
# define ERR_INFILE "infile"
# define ERR_OUTFILE "outfile"
# define ERR_EXECVE "Execve error"

/* Structures */
typedef struct s_pipe {
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	t_list	*commands;
	t_list	*lst_head;
	char	**command_av;
	int		heredoc;
	char	*hd_eof;
}	t_pipe;

/* Other defines */
# define READ 0
# define WRITE 1
# define OPTION_PERROR 1
# define OPTION_OTHER 2

/* function prototypes */
void	err_exit(char *err_msg, int option);
void	px_process(char **envp, t_pipe *pipe);
void	finish(char **envp, t_pipe *pipex);
void	execute_command(char **envp, t_pipe *pipex);

#endif
