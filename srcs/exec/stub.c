/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:05:57 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/11 04:25:13 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char **av)
{
	(void)av;
	return (0);
}

int	execute_builtin(char **av)
{
	(void)av;
	printf("DEBUG: Executing mocked builtin.\n");
	return (0);
}

char	*resolve_path(char *cmd, char **envp)
{
	(void)envp;
	if (strcmp(cmd, "ls") == 0)
		return (strdup("/bin/ls"));
	if (strcmp(cmd, "cat") == 0)
		return (strdup("/bin/cat"));
	return (strdup(cmd));
}


