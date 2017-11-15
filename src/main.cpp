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
		std::string argument(*++argv);
		Polynomial pol(argument);
		pol.retriveSigns();
		pol.tokenizeTerms();
		pol.groupTerms();
		pol.validatePolynomial();
		pol.sortPolynomialExpression();
		pol.getDegreeOfPolynomial();
		if (pol.degreeOfPolynomial() > 0)
			pol.reducePolynomial();
		if (pol.degreeOfPolynomial() > 2)
			std::cout << "The polynomial degree is stricly greater than 2, I can't solve.\n";
		pol.solvePolynomial();
	}
	return 0;
}
