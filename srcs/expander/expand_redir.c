/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:46 by kamys             #+#    #+#             */
/*   Updated: 2026/01/21 15:13:54 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_redir(t_redir *redir, t_shell *sh)
{
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
			redir->file = expand_word(redir->file, sh);
		redir = redir->next;
	}
}
