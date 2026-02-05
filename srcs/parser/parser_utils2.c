/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by kamys             #+#    #+#             */
/*   Updated: 2026/02/05 00:00:18 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redir(t_token_type type)
{
	return (type == TK_REDIR_IN
		|| type == TK_REDIR_OUT
		|| type == TK_APPEND
		|| type == TK_HEREDOC);
}

int	is_logic_op(t_token_type type)
{
	return (type == TK_PIPE
		|| type == TK_AND
		|| type == TK_OR
		|| type == TK_LIST);
}
