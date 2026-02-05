/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:37:31 by amyrodri          #+#    #+#             */
/*   Updated: 2026/02/04 23:59:23 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_borders(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	if (is_logic_op(head->type) && !is_redir(head->type))
	{
		printf("Syntax %s : error\n", head->value);
		return (1);
	}
	while (head->next)
		head = head->next;
	if (token_op(head->type))
	{
		printf("Syntax %s : error\n", head->value);
		return (1);
	}
	return (0);
}

static int	check_next_token(t_token *tokens)
{
	if (!tokens->next)
		return (0);
	if (is_logic_op(tokens->type)
		&& is_logic_op(tokens->next->type))
	{
		printf("Syntax %s : error\n", tokens->next->value);
		return (1);
	}
	if (is_redir(tokens->type)
		&& token_op(tokens->next->type))
	{
		printf("Syntax %s : error\n", tokens->next->value);
		return (1);
	}
	return (0);
}

static t_token	*check_paren(t_token *tokens)
{
	int	depth;

	depth = 0;
	if (tokens->type != TK_LPAREN)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == TK_LPAREN)
			depth++;
		else if (tokens->type == TK_RPAREN)
		{
			depth--;
			if (depth == 0)
				return (tokens);
		}
		tokens = tokens->next;
	}
	if (depth > 0)
		printf("syntax: unexpected '('\n");
	return (NULL);
}

static int	handle_paren_open(t_token **head_ptr)
{
	t_token	*end;
	t_token	*head;

	head = *head_ptr;
	end = check_paren(head);
	if (!end)
		return (1);
	if (end->next && !token_op(end->next->type)
		&& end->next->type != TK_RPAREN)
	{
		printf("minishell: syntax error near unexpected token '%s'\n",
			end->next->value);
		return (1);
	}
	if (check_inside(head->next, end))
		return (1);
	*head_ptr = end->next;
	return (0);
}

int	check_syntax(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	if (check_borders(head))
		return (1);
	while (head)
	{
		if (check_next_token(head))
			return (1);
		if (head->type == TK_LPAREN)
		{
			if (handle_paren_open(&head))
				return (1);
			continue ;
		}
		if (head->type == TK_RPAREN)
		{
			printf("syntax: unexpected ')'\n");
			return (1);
		}
		head = head->next;
	}
	return (0);
}
