/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:28:51 by aclement          #+#    #+#             */
/*   Updated: 2023/04/17 23:20:16 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_dollar(char *str)
{
    //printf("find dollar\n");

    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == '$')
            return (i);
        i++;
    }
    return (-1);
}



int pair_quote(char *input)
{
    //printf("pair quotes\n");
    int i;
    int nb;
    int len;
    int flag;

    i = 0;
    nb = 0;
    len = ft_strlen(input);
    flag = 0;
    while (i < len)
    {
        if (flag == 0 && input[i] == 39)
            flag = 9;
        else if (flag == 0 && input[i] == 34)
            flag = 4;
        else if (flag == 9 && input[i] == 39)
            flag = 0;
        else if (flag == 4 && input[i] == 34)
            flag = 0;
        i++;
    }
    return (flag);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char *input;
    t_list  **token;
    t_env   **var_env;

    while (1)
    {
        input = get_input();
        if (pair_quote(input) != 0)
            printf("Erreur de lecture des quotes.\n");
        else
        {
            token = malloc(sizeof(t_list));
            token[0] = NULL;
            var_env = malloc(sizeof(t_env));
            var_env[0] = NULL;
            init_env(var_env, env);
            init_list(token, input, var_env);
            print_list(token);
            //print_env(var_env);
        }
    }
    return (0);
}

void	print_list(t_list **token)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = (*token);
	while (*token)
	{
		printf("****ID Token****\n");
		printf("content: [%s]\n", (*token)->block);
		printf("type: [%d]\n", (*token)->type);
		printf("****************\n");
		(*token) = (*token)->next;
	}
	(*token) = tmp;
}

void    print_env(t_env **var_env)
{
    t_env *tmp;
    int i;

    i = 0;
    tmp = (*var_env);
    while (*var_env)
    {
        printf("[%s] =", (*var_env)->name);
        printf("[%s]\n", (*var_env)->value);
        (*var_env) = (*var_env)->next;
    }
    (*var_env) = tmp;
}
