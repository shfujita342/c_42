/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yseto < yseto@student.42tokyo.jp Mail>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 19:15:48 by yseto             #+#    #+#             */
/*   Updated: 2025/10/02 15:52:54 by yseto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}

t_env	*new_env_node(const char *key, const char *value)
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

void	env_add_back(t_env **head, t_env *node)
{
	t_env	*tmp;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	env_add_from_string(t_env **head, const char *env_str)
{
	char	*eq;
	char	*key;
	char	*value;
	t_env	*node;

	eq = ft_strchr(env_str, '=');
	if (!eq)
		return (0);
	key = ft_strndup(env_str, eq - env_str);
	value = ft_strdup(eq + 1);
	node = new_env_node(key, value);
	free(key);
	free(value);
	if (!node)
		return (-1);
	env_add_back(head, node);
	return (0);
}

t_env	*copy_env(char **envp)
{
	t_env	*head;
	int		i;

	head = NULL;
	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (env_add_from_string(&head, envp[i]) == -1)
		{
			free_env_list(head);
			return (NULL);
		}
		i++;
	}
	return (head);
}
