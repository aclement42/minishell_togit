/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:41:06 by aclement          #+#    #+#             */
/*   Updated: 2023/04/17 17:11:06 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pwd(t_env **var_env)
{
    t_env *tmp;
    int i;

    i = 0;
    tmp = (*var_env);
    while (*var_env)
    {
        if ((*var_env)->name == "[PWD]")
            printf("[%s]\n", (*var_env)->value);
        (*var_env) = (*var_env)->next;
    }
    (*var_env) = tmp;
}