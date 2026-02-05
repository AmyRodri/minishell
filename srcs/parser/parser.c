/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:42:06 by kamys             #+#    #+#             */
/*   Updated: 2026/02/04 23:43:35 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*parse_redirs(t_token **tokens)
{
	t_redir	*list;

	list = NULL;
	while (*tokens)
	{
		if ((*tokens)->type == TK_REDIR_IN
			|| (*tokens)->type == TK_REDIR_OUT
			|| (*tokens)->type == TK_APPEND
			|| (*tokens)->type == TK_HEREDOC)
			add_redir_back(&list, redirs(tokens, (*tokens)->type));
		else
			break ;
	}
	return (list);
}

t_ast	*parse_simple(t_token **tokens)
{
	t_redir	*redirs;
	t_ast	*cmd;
	t_cmd	*c;

	if (*tokens && (*tokens)->type == TK_LPAREN)
		return (parse_subshell(tokens));
	redirs = parse_redirs(tokens);
	if (*tokens && (*tokens)->type == TK_WORD)
		cmd = parse_command(tokens);
	else
		cmd = new_node(NODE_CMD, NULL, NULL, ft_calloc(1, sizeof(t_cmd)));
	c = (t_cmd *)cmd->content;
	if (redirs)
	{
		if (c->redir)
			add_redir_back(&redirs, c->redir);
		c->redir = redirs;
	}
	return (cmd);
}

t_ast	*parser(t_token *tokens)
{
	t_ast	*ast;

	if (check_syntax(tokens))
		return (NULL);
	ast = parse_sequence(&tokens);
	return (ast);
}
