/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:13:51 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/11 03:14:11 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse_and(t_token **tokens)
{
	t_ast	*node;
	t_ast	*new;
	t_ast	*right;

	node = parse_pipe(tokens);
	while (*tokens && (*tokens)->type == TK_AND)
	{
		*tokens = (*tokens)->next;
		right = parse_pipe(tokens);
		new = malloc(sizeof(t_ast));
		new->type = NODE_AND;
		new->left = node;
		new->right = right;
		new->content = NULL;
		node = new;
	}
	return (node);
}
