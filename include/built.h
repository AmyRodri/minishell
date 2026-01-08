/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:00:29 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/05 15:59:54 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include <dirent.h>
# include "minishell.h"

typedef struct s_env_table	t_env_table;

void	print_env(t_env_table *env, char *path);
void	cd(t_env_table *env, char *path);
void	export(t_env_table *env, char *key_value);
void	unset(t_env_table *env, char *key);
void	echo(t_env_table *env, char *flag, char *line);
void	pwd(t_env_table *env, char *path);

#endif
