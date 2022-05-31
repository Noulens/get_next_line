/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:21:54 by tnoulens          #+#    #+#             */
/*   Updated: 2022/05/31 16:50:17 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_append(char *old, char *new)
{
	int				len;
	register char	*ptr;
	char			*ret;
	register char	*oldptr;

	if ((old == NULL && new == NULL) || new == NULL)
		return (NULL);
	oldptr = old;
	if (!old)
		len = ft_strlen(new);
	else
		len = ft_strlen(oldptr) + ft_strlen(new);
	ret = (char *)malloc(len * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	ret[0] = 0;
	ptr = ret;
	while (oldptr && *oldptr)
		*ptr++ = *oldptr++;
	while (*new)
		*ptr++ = *new++;
	*ptr = 0;
	free(old);
	return (ret);
}

static char	*ft_read(char *suf, int fd)
{
	int		n;
	char	*p;
	char	*buffy;

	n = 1;
	p = NULL;
	p = ft_append(p, suf);
	buffy = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!ft_strchr(p, '\n') && n)
	{
		n = read(fd, buffy, BUFFER_SIZE);
		if (n == -1)
			return (free(buffy), free(p), NULL);
		if (n == 0)
		{
			suf[0] = 0;
			return (free(buffy), p);
		}
		buffy[n] = 0;
		p = ft_append(p, buffy);
	}
	free(buffy);
	return (p);
}

static int	ft_extract_nl(char *line)
{
	char			*p;
	register int	i;

	p = line;
	i = 0;
	while (p[i] != '\n' && p[i])
		i++;
	if (p[i] != 0)
		p[++i] = 0;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	suf[BUFFER_SIZE + 1];
	char		*p;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	p = ft_read(suf, fd);
	if (p == NULL || *p == 0)
		return (free(p), NULL);
	ft_cpy(suf, p);
	ft_extract_nl(p);
	return (p);
}
