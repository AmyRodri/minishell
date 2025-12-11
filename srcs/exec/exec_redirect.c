/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:26:52 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/11 04:28:23 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	apply_redirect(t_redir *redirs)
{
	int		fd;
	t_redir	*curr;

	curr = redirs;
	while (curr)
	{
		fd = -1;
		if (curr->type == REDIR_IN)
			fd = open(curr->file, O_RDONLY);
		else if (curr->type == REDIR_OUT)
			fd = open(curr->file, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
		if (fd == -1)
		{
			perror(curr->file);
			exit(1);
		}
		if (curr->type == REDIR_IN
			|| curr->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		curr = curr->next;
	}
}

int	handle_redirect(t_ast *redir_node, char **envp)
{
	t_redir	*redirs;
	pid_t	pid;
	int		status;

	status = 0;
	redirs = (t_redir *)redir_node->content;
	pid = fork();
	if (pid == -1)
	{
		perror("Minishell: fork");
		return (1);
	}
	if (pid == 0)
	{
		apply_redirect(redirs);
		exit(execute_ast(redir_node->left, envp));
	}
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Minishell: waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
