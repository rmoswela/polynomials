#ifndef POLYNOMIAL_HPP
# define POLYNOMIAL_HPP

#include <cstring>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <regex>
#include <vector>

class Polynomial
{
	private:
		std::string		_expression;
		std::string		_plus;
		std::string		_minus;
		std::string		_equals;

		std::vector<std::string> _terms;
		Polynomial();

	public:
		Polynomial(std::string expre);
		Polynomial(Polynomial const & target);
		Polynomial	& operator=(Polynomial const & target);
		~Polynomial();

		void	retriveSigns(void);
		void	groupTerms(void);
		void	validatePolynomial(void);
		void	getDegreeOfPolynomial(void);
		void	reducePolynomial(void);
		void	solvePolynomial(void);
};

#endif
