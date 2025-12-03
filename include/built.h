/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:00:29 by amyrodri          #+#    #+#             */
/*   Updated: 2025/12/03 18:24:19 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_H
# define BUILT_H

# include <dirent.h>
# include "minishell.h"

typedef struct s_env_table	t_env_table;

void	print_env(t_env_table *env);
void	cd(t_env_table *env, char *path);
void	export(t_env_table *env, char *key_value);
void	unset(t_env_table *env, char *key);
void	echo(t_env_table *env, char *flag, char *line);

#endif
