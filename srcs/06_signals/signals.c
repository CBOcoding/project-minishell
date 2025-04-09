#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <termios.h>

volatile sig_atomic_t g_signal = 0;

void	handle_sigint(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int signum)
{
	(void)signum;
	g_signal = SIGQUIT;
	rl_on_new_line();          // riposiziona correttamente la riga
	rl_replace_line("", 0);    // svuota input buffer
	rl_redisplay();            // ridisegna il prompt
	/* Do nothing on Ctrl+\ */
}

void	disable_echoctl(void)
{
	struct termios term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL; /* disattiva stampa ^C ^\ */
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	setup_signals(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	// Setup SIGINT (Ctrl+C)
	sa_int.sa_handler = handle_sigint;           // custom handler
	sigemptyset(&sa_int.sa_mask);                // don't block other signals during handler
	sa_int.sa_flags = SA_RESTART;                // restart interrupted syscalls
	sigaction(SIGINT, &sa_int, NULL);            // register the handler for SIGINT

	// Setup SIGQUIT (Ctrl+\)
	sa_quit.sa_handler = handle_sigquit;         // custom handler (does nothing)
	sigemptyset(&sa_quit.sa_mask);               // same here
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);          // register for SIGQUIT

	// disable_echoctl(); /* disable the print of Ctrl+^C (stampato poi manualmente) and Ctrl+^\ */
}
