/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:09:00 by kamys             #+#    #+#             */
/*   Updated: 2026/01/21 15:14:34 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*expand_word(char *s, t_shell *sh)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			handle_single_quotes(&res, s, &i);
		else if (s[i] == '\"')
			handle_double_quotes(&res, s, &i, sh);
		else if (s[i] == '$')
			handle_dolar(&res, s, &i, sh);
		else if (s[i] == '~')
			handle_tilde(&res, s, &i, sh);
		else
			append_char(&res, s[i++]);
	}
	free(s);
	return (res);
}
