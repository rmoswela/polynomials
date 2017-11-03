#include "polynomial.hpp"

Polynomial::Polynomial(std::string expression)
{
	this->_expression = expression;
	removeSpaces();
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

void		Polynomial::removeSpaces(void)
{
	this->_expression.erase(std::remove(this->_expression.begin(), this->_expression.end(), ' '), this->_expression.end());
	std::cout << "expression without spaces = " << this->_expression << std::endl;
}

void		Polynomial::checkSignOfFirstTerm(void)
{
	if (this->_expression.at(0) == '-')
		this->_signs.push_back("-");
	else
		this->_signs.push_back("+");
}

void		Polynomial::checkSignAfterEqual(int pos)
{
	if (this->_expression.at(pos) == '-')
		this->_signs.push_back("-");
	else
		this->_signs.push_back("+");
}

void		Polynomial::retriveSigns(void)
{

	for (std::string::iterator it = this->_expression.begin(); it != this->_expression.end(); ++it)
	{
		if (std::distance(this->_expression.begin(), it) == 0)
			checkSignOfFirstTerm();
		else
		{
			this->_sign = *it;
			if (this->_sign.compare("+") == 0)
				this->_signs.push_back("+");
			else if (this->_sign.compare("-") == 0)
				this->_signs.push_back("-");
			else if (this->_sign.compare("=") == 0)
			{
				this->_signs.push_back("=");
				it++;
				checkSignAfterEqual(std::distance(this->_expression.begin(), it));
			}
		}
	}

	for(std::vector<std::string>::iterator it = this->_signs.begin(); it != this->_signs.end(); ++it)
	{
		std::cout << "signs found = " << *it << std::endl;
	}
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
		this->_unsortedTerms.push_back(token);
		token = std::strtok(NULL, "+-=");
	}


		std::string temp;
		int pos;

	for (std::vector<std::string>::iterator it = this->_unsortedTerms.begin(); it != this->_unsortedTerms.end(); ++it)
	{
		this->_sign = *it;
		pos = std::distance(this->_unsortedTerms.begin(), it);
		if (this->_signs.at(pos).compare("=") != 0)
		{
			temp = this->_signs.at(pos) + this->_sign;
			std::cout << "sign = " << this->_signs.at(pos) << std::endl;
			std::cout <<  "temp = " << temp << std::endl;
			this->_sortedTerms.push_back(temp);
		}
		else
		{
			pos += 1;
			temp = this->_signs.at(pos) + this->_sign;
			std::cout << "sign = " << this->_signs.at(pos) << std::endl;
			std::cout <<  "temp = " << temp << std::endl;
			this->_sortedTerms.push_back(temp);
		}
		//std::cout << "token in vector = " << *it << std::endl;
	}

	for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
	{
		std::cout << "sorted terms = " << *it << std::endl;
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
