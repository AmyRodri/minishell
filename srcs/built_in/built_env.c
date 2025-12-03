/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:59:58 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/03 13:24:52 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	print_env(t_env_table *env)
{
	char	**new_env;
	int		i;

	new_env = env_export(env);
	i = 0;
	while (new_env[i])
		printf("%s\n", new_env[i++]);
}
