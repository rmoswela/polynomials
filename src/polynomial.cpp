#include "polynomial.hpp"

Polynomial::Polynomial(std::string expression)
{
	this->_expression = expression;
}

Polynomial::Polynomial(Polynomial const & target)
{
	*this = target;
	return;
}

Polynomial	&	Polynomial::operator=(Polynomial const & target)
{
	if (this != &target)
		*this = target;
	return *this;
}

Polynomial::~Polynomial()
{}


void		Polynomial::retriveSigns(void)
{
	std::size_t plus = this->_expression.find("+");
	std::size_t minus = this->_expression.find("-");
	std::size_t equals = this->_expression.find("=");

	if (plus != std::string::npos)
		this->_plus = plus;
	else if (minus != std::string::npos)
		this->_minus = minus;
	else if (equals != std::string::npos)
		this->_equals = equals;
}

/*
 * function to group like terms of the expression
 */
void		Polynomial::groupTerms(void)
{
	char *express = new char[this->_expression.length()+1];
	std::strcpy(express, this->_expression.c_str());

	char *token = std::strtok(express, "+-=");
	while (token != NULL)
	{
		std::cout << "token string = " << token << std::endl;
		this->_terms.push_back(token);
		token = std::strtok(NULL, "+-=");
	}


	for (std::vector<std::string>::iterator it = this->_terms.begin(); it != this->_terms.end(); ++it)
	{
		std::cout << "token in vector = " << *it << std::endl;
	}
}

void		Polynomial::validatePolynomial(void)
{}

void		Polynomial::getDegreeOfPolynomial(void)
{
}

void		Polynomial::reducePolynomial(void)
{}

void		Polynomial::solvePolynomial(void)
{}
