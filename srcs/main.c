/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:17:23 by kamys             #+#    #+#             */
/*   Updated: 2025/12/11 06:23:57 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input(char	*line, t_env_table	*env)
{
	t_token	*token;
	t_ast	*ast_root;
	char	**env_array;
	int		exit_status;

	token = lexer(line);
	if (!token)
		return ;
	ast_root = parser(token);
	if (ast_root)
	{
		env_array = env_export(env);
		exit_status = execute_ast(ast_root, env_array);
		free_char_array(env_array);
	}
}

int	run_interactive_shell(t_env_table *env)
{
	char	*line;

	while (1)
	{
		line = readline(ft_strjoin(env_get(env, "USER"), " > "));
		if (!line)
			break ;
		if (*line)
			add_history(line);
		input(line, env);
		free(line);
	}
	return (0);
}

int	run_command_mode(char **argv)
{
	if (!ft_strncmp(argv[1], "-c", 2))
	{
		printf("algum dia vai começar a executar -> %s\n", argv[2]);
		exit (0);
	}
	ft_putstr_fd("usage: minishell -c \"command\"\n", 2);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_env_table	*env;
	int			status;

	status = 0;
	env = env_init(97, envp);
	if (!env)
		return (1);
	setup_sig();
	if (argc >= 3)
		status = run_command_mode(argv);
	else if (isatty(STDIN_FILENO))
		status = run_interactive_shell(env);
	rl_clear_history();
	rl_cleanup_after_signal();
	env_destroy(env);
	printf("exit\n");
	return (status);
}
