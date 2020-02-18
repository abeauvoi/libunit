/*
** 1. Malloc, Free, Exit
** 2. Fork, Write
** 3. Wait + macros
** 4. Signal macros
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "libunit.h"


/*
** This function verifies the status returned by wait and compares the obtained
** result against an expected output.
** The color green will indicate that the test went as expected.
** And red the opposite.
** Since this code only relies on string literals, only addresses are compared
** to check if strings match or not.
*/

static unsigned int 	print_test_result(
		int stat_lock, const char *expected_output)
{
	const char 	*msg;
	const char 	*color;

	msg = NULL;
	if (WIFEXITED(stat_lock))
	{
		if (WEXITSTATUS(stat_lock) == 0)
			msg = OK;
		else
			msg = KO;
	}
	else if (WIFSIGNALED(stat_lock))
	{
		if (WTERMSIG(stat_lock) == SIGSEGV)
			msg = SEGV;
		else if (WTERMSIG(stat_lock) == SIGBUS)
			msg = BUSE;
	}
	color = (msg == expected_output ? GREEN : RED);
	ft_putstr(color);
	if (msg != NULL)
		ft_putstr(msg);
	ft_putstr(WHITE);
	return (color[3] == GREEN[3]);
}

static void 			execute_test(const t_unit_test *test)
{
	ft_putstr("> ");
	ft_putstr(test->name);
	ft_putstr(" : ");
	if (test->func() == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}

void 					print_total_passed_tests(unsigned int result_info)
{
	ft_putnbr((result_info >> 16) & 0xff);
	ft_putstr("/");
	ft_putnbr(result_info & 0xff);
	ft_putstr(" test");
	if ((result_info & 0xff) > 1)
		write(1, "s", 1);
	ft_putstr(" passed\n");
}

/*
** This is the core function of the library. It is meant to be returned by
** each launcher invoked in the main.
** This function will return an int that contains the number of successful
** tests on the 16 high-order bits and the total of tests done on the remaining
** bits.
*/

unsigned int			execute_tests(const t_unit_test *tests)
{
	pid_t			pid;
	int				stat_lock;
	unsigned int 	result_info;

	result_info = 0;
	while (tests->func != NULL)
	{
		pid = fork();
		if (pid == 0)
			execute_test(tests);
		else if (pid == -1
				&& write(2, "Fork error, skipping test...\n", 29) == -1)
			exit(EXIT_FAILURE);
		else
		{
			wait(&stat_lock);
			result_info += 1 + 
				(print_test_result(stat_lock, tests->expected_output) << 16);
		}
		++tests;
	}
	write(1, "\n", 1);
	return (result_info);
}
