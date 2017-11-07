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
 * function to split the expression into terms
 */
void		Polynomial::tokenizeTerms(void)
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

}

void		Polynomial::groupTerms(void)
{
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

}

void		Polynomial::validatePolynomial(void)
{
	std::regex validator("((\\+|-)?[0-9]+)(\\.([0-9]+))?((\\*)([a-zA-Z]+)(\\^)([0-9]))?");

	for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
	{
		std::cout << "sorted terms = " << *it << std::endl;
		if (regex_match(*it, validator))
			std::cout << "validated " << *it << std::endl;
		else
			std::cout << "failed to validate " << *it << " throw exception here" << std::endl;
	}

}

void		Polynomial::sortPolynomialExpression(void)
{
	std::vector<std::string> temp;
	std::string tempIt;
	std::vector<std::string>::reverse_iterator rit = this->_sortedTerms.rbegin();

	for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
	{
		tempIt = *it;
		std::reverse(tempIt.begin(), tempIt.end());
		temp.push_back(tempIt);
		std::cout << "reversed terms = " << tempIt << std::endl;
	}
	std::sort(temp.begin(), temp.end());

  	for (size_t length = 0 ; rit!= this->_sortedTerms.rend(); ++rit)
  	{
  		tempIt = temp.at(length);
  		std::reverse(tempIt.begin(), tempIt.end());
    	*rit = tempIt;
    	length++;
  	}

  	for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
	{
		std::cout << "reuben = " << *it << std::endl;
	}

	for(std::vector<std::string>::iterator it = temp.begin(); it != temp.end(); ++it)
		std::cout << "sorted terms = " << *it << std::endl;
}

void		Polynomial::getDegreeOfPolynomial(void)
{
	std::string charToFind = "^";
	std::string degree;
	std::size_t found = this->_sortedTerms.at(0).find(charToFind);
	if (found != std::string::npos)
	{
		degree = this->_sortedTerms.at(0).at(found+1);
		std::cout << "degree of polynomial = " << degree << std::endl;
		getDiscriminant(degree);
	}
	else
		std::cout << "degree of polynomial = 0 " << std::endl;
}

void		Polynomial::getDiscriminant(std::string degree)
{
	int num = std::stoi(degree);
	if (num == 2)
	{
		int a = this->_sortedTerms.at(0).at(1);
	}
}

void		Polynomial::reducePolynomial(void)
{}

void		Polynomial::solvePolynomial(void)
{}
