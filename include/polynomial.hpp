#ifndef POLYNOMIAL_HPP
# define POLYNOMIAL_HPP

#include <cstring>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <regex>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>

class Polynomial
{
	private:
		std::string		_expression;
		std::string		_degreeOfPol;
		float			_a, _b, _c, _y1, _y2;
		std::string		_sign;
		int				_pos;
		int 			_discriminant;

		std::vector<std::string> _unsortedTerms;
		std::vector<std::string> _sortedTerms;
		std::vector<std::string> _signs;
		Polynomial();
		void	checkSignOfFirstTerm(void);
		void	checkSignAfterEqual(int pos);
		void	removeSpaces(void);
		int		solveDiscriminant(std::vector<std::string> v, bool flag);
		void	getDiscriminant(std::string degree);
		std::vector<std::string>	getTheSameDegreeTerms(std::vector<std::string> temp);
		void	displayDiscriminant(void);
		void	inverseOperation(void);
		float	calculateRoot(float num);

	public:
		Polynomial(std::string expre);
		Polynomial(Polynomial const & target);
		Polynomial	& operator=(Polynomial const & target);
		~Polynomial();

		void	retriveSigns(void);
		void	tokenizeTerms(void);
		void	groupTerms(void);
		void	validatePolynomial(void);
		void	sortPolynomialExpression(void);
		void	getDegreeOfPolynomial(void);
		void	reducePolynomial(void);
		void	factorsOfAConstant(void);
		void	solvePolynomial(void);
		void	degreeOfTwo();
		void	degreeOfOne();
		void	degreeOfZero();
};

#endif
