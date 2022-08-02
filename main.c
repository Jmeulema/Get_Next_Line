/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeulema <jmeulema@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:48:50 by jmeulema          #+#    #+#             */
/*   Updated: 2022/08/02 14:50:34 by jmeulema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"
#include "fcntl.h"

int	main(void)
{
	char	*str;
	int		i;
	int		fd;

	i = 1;
	fd = open("file.txt", O_RDONLY);
	while (i != 0)
	{
		str = get_next_line(fd);
		if (!str)
			i = 0;
		else
			printf("%s", str);
	}
	printf("\n");
}
