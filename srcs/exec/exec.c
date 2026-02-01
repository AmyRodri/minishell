/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:36:20 by cassunca          #+#    #+#             */
/*   Updated: 2026/02/01 14:10:27 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_ast(t_ast *root, t_shell *sh)
{
	if (!root)
		return (0);
	else if (root->type == NODE_PIPE)
		return (handle_pipe(root, sh));
	else if (root->type == NODE_CMD)
		return (execute_cmd(root, sh));
	else if (root->type == NODE_AND)
		return (handle_and(root, sh));
	else if (root->type == NODE_OR)
		return (handle_or(root, sh));
	if (root->type == NODE_SUB)
		return (execute_sub(root, sh));
	if (root->type == NODE_SEQ)
		return (handle_sequence(root, sh));
	return (1);
}

static void	exec_child(char *path_cmd, char **av, t_env_table *env)
{
	execve(path_cmd, av, env_export(env));
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(av[0], 2);
	if (errno == ENOENT)
		ft_putstr_fd(": command not found\n", 2);
	else
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	exit(127);
}

static int	wait_child(pid_t pid, int status)
{
	int	sig;

	while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + sig);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	exec_simple_command(t_redir *redir, char *path_cmd,
	char **av, t_env_table *env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("Minishell: fork\n");
		return (1);
	}
	if (pid == 0)
	{
		if (redir)
			if (apply_redirect(redir) < 0)
				exit (1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_child(path_cmd, av, env);
	}
	return (wait_child(pid, status));
}
