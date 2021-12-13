/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:14 by tkirihar          #+#    #+#             */
/*   Updated: 2021/11/22 15:49:15 by tkirihar         ###   ########.fr       */
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
	write(1, "\n[Received from the client: ", 28);
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

int	bit_send(int send_bit, pid_t pid)
{
	if (send_bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			return (-1);
	}
	else if (send_bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			return (-1);
	}
	else
		return (-1);
	return (0);
}
