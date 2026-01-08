/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:26:52 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/08 16:50:42 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	apply_redirect(t_redir *redir)
{
	int		fd;

	while (redir)
	{
		if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("Minishell: open");
			return (-1);
		}
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("Minishell: dup2");
			close(fd);
			return (-1);
		}
		close(fd);
		redir = redir->next;
	}
	return (0);
}

int	handle_redirect(t_ast *redir_node, t_env_table *env)
{
	t_redir	*redir_list;
	pid_t	pid;
	int		status;

	redir_list = (t_redir *)redir_node->content;
	if (!redir_list)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		if (apply_redirect(redir_list) == -1)
			exit(1);
		status = execute_ast(redir_node->left, env);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}
