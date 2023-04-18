/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:42:52 by aclement          #+#    #+#             */
/*   Updated: 2023/04/07 14:50:25 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_envnew(char *stockname, char *stockvalue)
{
	//printf("ft_envnew\n");
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = stockname;
	new->value = stockvalue;
	new->next = NULL;
    //free(stockvalue);
    //free(stockvalue);
	return (new);
}

void	add_env(t_env **var_env, char *stockname, char *stockvalue)
{
	//printf("add env\n");
	t_env *to_add;

	to_add = ft_envnew(stockname, stockvalue);
	ft_envadd_back(var_env, to_add);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	//printf("ft_envadd_back\n");
	t_env	*dernier;

	if (lst)
	{
		if (*lst)
		{
			dernier = ft_envlast(*lst);
			dernier->next = new;
		}
		else
			*lst = new;
	}
}

t_env	*ft_envlast(t_env *lst)
{
	//printf("ft_envlast\n");
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}