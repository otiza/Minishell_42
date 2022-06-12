/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaiza <amaaiza@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:36:17 by amaaiza           #+#    #+#             */
/*   Updated: 2022/02/14 19:40:58 by amaaiza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	other(char **cmd1, t_as *as, t_command *cmd)
{
	pid_t	pid;
	int		status;

	g_main.isfork = 1;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		as->exitstat = WEXITSTATUS(status);
	}
	else
	{
		dup2(cmd->in, 0);
		dup2(cmd->out, 1);
		execve(get_cmd_path(cmd->args[0], as->env), cmd1, as->envp);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
}

void	ft_check(t_as *as, t_command *cmd)
{
	as->sigint = 1;
	if (as->cmds_size == 0 || cmd == NULL || cmd->args[0] == NULL)
		return ;
	else if (!strncmp(cmd->args[0], "help", 5))
		do_help();
	else if (!strncmp(cmd->args[0], "echo", 5))
		do_echo(as, cmd);
	else if (!strncmp(cmd->args[0], "exit", 5))
		ft_exit(as, cmd);
	else if (!strncmp(cmd->args[0], "pwd", 4))
		do_pwd(as, cmd);
	else if (!strncmp(cmd->args[0], "env", 4))
		do_env(as, cmd);
	else if (!strncmp(cmd->args[0], "cd", 3))
		do_cd(as, cmd);
	else if (!strncmp(cmd->args[0], "export", 7))
		do_export(as, cmd);
	else if (!strncmp(cmd->args[0], "unset", 6))
		do_unset(as, cmd);
	else
		other(cmd->args, as, cmd);
	g_main.isfork = 0;
}

void	mydup(t_as *as, int *fds, size_t cmd, int fd)
{
	if (cmd != 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	if (as->cmds_size - 1 != cmd)
		dup2(fds[1], 1);
	close(fds[1]);
	close(fds[0]);
}

void	ft_exitstatu(int *fd, int *fds, pid_t pid)
{
	if (pid == -1)
		ft_putstr_fd("error : fork failed\n", 2);
	else
	{
		if (*fd)
			close(*fd);
		close(fds[1]);
		*fd = fds[0];
	}
}

void	pipes(t_as *as)
{
	int		pipes[2];
	int		fd;
	pid_t	*pid;
	size_t	i;

	pid = malloc(sizeof(pid_t *) * (as->cmds_size));
	i = -1;
	while (++i < as->cmds_size)
	{
		pipe(pipes);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			mydup(as, pipes, i, fd);
			ft_check(as, as->cmds[i]);
			exit(as->exitstat);
		}
		ft_exitstatu(&fd, pipes, pid[i]);
	}
	close (fd);
	i = -1;
	while (++i < as->cmds_size)
		waitpid(pid[i], &as->exitstat, 0);
	free(pid);
	as->exitstat = WEXITSTATUS(as->exitstat);
}
