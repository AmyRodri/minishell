/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:35:20 by kamys             #+#    #+#             */
/*   Updated: 2025/11/25 21:46:48 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	isopertor(const char *s, int i)
{
	if (s[i] == '&' && s[i + 1] == '&')
		return (1);
	if (s[i] == '|' && s[i + 1] == '|')
		return (1);
	if (s[i] == '<' && s[i + 1] == '<')
		return (1);
	if (s[i] == '>' && s[i + 1] == '>')
		return (1);
	if (s[i] == '|' || s[i] == ';'
		|| s[i] == '<' || s[i] == '>'
		|| s[i] == '(' || s[i] == ')')
		return (1);
	return (0);
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->type = type;
	tok->value = value;
	tok->next = NULL;
	return (tok);
}

void	add_token(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*tokenize_operetor(const char *s, int *i)
{
	char	c;

	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		*i += 2;
		return (new_token(TK_HEREDOC, ft_strdup("<<")));
	}
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		*i += 2;
		return (new_token(TK_APPEND, ft_strdup(">>")));
	}
	if (s[*i] == '&' && s[*i + 1] == '&')
	{
		*i += 2;
		return (new_token(TK_AND, ft_strdup("&&")));
	}
	if (s[*i] == '|' && s[*i + 1] == '|')
	{
		*i += 2;
		return (new_token(TK_OR, ft_strdup("||")));
	}
	c = s[*i];
	(*i)++;
	if (c == '<')
		return (new_token(TK_REDIR_IN, ft_strdup("<")));
	if (c == '>')
		return (new_token(TK_REDIR_OUT, ft_strdup(">")));
	if (c == '|')
		return (new_token(TK_PIPE, ft_strdup("|")));
	if (c == ';')
		return (new_token(TK_LIST, ft_strdup(";")));
	if (c == '(')
		return (new_token(TK_LPAREN, ft_strdup("(")));
	if (c == ')')
		return (new_token(TK_RPAREN, ft_strdup(")")));
	return (NULL);
}

t_token	*tokenize_word(const char *s, int *i)
{
	int		j;
	int		start;
	char	quote;
	char	*word;

	start = *i;
	j = *i;
	while (s[j] && !isspace(s[j]) && !isopertor(s, j)) // rebuild isspace ^~^
	{
		if (s[j] == '\'' || s[j] == '\"')
		{
			quote = s[j];
			j++;
			while (s[j] && s[j] != quote)
				j++;
			if (!s[j])
				break ;
			j++;
		}
		else
			j++;
	}
	word = ft_substr(s, start, j - start);
	*i = j;
	return (new_token(TK_WORD, word));
}

t_token	*lexer(const char *s)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	while (s[i])
	{
		if (isspace(s[i])) // rebuild isspace *_*
		{
			i++;
			continue ;
		}
		if (s[i] == '\0')
			break ;
		if (isopertor(s, i))
		{
			add_token(&list, tokenize_operetor(s, &i));
			continue ;
		}
		add_token(&list, tokenize_word(s, &i));
	}
	return (list);
}

const char *token_type_to_str(t_token_type type)
{
	if (type == TK_WORD)
		return ("WORD");
	if (type == TK_PIPE)
		return ("PIPE");
	if (type == TK_REDIR_IN)
		return ("<");
	if (type == TK_REDIR_OUT)
		return (">");
	if (type == TK_APPEND)
		return (">>");
	if (type == TK_HEREDOC)
		return ("<<");
	if (type == TK_AND)
		return ("&&");
	if (type == TK_OR)
		return ("||");
	if (type == TK_LIST)
		return (";");
	if (type == TK_LPAREN)
		return ("(");
	if (type == TK_RPAREN)
		return (")");
	return ("UNKNOWN");
}

void	print_tokens(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("[%d] Type: %-7s | Value: \"%s\"\n", i,
			token_type_to_str(list->type),
			list->value ? list->value : "(null)");
		list = list->next;
		i++;
	}
}
