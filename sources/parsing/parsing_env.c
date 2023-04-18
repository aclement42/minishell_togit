/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 04:32:54 by aclement          #+#    #+#             */
/*   Updated: 2023/04/07 15:00:54 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_env(t_env **var_env, char **env)
{
    //printf("init env\n");
    var_env = create_env(var_env, env);
}

t_env   **create_env(t_env **var_env, char **env)
{
    //printf("create env\n");
    int i;
    int j;
    int start;
    int end;
    char    *stock_name;
    char    *stock_value;

    i = 0;
    j = 0;
    while (env[j])
    {
        i = 0;
        start = i;
        while (env[j][i] != '=')
            i++;
        end = i - 1;
        stock_name = block_malloc(env[j], start, end, end - start);
        start = ++i;
        while (env[j][i] != '\n' && env[j][i] != '\0')
            i++;
        end = i - 1;
        stock_value = block_malloc(env[j], start, end, end - start);
        add_env(var_env, stock_name, stock_value);
        //free(stock_value);
        //free(stock_name);
        //printf("%s = %s\n", stock_name, stock_value);
        j++;
    }
    return (var_env);
}
