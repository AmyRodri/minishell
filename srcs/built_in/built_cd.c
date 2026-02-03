/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:48:48 by amyrodri          #+#    #+#             */
/*   Updated: 2026/02/03 16:48:54 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static void	set_pwd_oldpwd(t_env_table *env, char *pwd, char *old_pwd)
{
	env_set(env, "OLDPWD", old_pwd);
	env_set(env, "PWD", pwd);
}

static int	cd_path(t_env_table *env, char *path)
{
	char	*cwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd"), 1);
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		free(old_pwd);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}
	set_pwd_oldpwd(env, cwd, old_pwd);
	free(old_pwd);
	free(cwd);
	return (0);
}

static int	cd_dash(t_env_table *env)
{
	char	*cwd;
	char	*old_pwd;
	char	*pwd;

	old_pwd = env_get(env, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		return (1);
	}
	pwd = env_get(env, "PWD");
	if (chdir(old_pwd) == -1)
		return (perror("cd"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd"), 1);
	printf("%s\n", cwd);
	set_pwd_oldpwd(env, cwd, pwd);
	free(cwd);
	return (0);
}

static int	cd_home(t_env_table *env)
{
	char	*cwd;
	char	*old_pwd;
	char	*home;

	home = env_get(env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(home) == -1)
		return (free(old_pwd), perror("cd"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(old_pwd), perror("cd"), 1);
	set_pwd_oldpwd(env, cwd, old_pwd);
	free(cwd);
	free(old_pwd);
	return (0);
}

int	cd(t_env_table *env, t_cmd *cmd)
{
	if (!cmd->argv[1] || !ft_strcmp(cmd->argv[1], "~"))
		return (cd_home(env));
	if (cmd->argc != 2)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	else if (!ft_strcmp(cmd->argv[1], "-"))
		return (cd_dash(env));
	else
		return (cd_path(env, cmd->argv[1]));
}
