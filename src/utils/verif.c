/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:47:14 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/27 18:34:46 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	ft_verif_line(char *line)
{
	char	prev;
	int		i;
	int		flag;

	if (is_empty_line(line) == 1)
		return (0);
	i = 0;
	flag = 0;
	prev = '\0';
	while (line[i])
	{
		if (!flag && (prev != '\\' && is_quote(line[i])))
			flag = is_quote(line[i]);
		else if (flag && ((is_quote(line[i]) == flag && prev != '\\')))
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

static int      test_cmd(char **paths, char *s)
{
        int     i;
        char    *test_path;

        i = 0;
        while (paths[i])
        {
                test_path = ft_strjoin_t(paths[i], "/", s);
                if (access(test_path, F_OK | X_OK) == 0)
                {
                        ft_free_split(paths);
                        free(test_path);
                        return (1);
                }
                free(test_path);
                i++;
        }
        ft_free_split(paths);
        return (0);
}

int	is_cmd(char *s, t_env *env)
{
	t_env	*path;
	char	**paths;

	path = env;
	while (path && ft_cmp("PATH", path->key) != 0)
		path = path->next;
	if (!path)
		return (0);
	paths = ft_split(path->value, ':');
	return (test_cmd(paths, s));
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
