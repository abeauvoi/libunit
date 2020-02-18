# ifndef LIBUNIT_H
 # define LIBUNIT_H

# define OK "[OK]\n"
# define KO "[KO]\n"
# define SEGV "[SEGV]\n"
# define BUSE "[BUSE]\n" 
# define RED "\033[31m"
# define GREEN "\033[32m"
# define WHITE "\033[37m"

typedef struct 	s_unit_test
{
	int 		(*func)(void);
	const char 	*name;
	const char 	*expected_output;
}				t_unit_test;

void 			ft_putstr(const char *str);
size_t 			ft_strlen(const char *str);
void 			ft_putnbr(int nb);
void 			print_total_passed_tests(unsigned int result_info);
unsigned int 	execute_tests(const t_unit_test *test_suite);

# endif
