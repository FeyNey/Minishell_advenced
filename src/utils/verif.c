/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:47:14 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/18 19:43:28 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_verif_line(char *line)
{
	char	prev;
	int	i;
	int	flag;

	if (is_empty_line(line) == 1)
		return (0);
	i = 0;
	flag = 0;
	prev = '\0';
	while (line[i])
	{
		if (!flag && (prev != '\\' && is_quote(line[i])))
			flag = is_quote(line[i]);
		else if (flag && ((is_quote(line[i])== flag && prev != '\\')))
			flag = 0;
		prev = line[i];
		i++;
	}
	if (flag)
	{
		write(1, "bash : not interpreted unclosed quotes\n", 39);
		return (0);
	}
	return (1);
}

int	is_cmd(char *s, t_env *env)
{
	t_env	*path;
	int		i;
	char	**paths;
	char	*test_path;

	path = env;
	i = 0;

	while (ft_cmp("PATH", path->key) != 0)
		path = path->next;
	paths = ft_split(path->value, ':');
	while (paths[i])
	{
		test_path = ft_strjoin_t(paths[i], "/", s);
		if (access(test_path, F_OK | X_OK) == 0)
		{
			free(test_path);
			ft_free_split(paths);
			return (1);
		}
		free(test_path);
		i++;
	}
	ft_free_split(paths);
	return (0);
}

int	is_builtin(char *s)
{
	if (!ft_cmp("echo", s) || !ft_cmp("cd", s) || !ft_cmp("pwd", s))
		return (1);
	if (!ft_cmp("export", s) || !ft_cmp("unset", s) || !ft_cmp("env", s))
		return (1);
	return (0);
}

int	t_redir(char *s)
{
	if (!ft_cmp("<", s))
		return (RIN);
	if (!ft_cmp("<<", s))
		return (RRIN);
	if (!ft_cmp(">", s))
		return (ROUT);
	if (!ft_cmp(">>", s))
		return (RROUT);
	if (!ft_cmp("|", s))
		return (PIPE);
	return (0);
}
