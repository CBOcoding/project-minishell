/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:00:53 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/08 16:24:48 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*swap;

	if (*lst == NULL)
		return ;
	while (*lst != NULL)
	{
		swap = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = swap;
	}
	*lst = NULL;
}
