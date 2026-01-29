/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adeflers <adeflers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:06:23 by adeflers          #+#    #+#             */
/*   Updated: 2025/05/19 21:20:52 by adeflers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*stock_buff(int fd, char *start_c, char *buff);
char	*next_line(char *line);
char	*ft_gen0(void);

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

/* int	main(int ac, char **av) */
/* { */
/* 	int	fd = open(av[1], O_RDONLY); */
/* 	char	*output1 = get_next_line(fd); */
/* 	char	*output2 = get_next_line(fd); */
/* 	char	*output3 = get_next_line(fd); */
/* 	char	*output4 = get_next_line(fd); */
/* 	char	*output5 = get_next_line(fd); */
/* 	char	*output6 = get_next_line(fd); */
/* 	char	*output7 = get_next_line(fd); */
/* 	char	*output8 = get_next_line(fd); */
/* 	char	*output9 = get_next_line(fd); */
/* 	char	*output10 = get_next_line(fd); */
/* 	char	*output11 = get_next_line(fd); */
/* 	char	*output12 = get_next_line(fd); */
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
