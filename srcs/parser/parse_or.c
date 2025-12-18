/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_or.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:13:03 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/11 03:13:33 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_or(t_token **tokens)
{
	t_ast	*node;
	t_ast	*new;
	t_ast	*right;

	node = parse_and(tokens);
	while (*tokens && (*tokens)->type == TK_OR)
	{
		*tokens = (*tokens)->next;
		right = parse_and(tokens);
		new = malloc(sizeof(t_ast));
		new->type = NODE_OR;
		new->left = node;
		new->right = right;
		new->content = NULL;
		node = new;
	}
	return (node);
}
