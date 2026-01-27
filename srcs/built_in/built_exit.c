/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:58:03 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/27 15:44:34 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static int	ft_is_numeric(const char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_exit(t_shell *sh, t_cmd *cmd)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->argc == 1)
	{
		sh->exit_code = sh->last_status;
		sh->should_exit = 1;
		return (0);
	}
	if (!ft_is_numeric(cmd->argv[1]))
	{
		ft_putendl_fd("Minishell: exit: numeric argument required",
			STDERR_FILENO);
		sh->exit_code = 255;
		sh->should_exit = 1;
		return (0);
	}
	if (cmd->argc > 2)
	{
		ft_putendl_fd("Minishell: exit: too many arguments",
			STDERR_FILENO);
		return (1);
	}
	sh->exit_code = ft_atoi(cmd->argv[1]) % 256;
	sh->should_exit = 1;
	return (sh->exit_code);
}
