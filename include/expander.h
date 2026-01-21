/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 14:40:55 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 12:18:16 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_shell	t_shell;

/* ========== EXPAND ========== */

void	expand_alias_ast(t_ast *root, t_shell *sh);
void	expand_ast(t_ast *root, t_shell *sh);
void	expand_cmd(t_cmd *cmd, t_shell *sh);
void	expand_redir(t_redir *redir, t_shell *sh);
void	handle_tilde(char **res, char *s, int *i, t_shell *sh);
void	handle_dolar(char **res, char *s, int *i, t_shell *sh);
char	*expand_word(char *s, t_shell *sh);

/* ========== EXPAND QUOTES ========== */

void	handle_single_quotes(char **res, char *s, int *i);
void	handle_double_quotes(char **res, char *s, int *i, t_shell *sh);

/* ========== EXPAND UTILS ========== */

void	append_char(char **s, char c);
void	append_str(char **s, char *add);

#endif