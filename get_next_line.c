/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchamma <mchamma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:37:27 by mchamma           #+#    #+#             */
/*   Updated: 2023/06/19 11:41:38 by mchamma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_isolate_backup(char *ref)
{
	char	*backup;

	backup = NULL;
	if (ft_strchr(ref, '\n'))
		backup = ft_strdup(ft_strchr(ref, '\n') + 1);
	free(ref);
	return (backup);
}

char	*ft_isolate_next_line(char *ref)
{
	int		i;
	char	*line;

	i = 0;
	while (ref[i] != '\n' && ref[i] != '\0')
		i++;
	if (ref[i] == '\0' && i == 0)
		return (NULL);
	if (ref[i] == '\n')
		i++;
	line = ft_substr(ref, 0, i);
	return (line);
}

char	*ft_finding_next_line(int fd, char *step, char *ref)
{
	char	*aux;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read (fd, step, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		step[bytes_read] = '\0';
		if (ref == NULL)
			ref = ft_strdup("");
		aux = ft_strdup(ref);
		free(ref);
		ref = ft_strjoin(aux, step);
		free(aux);
		if (ft_strchr(ref, '\n'))
			break ;
	}
	return (ref);
}

char	*get_next_line(int fd)
{
	char		*step;
	char static	*ref;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	step = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!step)
		return (NULL);
	ref = ft_finding_next_line(fd, step, ref);
	free (step);
	if (ref == NULL)
		return (NULL);
	line = ft_isolate_next_line(ref);
	ref = ft_isolate_backup(ref);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	printf("BUFFER_SIZE: %d\n\n", BUFFER_SIZE);

// 	fd = open ("loren.md", O_RDONLY);
// 	printf("%d\n\n", fd);

// 	line = get_next_line(fd);
// 	printf("Line 1: %s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("Line 2: %s\n", line);
// 	free(line);

// 	line = get_next_line(fd);
// 	printf("Line 3: %s\n", line);
// 	free(line);

// 	close(fd);
// 	return (0);
// }

// cc -Wall -Wextra -Werror -g -D BUFFER_SIZE=42 \
// 	get_next_line.c get_next_line_utils.c \
// 	-I get_new_line.h && ./a.out && rm a.out