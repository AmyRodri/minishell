/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:49 by kamys             #+#    #+#             */
/*   Updated: 2026/01/21 15:15:26 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	handle_tilde(char **res, char *s, int *i, t_shell *sh)
{
	if (*i == 0 || s[*i - 1] == ' ')
		append_str(res, env_get(sh->env, "HOME"));
	else
		append_char(res, s[*i]);
	(*i)++;
}
