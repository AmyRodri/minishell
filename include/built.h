/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:00:29 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/22 12:19:01 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include <dirent.h>
# include "minishell.h"

typedef struct s_env_table		t_env_table;
typedef struct s_alias_table	t_alias_table;
typedef struct s_cmd			t_cmd;
typedef struct s_shell			t_shell;

/* ========== UTILS ===================== */

int		key_len(const char *s);
int		key_cmp(const char *s1, const char *s2);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
int		is_append(char *s);

/* ========== BUILT OPERATIONS ========== */

void	display_export(t_env_table *env);
void	display_alias(t_alias_table *alias);

/* ========== BUILT OPERATIONS ========== */

int		cd(t_env_table *env, t_cmd *path);
int		echo(t_env_table *env, t_cmd *cmd);
int		print_env(t_env_table *env, t_cmd *cmd);
int		export(t_env_table *env, t_cmd *cmd);
int		pwd(t_env_table *env, t_cmd *cmd);
int		unset(t_env_table *env, t_cmd *cmd);
int		alias(t_alias_table *alias, t_cmd *cmd);
int		unalias(t_alias_table *alias, t_cmd *cmd);
int		ft_exit(t_shell *sh, t_cmd *cmd);

#endif
