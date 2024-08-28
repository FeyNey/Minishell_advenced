/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_buildin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:59:06 by aglampor          #+#    #+#             */
/*   Updated: 2024/08/26 18:54:32 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     export(t_token *t, t_env **myEnv)
{
        int     err;

        if (t->next && ((t->next)->type) != PIPE)
                err = add_myenv(t, myEnv);
        else
                err = build_export(*(myEnv));
        return (err);
}

