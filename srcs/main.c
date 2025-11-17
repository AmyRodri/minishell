/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2025/11/17 18:40:59 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	setup_sig();
	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (*line)
				add_history(line);
			if (!ft_strncmp(line, "exit", 5))
			{
				free(line);
				break ;				
			}
			free(line);
		}		
	}
	else
	{
		if (argc >= 2)
			if (!ft_strncmp(argv[1], "-c", 2))
				printf("algum dia vai começar a executar -> %s\n", argv[2]);
	}
	rl_clear_history();
	rl_cleanup_after_signal();
	printf("exit\n");
	return (0);
}
