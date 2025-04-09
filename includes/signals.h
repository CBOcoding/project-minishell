#ifndef SIGNALS_H
# define SIGNALS_H

#include <signal.h> // required for sig_atomic_t and sigaction

extern volatile sig_atomic_t g_signal;

void	handle_sigint(int signum);
void	handle_sigquit(int signum);
void	setup_signals(void);
void	disable_echoctl(void);

#endif