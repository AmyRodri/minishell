/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:37:20 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/26 14:44:02 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	**argv_add(char **argv, char *word)
{
	int		i;
	char	**new;

	i = 0;
	while (argv && argv[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (argv && argv[i])
	{
		new[i] = argv[i];
		i++;
	}
	new[i++] = ft_strdup(word);
	new[i] = NULL;
	free(argv);
	return (new);
}

int	match_pattern(char *p, char *s)
{
	if (!*p && !*s)
		return (1);
	if (*p == '*')
		return (match_pattern(p + 1, s)
			|| (*s && match_pattern(p, s + 1)));
	if (*p == '?')
		return (*s && match_pattern(p + 1, s + 1));
	if (*p == *s)
		return (match_pattern(p + 1, s + 1));
	return (0);
}
