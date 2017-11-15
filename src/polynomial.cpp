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
	//std::cout << "expression without spaces = " << this->_expression << std::endl;
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
			this->_sortedTerms.push_back(temp);
		}
		else
		{
			pos += 1;
			if (this->_signs.at(pos) == "+")
				this->_signs.at(pos) = "-";
			else
				this->_signs.at(pos) = "+";
			temp = this->_signs.at(pos) + this->_sign;
			this->_sortedTerms.push_back(temp);
		}
	}

}

void		Polynomial::validatePolynomial(void)
{
	float first = 0;
	float sec = 0;
	float third = 0;
	float fouth = 0;
	bool flag = false;
	bool f = false;
	bool s = false;
	bool t = false;
	std::string sign = "+";
	std::string temp;
	std::size_t found;
	std::regex validator("((\\+|-)?[0-9]+)(\\.([0-9]+))?((\\*)([a-zA-Z]+)(\\^)([0-9]))?");
	std::vector<std::string> v = this->_sortedTerms;
	this->_length = v.size();
	this->_val = v;

	for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
	{
		if (!regex_match(*it, validator)){
			std::cout << "failed to validate " << *it << " throw exception here" << std::endl;
			exit(0);
		}
	}

	this->_sortedTerms.erase (this->_sortedTerms.begin(), this->_sortedTerms.end());
	for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
	{
		temp = *it;
		//std::cout << "check " << temp << std::endl;
		found = temp.find("*");
		if (found == std::string::npos)
			temp += "*X^0";

		found = temp.find("*");
		if (found != std::string::npos)
		{
			if (temp.substr(found+1).compare("X^0") == 0)
			{
				first += std::stof(temp.substr(0, found));
				temp = std::to_string(first) + "*X^0";
				f = true;
			}
			else if (temp.substr(found+1).compare("X^1") == 0)
			{
				sec += std::stof(temp.substr(0, found));
				temp = std::to_string(sec) + "*X^1";
				s = true;
			}
			else if (temp.substr(found+1).compare("X^2") == 0)
			{
				third += std::stof(temp.substr(0, found));
				temp = std::to_string(third) + "*X^2";
				t = true;
			}
			else if (temp.substr(found+1).compare("X^3") == 0)
			{
				fouth += std::stof(temp.substr(0, found));
				temp = std::to_string(fouth) + "*X^3";
				flag = true;
			}
			//std::cout << "last " << temp.substr(found+1) << std::endl;
			//std::cout << "first " << temp.substr(0, found) << std::endl;
		}
		//std::cout << "terms = " << temp << std::endl;
	}
	if (f == true){
		if (first >= 0)
			this->_sortedTerms.push_back(sign + std::to_string(first) + "*X^0");
		else
			this->_sortedTerms.push_back(std::to_string(first) + "*X^0");
	}
	if (s == true){
		if (sec >= 0)
			this->_sortedTerms.push_back(sign + std::to_string(sec) + "*X^1");
		else
			this->_sortedTerms.push_back(std::to_string(sec) + "*X^1");
	}
	if (t == true){
		std::cout << third << "in \n";
		if (third >= 0)
			this->_sortedTerms.push_back(sign + std::to_string(third) + "*X^2");
		else
			this->_sortedTerms.push_back(std::to_string(third) + "*X^2");
	}
	if (flag == true){
		if (fouth >= 0)
			this->_sortedTerms.push_back(sign + std::to_string(fouth) + "*X^3");
		else
			this->_sortedTerms.push_back(std::to_string(fouth) + "*X^3");
	}

}

void		Polynomial::sortPolynomialExpression(void)
{
	std::vector<std::string> temp, tempStr;
	std::string tempIt;


	for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
	{
		tempIt = *it;
		std::reverse(tempIt.begin(), tempIt.end());
		temp.push_back(tempIt);
		//std::cout << "reversed terms = " << tempIt << std::endl;
	}
	std::sort(temp.begin(), temp.end());

	this->_sortedTerms.erase (this->_sortedTerms.begin(), this->_sortedTerms.end());
	for(std::vector<std::string>::iterator it = temp.begin(); it != temp.end(); ++it)
	{
		this->_sortedTerms.push_back(*it);
		//std::cout << "sorted 2 terms = " << *it << std::endl;
	}

	//tempStr = getTheSameDegreeTerms(temp);

	/*for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
	{		
		tempIt = *it;
		std::reverse(tempIt.begin(), tempIt.end());
		std::cout << "test2222 = " << tempIt << std::endl;
	}*/

	tempStr = this->_sortedTerms;
	this->_sortedTerms.erase (this->_sortedTerms.begin(), this->_sortedTerms.end());
	for(unsigned i = tempStr.size(); i-- > 0; )
	{
		tempIt = tempStr.at(i);
		std::reverse(tempIt.begin(), tempIt.end());
		this->_sortedTerms.push_back(tempIt);
		//std::cout << "reuben moswela = " << tempIt << std::endl;
	}
}

void		Polynomial::getDegreeOfPolynomial(void)
{
	std::string charToFind = "^";
	std::size_t found = this->_sortedTerms.at(0).find(charToFind);
	std::cout << "char " << this->_sortedTerms.at(0) << std::endl;
	if (found != std::string::npos)
	{
		this->_degreeOfPol = this->_sortedTerms.at(0).at(found+1);
		std::cout << "degree of polynomial = " << _degreeOfPol << std::endl;
		getDiscriminant(_degreeOfPol);
	}
	else
		std::cout << "degree of polynomial = 0 " << std::endl;
}

void		Polynomial::displayDiscriminant(void)
{
	if (_discriminant > 0)
		std::cout << "the discriminant is positive " << _discriminant<< " and the solutions are two " << std::endl;
	else if (_discriminant < 0)
		std::cout << "the discriminant is negative " << _discriminant << " and the solution is imaginary" << std::endl;
	else
		std::cout << "the discriminant is " << _discriminant << " and the solution is one "<< std::endl;
}

void		Polynomial::getDiscriminant(std::string degree)
{
	int num = std::stoi(degree);
	std::size_t found, found1;
	std::vector<std::string> tempVec;
	std::string temp, str_num;
	bool flag = false;

	if (num == 2)
	{
		int count = 0;
		for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
		{
			//std::cout << "disaster = " << *it << std::endl;
			temp = *it;
			found = temp.find("*");
			found1 = temp.find("^");
			if (found != std::string::npos)
			{
				str_num = temp.substr(0, found - 0);
				tempVec.push_back(str_num);
			}
			if (found1 != std::string::npos)
			{
				if (temp.substr(found1+1) == "1")
					flag = true;
			}
			count++;
		}
		//std::cout << "count = " << count << std::endl;
		_discriminant = solveDiscriminant(tempVec, flag);
		displayDiscriminant();
	}
}

float 		Polynomial::solveDiscriminant(std::vector<std::string> v, bool flag)
{
	int vecSize = v.size();
	/*std::cout << "vecSize = " << vecSize << std::endl;
	for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << "vector v = " << *it << std::endl;*/
	_a = std::stof(v.at(0));

	if (!v.at(1).empty())
		_b = std::stof(v.at(1));
	else
		_b = 0;
	//std::cout << "b = " << _b << std::endl;

	if (vecSize == 3)
		if (!v.at(2).empty())
			_c = std::stof(v.at(2));
		else
			_c = 0;
	else
		_c= 0;

	if (flag != true)
	{
		_c = _b;
		_b = 0;
	}
	/*std::cout << "c = " << _c << std::endl;
	std::cout << "a = " << _a << std::endl;
	std::cout << "b = " << _b << std::endl;
	std::cout << "c = " << _c << std::endl;*/
	return (_b * _b) - (4 * (_a * _c));
}


void		Polynomial::reducePolynomial(void)
{
	std::string reducedform = "Reduced Form : ";
	for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
		reducedform = reducedform + " " + *it;
	reducedform = reducedform + " = 0";
	
	std::cout << reducedform << std::endl;
}

void		Polynomial::degreeOfTwo(void)
{
	int length = this->_sortedTerms.size();
	/*std::cout << "length = " << length << std::endl;
	for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
		std::cout << "elements = " << *it << std::endl;*/
	if (length == 2)
		inverseOperation();
	else if (length == 3)
		factorsOfAConstant();
}

void		Polynomial::inverseOperation(void)
{
	std::size_t found;
	std::string step1 = "Step 1: ";
	std::string step2, hold;
	std::string temp;
	float divisor, dividend, num;
	int count = 0;
	int sign;

	for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
	{		
		temp = *it;
		found = temp.find("^");
		if (temp.at(0) == '+' && temp.at(found+1) == '0'){
			temp.replace(0, 1, "-");
			sign = -1;
		}
		else if (temp.at(0) == '-' && temp.at(found+1) == '0'){
			temp.replace(0, 1, "+");
			sign = 1;
		}

		if (count != 1)
			step1 = step1 + temp + " = ";
		else
			step1 = step1 + temp;
		count++;
	}
	std::cout << step1 << std::endl;

	count = 0;
	for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
	{
		temp = *it;
		found = temp.find("*");
		if (count != 1)
		{
			hold = temp.substr(found+1);
			divisor = std::stof(temp.substr(0, found - 0));
			step2 = temp.substr(0, found - 0) + step2;
			step2 = " / " + temp.substr(0, found - 0);
		}
		else
		{
			dividend = std::stof(temp.substr(0, found - 0));
			if (sign == -1)
				temp.replace(0, 1, "-");
			else
				temp.replace(0, 1, "+");
			step2 = temp.substr(0, found - 0) + step2;
		}
		count++;
	}
	num = (sign * dividend) / divisor;
	std::cout << "Step 2: " << hold << " = " <<step2 << std::endl;
	std::cout << "Step 3: " << "√"<< hold << " = √" << std::setprecision(4) << num << std::endl;
	std::cout << "discriminant = " << _discriminant << std::endl;
	//std::cout << "num = " << num << std::endl;
	if (_discriminant < 0)
	{
		std::cout << "Step 4: " << hold.at(0) << " = √" << "-1*" << num * -1 << std::endl;
		std::cout << "Solution: " << hold.at(0) << " = ±i√" << num * -1 << std::endl;
	}
	else
	{
		if (num < 0)
			num *= -1;
		num = calculateRoot(num);
		std::cout << "Solution: \n";
		std::cout << num << std::endl;
		std::cout << "-" << num << std::endl;
	}
}

float		Polynomial::calculateRoot(float number)
{
	float error = 0.00001; //define the precision of your result
    float root = number;

    while ((root - number / root) > error) //loop until precision satisfied 
        root = (root + number / root) / 2;
	
	//std::cout << "The Square root is: " << std::setprecision(3) << root << std::endl;
    return root;
}

void		Polynomial::degreeOfOne(void)
{
	int sign;
	std::size_t found;
	std::string step1 = "Step 1: ";
	std::string step2;
	std::string temp;
	int count = 0;
	float divisor, dividend, num;

	for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
	{
		std::cout << "temp = " << *it << std::endl;
		temp = *it;
		found = temp.find("^");
		if (temp.at(0) == '+' && temp.at(found+1) == '0'){
			temp.replace(0, 1, "-");
			sign = -1;
		}
		else if (temp.at(0) == '-' && temp.at(found+1) == '0'){
			temp.replace(0, 1, "+");
			sign = 1;
		}

		if (count != 1)
			step1 = step1 + temp + " = ";
		else
			step1 = step1 + temp;
		count++;
	}
	std::cout << step1 << std::endl;
	std::cout << "Sign1 " << sign << std::endl;

	count = 0;
	for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
	{
		temp = *it;
		found = temp.find("*");
		if (count != 1)
		{
			divisor = std::stof(temp.substr(0, found - 0));
			step2 =  " / " + temp.substr(0, found - 0);
		}
		else
		{
			dividend = std::stof(temp.substr(0, found - 0));
			if (sign == -1)
				temp.replace(0, 1, "-");
			else{
				temp.replace(0, 1, "+");
				dividend *= -1;
			}
			step2 = temp.substr(0, found - 0) + step2;
		}
		count++;
	}
	std::cout << "Step 2: " << step2 << std::endl;
	std::cout << "Sign " << sign << std::endl;
	std::cout << "dividend " << dividend << std::endl;
	std::cout << "divisor " << divisor << std::endl;
	num = (sign * dividend) / divisor;
	std::cout << "Solution: \n"; 
	std::cout << std::setprecision(3) << num << std::endl;
}

void		Polynomial::degreeOfZero(void)
{
	std::size_t found, found1;
	float num = 0;
	//std::cout << _length << " The is no solution: \n";

	if (_length == 2){
		found = this->_val.at(0).find("*");
		found1 = this->_val.at(1).find("*");
		if (std::stof(_val.at(1).substr(0, found1 - 0)) == (-1 * std::stof(_val.at(0).substr(0, found - 0))))
			std::cout << "All real numbers are solutions \n";
		else
			std::cout << "There is no solution \n";
	}
	else if (_length == 1)
	{
		for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
		{
			found = (*it).find("*");
			if (found != std::string::npos)
				num += std::stof((*it).substr(0, found - 0));
		}
		std::cout << "The solution is: \n";
		std::cout << std::setprecision(3) << num << std::endl;
	}
}

void		Polynomial::factorsOfAConstant(void)
{
    float x1, x2;

    if (_discriminant == 0)
    {
    	x1 = ((-1 * _b) + (calculateRoot(_discriminant))) / (2 * _a);
    	std::cout << "fucking solution is: " <<std::setprecision(5) << x1 << std::endl;
    }
    else if (_discriminant > 0)
    {
    	x1 = ((-1 * _b) + (calculateRoot(_discriminant))) / (2 * _a);
    	x2 = ((-1 * _b) - (calculateRoot(_discriminant))) / (2 * _a);
    	std::cout << "fucking solution is \n";
    	std::cout << std::setprecision(5) << x1 << std::endl;
    	std::cout << std::setprecision(5) << x2 << std::endl;
	}
	else if (_discriminant < 0)
	{
		std::cout << "Step 1: X " << " = " << ((-1*_b) / (2*_a)) << " √" << "-1*" << _discriminant * -1 << std::endl;
		std::cout << "Solution: X " << " = "<< ((-1*_b) / (2*_a)) << " ±i√" << _discriminant * -1 << std::endl;
	}
}

void		Polynomial::solvePolynomial(void)
{
	if (std::stoi(this->_degreeOfPol) == 2)
		degreeOfTwo();
	else if (std::stoi(this->_degreeOfPol) == 1)
		degreeOfOne();
	else if (std::stoi(this->_degreeOfPol) == 0)
		degreeOfZero();
}

int 	Polynomial::degreeOfPolynomial(void)
{
	return std::stoi(this->_degreeOfPol);
}
