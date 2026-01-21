/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:01:18 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 12:18:44 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	expand_ast(t_ast *root, t_shell *sh)
{
	if (!root)
		return ;
	if (root->type == NODE_CMD)
		expand_cmd((t_cmd *)root->content, sh);
	else if (root->type == NODE_REDIR)
		expand_redir((t_redir *)root->content, sh);
	expand_ast(root->left, sh);
	expand_ast(root->right, sh);
}
