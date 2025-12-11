/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:15:03 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/11 06:10:02 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_cmd(t_ast *cmd_node, char **envp)
{
	t_cmd	*cmd;
	char	*path_cmd;

	cmd = (t_cmd *)cmd_node->content;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd->argv) && is_exit(cmd->argv))
		return (execute_exit(cmd->argv, envp));
	if (is_builtin(cmd->argv))
		return (execute_builtin(cmd->argv));
	path_cmd = resolve_path(cmd->argv[0], envp);
	if (!path_cmd)
		path_cmd = cmd->argv[0];
	return (exec_simple_command(path_cmd, cmd->argv, envp));
}
