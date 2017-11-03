#include <polynomial.hpp>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "The number of arguments expected is two!\n";
		exit(EXIT_FAILURE);
	}
	else
	{
		std::string s(*++argv);
		Polynomial pol(s);
		pol.retriveSigns();
		pol.groupTerms();
		std::cout << "You have the required arguments\n";
	}
	return 0;
}
