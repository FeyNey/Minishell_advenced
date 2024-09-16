/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_CMD.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:20:48 by acoste            #+#    #+#             */
/*   Updated: 2024/08/28 14:43:40 by aglampor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_wrd_input(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (is_white((str[i])))
			i++;
		if (str[i])
		{	
			words++;
			i += end_cmd(&str[i]);
		}
	}
	return (words);
}


static void	cmd_split(char **arr, char *str)
{
	int	i_arr;
	int	i_char;
	int	end_CMD;
	
	i_arr = 0;
	i_char = 0;
	while (arr)
	{
		while (is_white(str[i_char]))
			i_char++;
		if (str[i_char] == '\0')
			break;
		end_CMD = end_cmd(&str[i_char]);
		arr[i_arr] = word_dup(&str[i_char], 0, end_CMD);
		i_arr++;
		i_char += end_CMD;
	}
}


char	**split_input(char *str)
{
        char            **arr;
        int                     words;

        words = count_wrd_input(str);
        arr = malloc(sizeof(char *) * (words + 1));
        if (!arr)
                return (0);
        arr[words] = 0;
        cmd_split(arr ,str);
	free(str);
        return (arr);
}


// problem si on envoie '\0' en input le split il casse
// je sais pas si je le regle (surtout comemnt le regler)

/*
cmd argument | cmd arg arg arg | cmd > file > 2 > 3 > file2 |

cdm argument
cmd arg arg arg
cmd > file > 2 > 3 file2



cmd = 0;

EXECVE(cmd);

argument = 1
| = 2;
> = 3;
< = 4;
>> = 5;
<< = 6;
file = 7;
*/
