/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 04:20:11 by aclement          #+#    #+#             */
/*   Updated: 2023/04/13 19:23:07 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_input(void)
{
    //printf("get_input\n");
    char* input;

    input = readline("\033[1;34mminishell$>\033[0m");
    if (input == NULL)
    {
        printf("Erreur de lecture de la input.\n");
        exit(EXIT_FAILURE);
    }
	add_history(input);
    return input;
}

int ft_strlen(char *str)
{
    //printf("ft_strlen\n");
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char    *block_malloc(char *input, int start, int end, int size)
{
    //printf("block malloc\n");
    char    *new;
    int        i;

    i = 0;
    new = malloc(sizeof(char) * (size + 1));
    if (new == 0)
        return (NULL);
    while (input[start] && start <= end)
        new[i++] = input[start++];
    new[i] = '\0';
    return (new);
}

char    *wordquotes_without_env(char *str)
{
    int i;

    i = 0;
    while (str && str[i] != '$')
        i++;
    str[i++] = 34;
    while (str && str[i])
        str[i] = '\0';
    return (str);
}

char    *word_without_env(char *str)
{
    int i;

    i = 0;
    printf("wordwithoutenv\n");
    while (str && str[i] != '$')
        i++;
    while (str && str[i])
        str[i] = '\0';
    return (str);
}

char    *word_without_env_more(char *str)
{
    int i;
    int j;

    j = 0;
    i = 0;
    printf("wordwithoutenvmore\n");
    while (str && str[i] != '$')
        i++;
    j = i++;
    //printf("%c\n", str[i]);
    while (str[i] && str[i] != '$')
        i++;
    while (str[i])
        str[j++] = str[i++];
    str[j] = '\0';
    //printf("str : %s\n", str);
    return (str);
}

char    *word_with_env(char *str)
{
    char    *new;
    int        i;

    i = 0;
    printf("wordwithenv\n");
    new = malloc(sizeof(char *));
    while (str[i] && str[i] != '$')
    {
        i++;
    }
    new[i] = '\0';
    return (new);
}