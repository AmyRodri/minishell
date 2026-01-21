/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:05:34 by kamys             #+#    #+#             */
/*   Updated: 2026/01/21 15:14:10 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_cmd(t_cmd *cmd, t_shell *sh)
{
	int	i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		cmd->argv[i] = expand_word(cmd->argv[i], sh);
		i++;
	}
}
