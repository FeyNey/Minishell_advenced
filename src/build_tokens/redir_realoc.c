/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_realoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexis <alexis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:46:24 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/19 11:24:06 by alexis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	if ((fic_name = owr(s1))) //?? pas bon
	{
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

char	**redir_realloc(t_token **token)
{
	int		i;
	int		j;
	int		type;
	char	**stash;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = (*token)->value;
	stash = malloc(sizeof(char *) * (count_redir((*token)->value) + 1));
	// printf("%d\n",count_redir((*token)->value));
	if (!stash)
		return (0);
	while (tmp[j])
	{
		if ((type = redir_type(tmp[j]))) //?? pas bon
			j += handle_redir(tmp[j], tmp[j + 1], type, token);
		else
		{
			// printf("%d index tmp\n",j);
			stash[i] = ft_strdup(tmp[j]);
			// printf("%s\n",stash[i]);
			j++;
			i++;
		}
	}
	stash[i] = 0;
	if (((*token)->value))
		ft_free_split((*token)->value);
	return (stash);
}
