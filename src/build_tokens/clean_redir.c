/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglampor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:22:37 by aglampor          #+#    #+#             */
/*   Updated: 2024/09/03 17:56:46 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_type(char	*str)
{
	if (!(find_c(str, '>')))
	{
		if (str[1] && !((find_c(&str[1], '>'))))
			return (RROUT);
		return (ROUT);
	}
	if ((find_c(str, '<') == 0))
	{
		if (str[1] && !(find_c(&str[1], '<')))
			return (RRIN);
		return (RRIN);
	}
	return (0);
}

int	open_file(char *fic_name, int redir)
{
	int	fd;

	if (redir == RIN)
		fd = open(fic_name, O_RDONLY, 0777);
	else if (redir == ROUT)
		fd = open(fic_name, O_WRONLY | O_CREAT, 0777);
	else if (redir == RROUT)
		fd = open(fic_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}

char	*owr(char *cmd)
{
	if (cmd[0] == '>')
	{
		if (cmd[1] && cmd[1] != '>')
			return (ft_strdup(&(cmd[1])));
		else if (cmd[1] == '>' && cmd[2])
			return (ft_strdup(&(cmd[2])));
	}
	if (cmd[0] == '<')
	{
		if (cmd[1] && cmd[1] != '<')
			return (ft_strdup(&(cmd[1])));
		else if (cmd[1] == '<' && cmd[2])
			return (ft_strdup(&(cmd[2])));
	}
	return (NULL);
}

void	refresh_tok(t_token **t, char *fic, int type_redir)
{
	int	fd;

	if (type_redir != RRIN)
		fd = open_file(fic, type_redir);
	else
		fd = ft_heardoc(fic);
	if (type_redir == RIN || type_redir == RRIN)
	{
		if ((*t)->fdin)
			close(fd);
		(*t)->fdin = fd;
	}
	else if (type_redir == ROUT || type_redir == RROUT)
	{
		if ((*t)->fdin)
			close(fd);
		(*t)->fdout = fd;
	}
}

//repalce selon la redir
void	remove_redir(t_token **ts)
{
	int	i;
	t_token		*p_first;

	p_first = (*ts);
	while ((*ts))
	{
		i = 0;
		while ((*ts)->value[i])
		{
			if (redir_type((*ts)->value[i]))
			{
				(*ts)->value = redir_realloc(&(*ts));
				break ;
			}
			i++;
		}
		(*ts) = (*ts)->next;
	}
	(*ts) = p_first;
}
