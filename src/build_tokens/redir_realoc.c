/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_realoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:46:24 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/03 18:09:39 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	ft_heardoc(char *end)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!(ft_cmp(line, end)))
			break;
		write(fd[1], line, ft_strlen(end));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	free(line);
	return (fd[0]);
}


static int	count_redir(char **cmds)
{
	int	i;
	int	nb_r;

	i = 0;
	nb_r = 0;
	while (cmds[i])
	{
		if (redir_type(cmds[i]))
		{
			nb_r++;
			if (!owr(cmds[i]))
			{
				nb_r++;
				i++;
			}
		}
		i++;
	}
	return (i - nb_r);
}

int	handle_redir(char *s1, char *s2, int type, t_token **p_tok)
{
	char	*fic_name;

	if (owr(s1))
	{
		(fic_name = owr(s1));
		refresh_tok(p_tok, fic_name, type);
		return (1);
	}
	if (s2)
	{
		refresh_tok(p_tok, s2, type);
		return (2);
	}
	return (1);
}

static void	tok_no_redir(char **stash, t_token **t)
{
	int		i;
	int		j;
	int		type;
	char	**cmd;

	i = 0;
	j = 0;
	cmd = (*t)->value;
	while (cmd[j])
	{
		if (redir_type(cmd[j]))
		{
			type = redir_type(cmd[j]);
			j += handle_redir(cmd[j], cmd[j + 1], type, t);
		}
		else
		{
			stash[i] = ft_strdup(cmd[j]);
			j++;
			i++;
		}
	}
	stash[i] = 0;
}

char	**redir_realloc(t_token **token)
{
	char	**stash;

	stash = malloc(sizeof(char *) * (count_redir((*token)->value) + 1));
	if (!stash)
		return (0);
	tok_no_redir(stash, token);
	if (((*token)->value))
		ft_free_split((*token)->value);
	return (stash);
}
