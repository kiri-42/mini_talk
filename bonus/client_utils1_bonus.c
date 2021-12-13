/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:06 by tkirihar          #+#    #+#             */
/*   Updated: 2021/11/22 15:49:07 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

void	print_pid(pid_t pid)
{
	char	print_char;

	if (!pid)
		return ;
	print_pid(pid / 10);
	print_char = (pid % 10) + '0';
	write(1, &print_char, 1);
}

void	print_receive_str(int fd, char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	write(fd, str, len);
}

void	print_client_pid(siginfo_t *info)
{
	write(1, "\n[Received from the server: ", 28);
	print_pid(info->si_pid);
	write(1, "]\n", 2);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	pid_atoi(char *char_pid)
{
	int		int_pid;
	size_t	i;

	i = 0;
	int_pid = 0;
	while (char_pid[i] != '\0')
	{
		if ('0' <= char_pid[i] && char_pid[i] <= '9')
		{
			int_pid = int_pid * 10 + (char_pid[i] - '0');
			i++;
		}
		else
			return (-1);
	}
	return (int_pid);
}
