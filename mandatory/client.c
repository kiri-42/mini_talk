/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:22 by tkirihar          #+#    #+#             */
/*   Updated: 2021/11/26 20:28:20 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <limits.h>

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

int	convert_str_to_bit(char *send_str, pid_t pid)
{
	int		send_bit;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(send_str);
	i = 0;
	while (i <= len)
	{
		j = 0;
		while (j < 8)
		{
			send_bit = send_str[i] & 1;
			send_str[i] = send_str[i] >> 1;
			j++;
			if (bit_send(send_bit, pid) == -1)
				return (-1);
			if (usleep(300) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		write(1, "Incorrect number of command line arguments\n", 43);
		return (-1);
	}
	pid = pid_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "The PID format is incorrect\n", 28);
		return (-1);
	}
	if (convert_str_to_bit(argv[2], pid) == -1)
	{
		write(1, "Failed to send the character string\n", 36);
		return (-1);
	}
	return (0);
}
