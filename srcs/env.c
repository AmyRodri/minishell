/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:06:00 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/18 16:31:15 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long	hash(char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while(*str)
	{
		c = *str++;
		hash = ((hash << 5) + hash) + c;
	}
	return (hash);
}

t_env_table *env_init(size_t size)
{
	t_env_table	*table;

	table = malloc(sizeof(t_env_table));
	if (!table)
		return (NULL);
	table->buckets = ft_calloc(size, sizeof(t_env *));
	table->size = size;
	return (table);
}

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	env_set(t_env_table *table, char *key, char *value)
{
	unsigned long	idx;
	t_env			*curr;
	
	idx = hash(key) % table->size;
	curr = table->buckets[idx];
	while (curr)
	{
		if (strcmp(curr->key, key) == 0) // rebuild ft_strcmp
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	t_env	*new = env_new(key, value);
	new->next = table->buckets[idx];
	table->buckets[idx] = new;
}

void	load_env(t_env_table *table, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		char	*entry = envp[i];
		char	*equal = ft_strchr(entry, '=');
		if (equal)
		{
			size_t	key_len = equal - entry;
			char	*key = ft_substr(entry, 0, key_len);
			char	*value = ft_strdup(equal + 1);
			env_set(table, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

char	**env_to_envp(t_env_table *table)
{
	size_t count = 0;
	
	for (size_t i = 0; i < table->size; i++)
	{
		t_env *curr = table->buckets[i];
		while (curr)
		{
			count++;
			curr = curr->next;
		}
	}
	char **envp = malloc(sizeof(char *) * (count + 1));
	size_t j = 0;
	for (size_t i = 0; i < table->size; i++)
	{
		t_env *curr = table->buckets[i];
		while (curr)
		{
			size_t len = ft_strlen(curr->key) + ft_strlen(curr->value) + 2;
			char	*entry = malloc(len);
			snprintf(entry, len, "%s=%s", curr->key, curr->value);
			envp[j++] = entry;
			curr = curr->next;
		}
	}
	envp[j] = NULL;
	return (envp);
}
