/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 13:05:47 by lchapot           #+#    #+#             */
/*   Updated: 2026/06/09 15:56:17 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

// char	*stock_buff(int fd, char *start_c, char *buff);
// char	*next_line(char *line);
// char	*ft_gen0(void);


t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	count = 0;
	temp = lst;
	while (temp)
	{
		temp = temp->next;
		count++;
	}
	return (count);
} 
void	ft_lstadd_back(t_list **lst, t_list *new_elem)
{
	t_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new_elem;
		}
		else
			*lst = new_elem;
	}
}
t_list	*ft_lstnew(void *content)
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(t_list));
	if (!new_lst)
		return (NULL);
	new_lst->content = content;
	new_lst->next = NULL;
	return (new_lst);
}

int	max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

void	printerr(char *msg)
{
	write(2, "Error\n", 6);
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
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (!i)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	new[i] = '\0';
	while (s[i])
	{
		i--;
		new[i] = s[i];
	}
	return (new);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	count;

	if (ft_strlen(s) <= start)
		count = 0;
	else if (ft_strlen(s + start) < len)
		count = ft_strlen(s + start);
	else
		count = len;
	new = (char *)malloc(sizeof(char) * (count + 1));
	if (!new)
		return (NULL);
	len = 0;
	while (count > 0)
	{
		new[len] = s[start + len];
		len++;
		count--;
	}
	new[len] = '\0';
	return (new);
}

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

char	*get_next_line(int fd, int need_free)
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

