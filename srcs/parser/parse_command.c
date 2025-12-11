/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 03:15:16 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/11 03:31:36 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir_type	redir_type(t_token_type type)
{
	if (type == TK_REDIR_IN)
		return (REDIR_IN);
	if (type == TK_REDIR_OUT)
		return (REDIR_OUT);
	return (REDIR_APPEND);
}



t_ast	*parse_command(t_token **tokens)
{
	t_redir	*redir;
	t_cmd	*cmd;
	char	**argv;
	int		argc;

	redir = NULL;
	argv = NULL;
	argc = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	while (*tokens)
	{
		t_token_type	type = (*tokens)->type;
		if (type == TK_PIPE || type == TK_AND || type == TK_OR
			|| type == TK_LIST || type == TK_RPAREN)
			break ;

		if (type == TK_REDIR_IN || type == TK_REDIR_OUT || type == TK_APPEND)
		{
			t_redir_type	rtype = redir_type(type);
			*tokens = (*tokens)->next;
			if (!*tokens || (*tokens)->type != TK_WORD)
			{
				printf("Error: filename expected\n");
				exit (1);
			}
			t_redir *r = malloc(sizeof(t_redir));
			r->type = rtype;
			r->file = ft_strdup((*tokens)->value);
			r->next = redir;
			redir = r;
			*tokens = (*tokens)->next;
			continue ;
		}

		if (type == TK_WORD)
		{
			argv = realloc(argv, sizeof(char*) * (argc + 2)); // realloc slk pq {Ö.Ö}
			argv[argc] = ft_strdup((*tokens)->value);
			argv[argc + 1] = NULL;
			argc++;
			*tokens = (*tokens)->next;
			continue ;
		}
		break ;
	}

	cmd->argv = argv;
	cmd->argc = argc;
	cmd->redir = redir;

	t_ast	*node = malloc(sizeof(t_ast));
	node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	node->content = cmd;
	return (node);
}
