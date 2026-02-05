/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:15:03 by cassunca          #+#    #+#             */
/*   Updated: 2026/02/05 00:23:40 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char **av)
{
	if (!av || !av[0])
		return (0);
	if (ft_strcmp(av[0], "cd") == 0 || ft_strcmp(av[0], "echo") == 0
		|| ft_strcmp(av[0], "env") == 0 || ft_strcmp(av[0], "export") == 0
		|| ft_strcmp(av[0], "pwd") == 0 || ft_strcmp(av[0], "unset") == 0
		|| ft_strcmp(av[0], "alias") == 0 || ft_strcmp(av[0], "unalias") == 0
		|| ft_strcmp(av[0], "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_shell *sh)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (cd(sh->env, cmd));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (echo(sh->env, cmd));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (print_env(sh->env, cmd));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (export(sh->env, cmd));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (pwd(sh->env, cmd));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (unset(sh->env, cmd));
	if (ft_strcmp(cmd->argv[0], "alias") == 0)
		return (alias(sh->aliases, cmd));
	if (ft_strcmp(cmd->argv[0], "unalias") == 0)
		return (unalias(sh->aliases, cmd));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(sh, cmd));
	return (127);
}

static int	exec_builtin_with_redirect(t_cmd *cmd, t_shell *sh)
{
	int	status;
	int	stdin_bakcup;
	int	stdout_bakcup;

	stdin_bakcup = dup(STDIN_FILENO);
	stdout_bakcup = dup(STDOUT_FILENO);
	if (cmd->redir)
		if (apply_redirect(cmd->redir) < 0)
			return (restore_fds(stdin_bakcup, stdout_bakcup), 1);
	status = execute_builtin(cmd, sh);
	restore_fds(stdin_bakcup, stdout_bakcup);
	return (status);
}

static int	exec_redir_only(t_cmd *cmd)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (cmd->redir)
	{
		if (apply_redirect(cmd->redir) < 0)
			return (restore_fds(stdin_backup, stdout_backup), 1);
	}
	restore_fds(stdin_backup, stdout_backup);
	return (0);
}

int	execute_cmd(t_ast *cmd_node, t_shell *sh)
{
	t_cmd	*cmd;
	char	*path_cmd;
	int		status;

	cmd = (t_cmd *)cmd_node->content;
	if (cmd && cmd->redir && (!cmd->argv || !cmd->argv[0]))
		return (exec_redir_only(cmd));
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	expand_cmd(cmd, sh);
	if (is_builtin(cmd->argv))
		return (exec_builtin_with_redirect(cmd, sh));
	path_cmd = resolve_path(cmd->argv[0], sh->env);
	if (!path_cmd || cmd->argv[0][0] == '\0')
	{
		ft_putstr_fd("Minishell: '", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd("' : command not found\n", 2);
		return (127);
	}
	signal(SIGINT, sig_handler_cmd);
	status = exec_simple_command(cmd->redir, path_cmd, cmd->argv, sh->env);
	setup_sig();
	env_set(sh->env, "_", path_cmd);
	return (free(path_cmd), status);
}
