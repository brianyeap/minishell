/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:12:13 by brian             #+#    #+#             */
/*   Updated: 2025/04/14 22:04:07 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "ft_printf/ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int		ft_atoi(const char *str);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(char c);
int		ft_isascii(int c);
int		ft_isdigit(char c);
int		ft_isprint(char c);
char	*ft_itoa(int n);
void	*ft_memdel(void *ptr);
void	*ft_memchr(void const *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *des, void const *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s1);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
size_t	ft_strlcpy(char *des, char const *src, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *str, const char *c, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	ft_tolower(int c);
char	ft_toupper(int c);
void	ft_skip_is_space(const char *str, int *i);
int		get_next_line(int fd, char **line);
int		ft_strisnum(const char *str);
void	ft_putendl(char *s);
int		process_stock(char **stock, char **line, int read_len);
int		newline_check(char *stock, int read_size);
char	*get_line(char *stock);
char	*stock_trim(char *stock);
int		process_stock(char **stock, char **line, int read_len);
int		read_to_stock(int fd, char **stock);
char	*buf_join(char *stock, char *buf);

#endif