/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:26:40 by cassunca          #+#    #+#             */
/*   Updated: 2026/02/05 01:33:36 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_cmd_in_pipeline(t_ast *node, t_shell *sh)
{
	t_cmd	*cmd;
	char	*path;

	cmd = node->content;
	expand_cmd(cmd, sh);
	if (cmd->redir)
		if (apply_redirect(cmd->redir) < 0)
			exit(1);
	if (is_builtin(cmd->argv))
		exit(exec_builtin_pipeline(cmd, sh));
	path = resolve_path(cmd->argv[0], sh->env);
	if (!path)
	{
		ft_putstr_fd("Minishell: '", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd("' : command not found\n", 2);
		free_ast(sh->root);
		clean_up(sh);
		exit(127);
	}
	exec_child(path, cmd->argv, sh->env);
}

static void	child_pipe_setup(int prev_fd, int fd[2], int i, int n)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (i < n - 1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

static void	wait_pipeline(pid_t last_pid, t_shell *sh)
{
	pid_t	pid;
	int		status;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
			sh->last_status = status;
		pid = wait(&status);
	}
}

static pid_t	run_pipeline(t_ast **cmds, int n, t_shell *sh)
{
	int		i;
	int		prev_fd;
	int		fd[2];
	pid_t	pid;
	pid_t	last_pid;

	i = 0;
	prev_fd = -1;
	last_pid = -1;
	while (i < n)
	{
		if (i < n - 1 && pipe(fd) < 0)
			break ;
		pid = fork();
		if (pid == 0)
		{
			child_pipe_setup(prev_fd, fd, i, n);
			exec_pipe_child(cmds[i], cmds, sh);
		}
		parent_pipe_cleanup(&prev_fd, fd, i, n);
		last_pid = pid;
		i++;
	}
	return (last_pid);
}

int	handle_pipe(t_ast *pipe_node, t_shell *sh)
{
	t_ast	**cmds;
	int		n;
	int		i;
	pid_t	last_pid;

	n = count_pipe_cmds(pipe_node);
	cmds = malloc(sizeof(t_ast *) * n);
	i = 0;
	collect_pipe_cmds(pipe_node, cmds, &i);
	signal(SIGINT, sig_handler_cmd);
	signal(SIGQUIT, SIG_IGN);
	last_pid = run_pipeline(cmds, n, sh);
	wait_pipeline(last_pid, sh);
	free(cmds);
	setup_sig();
	return (WEXITSTATUS(sh->last_status));
}
