/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:56 by kamys             #+#    #+#             */
/*   Updated: 2026/02/02 18:25:00 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	pid_minishell(char	**res, int	*i)
{
	char	*pid;

	pid = ft_itoa(getpid());
	append_str(res, pid);
	free(pid);
	(*i)++;
}

static void	get_last_code(int last_status, char **res, int	*i)
{
	char	*tmp;

	tmp = ft_itoa(last_status);
	append_str(res, tmp);
	free(tmp);
	(*i)++;
}

void	handle_dolar(char **res, char *s, int *i, t_shell *sh)
{
	char	*var;
	char	*val;
	int		start;

	(*i)++;
	if (!s[*i])
		return (append_char(res, '$'));
	if (s[*i] == '$')
		return (pid_minishell(res, i));
	if (s[*i] == '?')
		return (get_last_code(sh->last_status, res, i));
	if (!ft_isalpha(s[*i]) && s[*i] != '_')
		return (append_char(res, '$'));
	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	var = ft_substr(s, start, *i - start);
	val = env_get(sh->env, var);
	if (val)
		append_str(res, val);
	free(var);
}
