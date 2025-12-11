/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 02:32:19 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/11 04:16:05 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_ast	t_ast;
typedef struct s_redir	t_redir;

int		execute_cmd(t_ast *cmd_node, char **envp);
void	apply_redirect(t_redir *redirs);
int		handle_redirect(t_ast *redir_node, char **envp);

int		is_builtin(char **av);
int		execute_builtin(char **av);
char	*resolve_path(char *cmd, char **envp);

#endif
