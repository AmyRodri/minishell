/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 23:21:13 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/11 03:24:16 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_sequence(t_token **tokens)
{
	t_ast	*node;
	t_ast	*new;
	t_ast	*right;

	node = parse_or(tokens);
	while (*tokens && (*tokens)->type == TK_LIST)
	{
		*tokens = (*tokens)->next;
		right = parse_or(tokens);
		new = malloc(sizeof(t_ast));
		new->type = NODE_SEQ;
		new->left = node;
		new->right = right;
		new->content = NULL;
		node = new;
	}
	return (node);
}
