/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:01 by tkirihar          #+#    #+#             */
/*   Updated: 2021/11/22 16:26:20 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <stdlib.h>

void	print_pid(pid_t pid);
void	print_receive_str(int fd, char *str);
void	print_client_pid(siginfo_t *info);
size_t	ft_strlen(const char *str);
int		pid_atoi(char *char_pid);
int		bit_send(int send_bit, pid_t pid);

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

void	receive_str_check(char *receive_str, int8_t receive_char,
		int str_len, siginfo_t *info)
{
	if (str_len == 99 || receive_char == '\0')
	{
		receive_str[str_len] = '\0';
		print_receive_str(1, receive_str);
		str_len = 0;
		if (receive_char == '\0')
		{
			print_client_pid(info);
			exit(0);
		}
	}
}

void	convert_bit_to_str(int signal, siginfo_t *info, void *ucontext)
{
	int				check_bit;
	static int8_t	receive_char;
	static char		receive_str[100];
	static int		shift;
	static int		str_len;

	(void)ucontext;
	check_bit = signal == SIGUSR2;
	receive_char = receive_char | (check_bit << shift);
	shift++;
	if (shift == 8)
	{
		receive_str[str_len++] = receive_char;
		receive_str_check(receive_str, receive_char, str_len, info);
		shift = 0;
		receive_char = 0;
	}
}

int	set_signal(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = convert_bit_to_str;
	if (sigemptyset(&sa.sa_mask) < 0 || sigaction(SIGUSR1, &sa, NULL) < 0
		|| sigaction(SIGUSR2, &sa, NULL) < 0)
		return (-1);
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
	if (set_signal() == -1)
		return (-1);
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
	while (1)
		pause();
	return (0);
}
