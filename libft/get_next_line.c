/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_n_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:06:23 by adeflers          #+#    #+#             */
/*   Updated: 2026/06/11 12:56:56 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nextline(char *res)
{
	size_t	i;
	char	*afternl;

	i = 0;
	while (res[i] != '\n' && res[i] != '\0')
		i++;
	if (res[i] == 0 || res[1] == 0)
		return (NULL);
	afternl = ft_substr(res, i + 1, ft_strlen(res) - 1);
	if (!afternl)
		return (NULL);
	if (*afternl == 0)
	{
		free(afternl);
		afternl = NULL;
	}
	res[i + 1] = 0;
	return (afternl);
}

static char	*find_line(int fd, char *new, char *afternl)
{
	int			b_read;
	char		*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, new, BUFFER_SIZE);
		if (b_read < 0)
			return (free(afternl), NULL);
		else if (b_read == 0)
			break ;
		new[b_read] = 0;
		if (!afternl)
			afternl = ft_strdup("");
		tmp = afternl;
		afternl = ft_strjoin(tmp, new);
		if (!afternl)
			return (free(tmp), NULL);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(new, '\n'))
			break ;
	}
	return (afternl);
}

char	*g_n_l(int fd, int need_free)
{
	static char	*afternl = NULL;
	char		*res;
	char		*new;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || need_free)
	{
		if (afternl)
		{
			free(afternl);
			afternl = NULL;
		}
		return (NULL);
	}	
	new = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new)
		return (NULL);
	res = find_line(fd, new, afternl);
	free(new);
	new = NULL;
	if (!res)
		return (free(afternl), NULL);
	afternl = nextline(res);
	return (res);
}


// char	*stock_buff(int fd, char *start_c, char *buff);
// char	*next_line(char *line);
// char	*ft_gen0(void);

// char	*g_n_l(int fd)
// {
// 	static char	*start_c;
// 	char		*line;
// 	char		*buff;

// 	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
// 	{
// 		free(start_c);
// 		free(buff);
// 		start_c = NULL;
// 		buff = NULL;
// 		return (NULL);
// 	}
// 	if (!buff)
// 		return (NULL);
// 	line = stock_buff(fd, start_c, buff);
// 	free(buff);
// 	buff = NULL;
// 	if (!line)
// 		return (NULL);
// 	start_c = next_line(line);
// 	return (line);
// }

// char	*stock_buff(int fd, char *start_c, char *buff)
// {
// 	int		diams;
// 	char	*tmp;

// 	diams = 1;
// 	while (diams > 0)
// 	{
// 		diams = read(fd, buff, BUFFER_SIZE);
// 		if (diams == -1)
// 		{
// 			free(start_c);
// 			return (NULL);
// 		}
// 		else if (diams == 0)
// 			break ;
// 		buff[diams] = '\0';
// 		if (!start_c)
// 			start_c = ft_gen0();
// 		tmp = start_c;
// 		start_c = ft_strjoin(tmp, buff);
// 		free(tmp);
// 		tmp = NULL;
// 		if (ft_strchr(buff, '\n'))
// 			break ;
// 	}
// 	return (start_c);
// }

// char	*next_line(char *line)
// {
// 	char	*start_c;
// 	int		i;

// 	i = 0;
// 	while (line[i] != '\n' && line[i] != '\0')
// 		i++;
// 	if (line[i] == '\0')
// 		return (NULL);
// 	start_c = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
// 	if (*start_c == '\0')
// 	{
// 		free(start_c);
// 		start_c = NULL;
// 	}
// 	line[i + 1] = '\0';
// 	return (start_c);
// }

// char	*ft_gen0(void)
// {
// 	char	*new;

// 	new = malloc(1);
// 	if (!new)
// 		return (NULL);
// 	*new = '\0';
// 	return (new);
// }

/* int	main(int ac, char **av) */
/* { */
/* 	int	fd = open(av[1], O_RDONLY); */
/* 	char	*output1 = g_n_l(fd); */
/* 	char	*output2 = g_n_l(fd); */
/* 	char	*output3 = g_n_l(fd); */
/* 	char	*output4 = g_n_l(fd); */
/* 	char	*output5 = g_n_l(fd); */
/* 	char	*output6 = g_n_l(fd); */
/* 	char	*output7 = g_n_l(fd); */
/* 	char	*output8 = g_n_l(fd); */
/* 	char	*output9 = g_n_l(fd); */
/* 	char	*output10 = g_n_l(fd); */
/* 	char	*output11 = g_n_l(fd); */
/* 	char	*output12 = g_n_l(fd); */
/**/
/* 	printf("1er appel : %s", output1); */
/* 	free(output1); */
/* 	printf("2eme appel :%s", output2); */
/* 	free(output2); */
/* 	printf("3eme appel :%s", output3); */
/* 	free(output3); */
/* 	printf("4eme appel :%s", output4); */
/* 	free(output4); */
/* 	printf("5eme appel :%s", output5);  */
/* 	free(output5); */
/* 	printf("6eme appel :%s", output6); */
/* 	free(output6); */
/* 	printf("7eme appel :%s", output7); */
/* 	free(output7); */
/* 	printf("8eme appel :%s", output8); */
/* 	free(output8); */
/* 	printf("9eme appel :%s", output9); */
/* 	free(output9); */
/* 	printf("10eme appel :%s", output10); */
/* 	free(output10); */
/* 	printf("11eme appel :%s", output11); */
/* 	free(output11); */
/* 	printf("12eme appel :%s", output12); */
/* 	free(output12); */
/* 	close(fd); */
/* 	return (0); */
/* } */
