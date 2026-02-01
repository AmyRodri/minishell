/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:28:40 by amyrodri          #+#    #+#             */
/*   Updated: 2026/02/01 19:22:02 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_shell	t_shell;

int		ft_isspace(const char c);
int		ft_strcmp(const char *s1, const char *s2);
void	shell_upadate(t_shell *sh);
void	set_terminal_title(char *title);

#endif