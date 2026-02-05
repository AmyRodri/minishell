/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 01:28:39 by kamys             #+#    #+#             */
/*   Updated: 2026/02/05 01:31:42 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_builtin_pipeline(t_cmd *cmd, t_shell *sh)
{
	int		status;

	status = execute_builtin(cmd, sh);
	free_ast(sh->root);
	clean_up(sh);
	return (status);
}

int	count_pipe_cmds(t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
		return (count_pipe_cmds(node->left) + count_pipe_cmds(node->right));
	return (1);
}

void	collect_pipe_cmds(t_ast *node, t_ast **arr, int *i)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		collect_pipe_cmds(node->left, arr, i);
		collect_pipe_cmds(node->right, arr, i);
	}
	else
		arr[(*i)++] = node;
}

void	exec_pipe_child(t_ast *node, t_ast **cmds, t_shell *sh)
{
	free(cmds);
	exec_cmd_in_pipeline(node, sh);
	exit(1);
}

void	parent_pipe_cleanup(int *prev_fd, int fd[2], int i, int n)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (i < n - 1)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}
