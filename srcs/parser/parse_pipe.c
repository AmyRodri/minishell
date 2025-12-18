/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:14:30 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/11 03:14:52 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_pipe(t_token **tokens)
{
	t_ast	*node;
	t_ast	*new;
	t_ast	*right;

	node = parse_simple(tokens);
	while (*tokens && (*tokens)->type == TK_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_simple(tokens);
		new = malloc(sizeof(t_ast));
		new->type = NODE_PIPE;
		new->left = node;
		new->right = right;
		new->content = NULL;
		node = new;
	}
	return (node);
}
