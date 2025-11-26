/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:23:31 by kamys             #+#    #+#             */
/*   Updated: 2025/11/25 19:34:50 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "env.h"
# include "lexer.h"

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

// signal.c
int				get_singal(void);
void			reset_signal(void);
void			handler(int sig);
void			setup_sig(void);

#endif