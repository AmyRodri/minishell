/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:28:27 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/14 15:43:14 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	handle_and(t_ast *root, t_shell *sh)
{
	int	status;

	status = execute_ast(root->left, sh);
	if (status == 0)
		return (execute_ast(root->right, sh));
	return (status);
}
