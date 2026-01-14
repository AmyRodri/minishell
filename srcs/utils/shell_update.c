/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:00:38 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/14 12:10:19 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	shell_upadate(t_shell *sh)
{
	char	*shlvl;
	char	*new_shlvl;
	int		lvl;

	shlvl = env_get(sh->env, "SHLVL");
	if (!shlvl)
		lvl = 1;
	else
		lvl = ft_atoi(shlvl) + 1;
	if (lvl < 0)
		lvl = 1;
	new_shlvl = ft_itoa(lvl);
	env_set(sh->env, "SHLVL", new_shlvl);
	free(new_shlvl);
}
