/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_title.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:21:37 by kamys             #+#    #+#             */
/*   Updated: 2026/02/03 12:02:37 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_terminal_title(char *title)
{
	if (!title)
		return ;
	write(1, "\033]0;", 4);
	write(1, title, ft_strlen(title));
	write(1, "\007", 1);
}

void	update_title(t_shell *sh)
{
	char	*title;

	title = parse_ps1(sh->env, "%u@minishell:%d");
	set_terminal_title(title);
	free(title);
}
