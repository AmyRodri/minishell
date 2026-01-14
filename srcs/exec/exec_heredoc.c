/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:06:48 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/14 18:01:32 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	run_heredoc_loop(int fd, char *delimiter, 
	t_shell *sh)
{
	char	*line;
	char	*tmp_delim;
	int		expand;

	expand = !check_if_quoted(delimiter);
	tmp_delim = ft_strtrim(delimiter, "\"\'");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		if (expand)
			line = expand_variables_in_heredoc(line, sh);
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(tmp_delim);
}

int	exec_heredoc(t_redir *redir, t_shell *sh)
{
	int		fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	run_heredoc_loop(fd, redir->file, sh);
	close(fd);
	free(redir->file);
	redir->file = ft_strdup(".heredoc_tmp");
	redir->type = REDIR_IN;
	return (0);
}
