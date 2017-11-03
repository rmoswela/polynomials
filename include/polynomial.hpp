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
		std::size_t		_plus;
		std::size_t		_minus;
		std::size_t		_equals;
		std::string		_sign;
		int				_pos;

		std::vector<std::string> _unsortedTerms;
		std::vector<std::string> _sortedTerms;
		std::vector<std::string> _signs;
		Polynomial();
		void	checkSignOfFirstTerm(void);
		void	checkSignAfterEqual(int pos);
		void	removeSpaces(void);

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
