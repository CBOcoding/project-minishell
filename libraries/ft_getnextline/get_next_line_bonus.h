/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:29:00 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/28 11:10:03 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_fill_line_gnl(int fd, char *line);
char	*ft_next_line_gnl(char *line);
char	*ft_remaining_line_gnl(char *line);
char	*ft_strchr_gnl(char *string, int c);
size_t	ft_strlen_gnl(char *s);
char	*ft_strjoin_gnl(char *str1, char *buffer);

#endif
