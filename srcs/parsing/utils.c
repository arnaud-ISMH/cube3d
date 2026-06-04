/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:05:47 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/04 15:06:16 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*stock_buff(int fd, char *start_c, char *buff);
char	*next_line(char *line);
char	*ft_gen0(void);

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

void	printerr(char *msg)
{
	write(2, msg, ft_strlen(msg));
}
int	taille(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)(c))
			return ((char *)s);
		s++;
	}
	if ((char)(c) == '\0')
		return ((char *)s);
	return (NULL);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (taille(s1) + taille(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}



int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*start_c;
	char		*line;
	char		*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(start_c);
		free(buff);
		start_c = NULL;
		buff = NULL;
		return (NULL);
	}
	if (!buff)
		return (NULL);
	line = stock_buff(fd, start_c, buff);
	free(buff);
	buff = NULL;
	if (!line)
		return (NULL);
	start_c = next_line(line);
	return (line);
}

char	*stock_buff(int fd, char *start_c, char *buff)
{
	int		diams;
	char	*tmp;

	diams = 1;
	while (diams > 0)
	{
		diams = read(fd, buff, BUFFER_SIZE);
		if (diams == -1)
		{
			free(start_c);
			return (NULL);
		}
		else if (diams == 0)
			break ;
		buff[diams] = '\0';
		if (!start_c)
			start_c = ft_gen0();
		tmp = start_c;
		start_c = ft_strjoin(tmp, buff);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (start_c);
}

char	*next_line(char *line)
{
	char	*start_c;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	start_c = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
	if (*start_c == '\0')
	{
		free(start_c);
		start_c = NULL;
	}
	line[i + 1] = '\0';
	return (start_c);
}

char	*ft_gen0(void)
{
	char	*new;

	new = malloc(1);
	if (!new)
		return (NULL);
	*new = '\0';
	return (new);
}