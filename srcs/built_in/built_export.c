/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:28:05 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/03 16:37:53 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

void	export(t_env_table *env, char *key_value)
{
	char	**split;
	char	*key;
	char	*value;

	if (!key_value)
	{
		print_env(env);
		return ;
	}
	split = ft_split(key_value, '=');
	if (!split || !split[0] || !split[1])
		return ;
	key = split[0];
	value = split[1];
	env_set(env, key, value);
}
