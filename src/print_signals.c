/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnguyen- <pnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:15:28 by pnguyen-          #+#    #+#             */
/*   Updated: 2024/03/28 16:28:44 by pnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

#include "libft/libft.h"

static int	print_sig_msg1(int status);
static void	print_sig_msg2(int status);

void	print_signal_msg(int status)
{
	if (print_sig_msg1(status))
		return ;
	print_sig_msg2(status);
}

static int	print_sig_msg1(int status)
{
	if (status == SIGHUP)
		ft_putstr_fd("Hangup\n", STDERR_FILENO);
	else if (status == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (status == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (status == SIGILL)
		ft_putstr_fd("Illegal instruction (core dumped)\n", STDERR_FILENO);
	else if (status == SIGTRAP)
		ft_putstr_fd("Trace/breakpoint trap (core dumped)\n", STDERR_FILENO);
	else if (status == SIGABRT)
		ft_putstr_fd("Aborted (core dumped)\n", STDERR_FILENO);
	else if (status == SIGBUS)
		ft_putstr_fd("Bus error (core dumped)\n", STDERR_FILENO);
	else if (status == SIGFPE)
		ft_putstr_fd("Floating point exception (core dumped)\n", STDERR_FILENO);
	else if (status == SIGKILL)
		ft_putstr_fd("Killed\n", STDERR_FILENO);
	else if (status == SIGUSR1)
		ft_putstr_fd("User defined signal 1\n", STDERR_FILENO);
	else if (status == SIGSEGV)
		ft_putstr_fd("Segmentation fault (core dumped)\n", STDERR_FILENO);
	else
		return (0);
	return (1);
}

static void	print_sig_msg2(int status)
{
	if (status == SIGUSR2)
		ft_putstr_fd("User defined signal 2\n", STDERR_FILENO);
	else if (status == SIGALRM)
		ft_putstr_fd("Alarm clock\n", STDERR_FILENO);
	else if (status == SIGTERM)
		ft_putstr_fd("Terminated\n", STDERR_FILENO);
	else if (status == SIGSTKFLT)
		ft_putstr_fd("Stack fault\n", STDERR_FILENO);
	else if (status == SIGXCPU)
		ft_putstr_fd("CPU time limit exceeded (core dumped)\n", STDERR_FILENO);
	else if (status == SIGXFSZ)
		ft_putstr_fd("File size limit exceeded (core dumped)\n", STDERR_FILENO);
	else if (status == SIGVTALRM)
		ft_putstr_fd("Virtual timer expired\n", STDERR_FILENO);
	else if (status == SIGPROF)
		ft_putstr_fd("Profiling timer expired\n", STDERR_FILENO);
	else if (status == SIGPOLL)
		ft_putstr_fd("I/O possible\n", STDERR_FILENO);
	else if (status == SIGPWR)
		ft_putstr_fd("Power failure\n", STDERR_FILENO);
	else if (status == SIGSYS)
		ft_putstr_fd("Bad system call (core dumped)\n", STDERR_FILENO);
}
