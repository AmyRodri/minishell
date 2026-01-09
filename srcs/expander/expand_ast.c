/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:01:18 by kamys             #+#    #+#             */
/*   Updated: 2026/01/08 23:24:07 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	append_char(char **s, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = 0;
	new = ft_strjoin(*s, tmp);
	free(*s);
	*s = new;
}

void	append_str(char **s, char *add)
{
	char	*new;

	new = ft_strjoin(*s, add);
	free(*s);
	*s = new;
}

void	handle_dolar(char **res, char *s, int *i, t_env_table *env)
{
	char	*var;
	char	*val;
	int		start;

	(*i)++;
	if (s[*i] == '$')
	{
		append_str(res, env_get(env, "LAST_CODE"));
		(*i)++;
		return ;
	}
	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	var = ft_substr(s, start, *i - start);
	val = env_get(env, var);
	if (val)
		append_str(res, val);
	free(var);
}

void	handle_tilde(char **res, char *s, int *i, t_env_table *env)
{
	if (*i == 0 || s[*i - 1] == ' ')
		append_str(res, env_get(env, "HOME "));
	else
		append_char(res, s[*i]);
	(*i)++;
}

void	handle_single_quotes(char **res, char *s, int *i)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
		append_char(res, s[(*i)++]);
	if (s[*i] == '\'')
		(*i)++;
}

void	handle_double_quotes(char **res, char *s, int *i, t_env_table *env)
{
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '$')
			handle_dolar(res, s, i, env);
		else
			append_char(res, s[(*i)++]);
	}
	if (s[*i] == '"')
		(*i)++;
}

char	*expand_word(char *s, t_env_table *env)
{
	char	*res;
	int		i;

	(void)env;
	res = ft_strdup("");
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			handle_single_quotes(&res, s, &i);
		else if (s[i] == '\"')
			handle_double_quotes(&res, s, &i, env);
		else if (s[i] == '$')
			handle_dolar(&res, s, &i, env);
		else if (s[i] == '~')
			handle_tilde(&res, s, &i, env);
		else
			append_char(&res, s[i++]);
	}
	free(s);
	return (res);
}

void	expand_cmd(t_cmd *cmd, t_env_table *env)
{
	int	i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		cmd->argv[i] = expand_word(cmd->argv[i], env);
		i++;
	}
}

void	expand_redir(t_redir *redir, t_env_table *env)
{
	while (redir)
	{
		if (redir->type != REDIR_HEREDOC)
			redir->file = expand_word(redir->file, env);
		redir = redir->next;
	}
}

void	expand_ast(t_ast *root, t_env_table *env)
{
	if (!root)
		return ;
	if (root->type == NODE_CMD)
		expand_cmd((t_cmd *)root->content, env);
	else if (root->type == NODE_REDIR)
		expand_redir((t_redir *)root->content, env);
	expand_ast(root->left, env);
	expand_ast(root->right, env);
}
