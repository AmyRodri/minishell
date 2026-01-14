/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:30:19 by kamys             #+#    #+#             */
/*   Updated: 2026/01/14 12:01:35 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum s_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_AND,
	TK_OR,
	TK_LIST,
	TK_LPAREN,
	TK_RPAREN,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_op
{
	char			*op;
	t_token_type	type;
}	t_op;

/* ========== LEXER OPERETOR ========== */

t_token	*tokenize_operetor(const char *s, int *i);

/* ========== LEXER ========== */

int		isopertor(const char *s, int i);
t_token	*lexer(const char *s);
t_token	*new_token(t_token_type type, char *value);

/* ========== LEXER WORD ========== */

t_token	*tokenize_word(const char *s, int *i);

/* ========== LEXER UTILS ========== */

void	print_tokens(t_token *list);

#endif