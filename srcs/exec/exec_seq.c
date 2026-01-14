/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_seq.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:45:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/14 15:43:49 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_sequence(t_ast *root, t_shell *sh)
{
	int	status;

	status = execute_ast(root->left, sh);
	status = execute_ast(root->right, sh);
	return (status);
}
