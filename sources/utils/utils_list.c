/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclement <aclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 04:17:45 by aclement          #+#    #+#             */
/*   Updated: 2023/04/07 14:50:08 by aclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	//printf("ft_lstlast\n");
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	//printf("ft_lstadd_back\n");
	t_list	*dernier;

	if (lst)
	{
		if (*lst)
		{
			dernier = ft_lstlast(*lst);
			dernier->next = new;
		}
		else
			*lst = new;
	}
}

t_list	*ft_lstnew(char *input)
{
	//printf("ft_lstnew\n");
	t_list *new;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->block = input;
	new->next = NULL;
    return (new);
}

void    add_list(t_list **token, char *stock)
{
	//printf("addlist\n");
    t_list *to_add;
    
    to_add = ft_lstnew(stock);
	//free(stock);
    ft_lstadd_back(token, to_add);
}
