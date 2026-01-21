/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unalias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:41:52 by kamys             #+#    #+#             */
/*   Updated: 2026/01/21 16:24:58 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

int	unalias(t_alias_table *alias, t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->argv[i])
	{
		if (!alias_get(alias, cmd->argv[i]))
		{
			ft_putstr_fd("unalias: ", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd(": not found\n", 2);
			i++;
			ret = 1;
			continue ;
		}
		alias_unset(alias, cmd->argv[i]);
		i++;
	}
	return (ret);
}
