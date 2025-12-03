/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:51:35 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/03 19:20:08 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static void	environment(t_env_table *env, char *line, int *i)
{
	char	*key_word;
	char	*value;
	int		j;

	j = *i;
	while (line[j] != ' ' && line[j])
		j++;
	key_word = ft_substr(line, *i + 1, (j - *i) - 1);
	value = env_get(env, key_word);
	printf("%s", value);
	*i = j;
}

void	echo(t_env_table *env, char *flag, char *line)
{
	int	i;
	int	flag_n;

	(void)env;
	if (!ft_strcmp(flag, "-n"))
	{
		i = 8;
		flag_n = 0;
	}
	else
	{
		i = 5;
		flag_n = 1;
	}
	while (line[i])
	{
		if (line[i] == '$')
			environment(env, line, &i);
		printf("%c", line[i]);
		i++;
	}
	if (flag_n)
		printf("\n");
}
