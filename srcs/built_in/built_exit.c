/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:58:03 by amyrodri          #+#    #+#             */
/*   Updated: 2026/02/04 16:17:50 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

#include <limits.h>

static int	ft_atoll_safe(const char *s, long long *out)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s)
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		if (res > (LLONG_MAX - (*s - '0')) / 10)
			return (0);
		res = res * 10 + (*s - '0');
		s++;
	}
	*out = res * sign;
	return (1);
}

static int	normalize_exit_code(long long n)
{
	int	code;

	code = n % 256;
	if (code < 0)
		code += 256;
	return (code);
}

int	ft_exit(t_shell *sh, t_cmd *cmd)
{
	long long	val;

	if (cmd->argc == 1)
	{
		sh->exit_code = sh->last_status;
		sh->should_exit = 1;
		return (0);
	}
	if (!ft_atoll_safe(cmd->argv[1], &val))
	{
		ft_putendl_fd("Minishell: exit: numeric argument required",
			STDERR_FILENO);
		sh->exit_code = 2;
		sh->should_exit = 1;
		return (0);
	}
	if (cmd->argc > 2)
	{
		ft_putendl_fd("Minishell: exit: too many arguments",
			STDERR_FILENO);
		return (1);
	}
	sh->exit_code = normalize_exit_code(val);
	sh->should_exit = 1;
	return (sh->exit_code);
}
