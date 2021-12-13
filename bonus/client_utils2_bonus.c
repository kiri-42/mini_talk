/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:49:11 by tkirihar          #+#    #+#             */
/*   Updated: 2021/11/22 15:49:12 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

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
