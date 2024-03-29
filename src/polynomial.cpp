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
	std::regex validator("((\\+|-)?[0-9]+)(\\.([0-9]+))?((\\*)([a-zA-Z]+)(\\^)([0-9]))?");

	for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
	{
		std::cout << "sorted terms = " << *it << std::endl;
		if (!regex_match(*it, validator))
			std::cout << "failed to validate " << *it << " throw exception here" << std::endl;
		//else
			//std::cout << "validated " << *it << std::endl;
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
		std::cout << "reversed terms = " << tempIt << std::endl;
	}
	std::sort(temp.begin(), temp.end());

	for(std::vector<std::string>::iterator it = this->_sortedTerms.begin(); it != this->_sortedTerms.end(); ++it)
		std::cout << "sorted 2 terms = " << *it << std::endl;

	tempStr = getTheSameDegreeTerms(temp);

	this->_sortedTerms.erase (this->_sortedTerms.begin(), this->_sortedTerms.end());
	for(unsigned i = tempStr.size(); i-- > 0; )
	{
		tempIt = tempStr.at(i);
		std::reverse(tempIt.begin(), tempIt.end());
		this->_sortedTerms.push_back(tempIt);
		std::cout << "reuben moswela = " << tempIt << std::endl;
	}
}

void		Polynomial::getDegreeOfPolynomial(void)
{
	std::string charToFind = "^";
	std::size_t found = this->_sortedTerms.at(0).find(charToFind);
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
		std::cout << "the discriminant is positive " << _discriminant<< " and two solutions are = " << std::endl;
	else if (_discriminant < 0)
		std::cout << "the discriminant is negative " << _discriminant << " and the imaginary solution is = " << std::endl;
	else
		std::cout << "the discriminant is zero " << _discriminant << " the one solution is = "<< std::endl;
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
			std::cout << "disaster = " << *it << std::endl;
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
		std::cout << "count = " << count << std::endl;
		_discriminant = solveDiscriminant(tempVec, flag);
		displayDiscriminant();
	}
}

float 		Polynomial::solveDiscriminant(std::vector<std::string> v, bool flag)
{
	int vecSize = v.size();
	std::cout << "vecSize = " << vecSize << std::endl;
	for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << "vector v = " << *it << std::endl;
	_a = std::stof(v.at(0));

	if (!v.at(1).empty())
		_b = std::stof(v.at(1));
	else
		_b = 0;
	std::cout << "b = " << _b << std::endl;

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
	std::cout << "c = " << _c << std::endl;
	std::cout << "a = " << _a << std::endl;
	std::cout << "b = " << _b << std::endl;
	std::cout << "c = " << _c << std::endl;
	return (_b * _b) - (4 * (_a * _c));
}

std::vector<std::string>		Polynomial::getTheSameDegreeTerms(std::vector<std::string> temp)
{
	std::size_t found;
	std::string hold, tempStr, firstPartOfTerm, lastPartOfTerm, firstTerm, secondTerm, totalTerm;
	int count;
	float firstNum, secondNum, total;
	std::vector<std::string> vec;
	count = 0;

	for(std::vector<std::string>::iterator it = temp.begin(); it != temp.end(); ++it)
	{
		tempStr = *it;
		found = tempStr.find("*");

		std::cout << "firstPartOfTerm = " << firstPartOfTerm << std::endl;
		std::cout << "lastPartOfTerm = " << lastPartOfTerm << std::endl;
		std::cout << "tempStr = " << tempStr << std::endl;

		if (count >= 1 && found != std::string::npos)
		{
			if (firstPartOfTerm.compare(tempStr.substr(0, found - 0)) == 0)
			{
				hold = firstPartOfTerm;
				firstTerm = tempStr.substr(found+1);

				std::cout << "numbers to add = " <<  firstTerm << std::endl;
				std::cout << "numbers to add = " << lastPartOfTerm << std::endl;
				reverse(firstTerm.begin(),firstTerm.end());
				reverse(lastPartOfTerm.begin(),lastPartOfTerm.end());

				std::cout << "numbers to add after rev = " <<  firstTerm << std::endl;
				std::cout << "numbers to add after rev = " <<  lastPartOfTerm << std::endl;
				firstNum = stof(firstTerm);
				secondNum = stof(lastPartOfTerm);
				total = firstNum + secondNum;
				std::cout << "total after rounding = " << total << std::endl;
				totalTerm = std::to_string(total);
				std::cout << "totalTerm = " <<  totalTerm << std::endl;
				reverse(totalTerm.begin(),totalTerm.end());
				if (total > 0)
					totalTerm = firstPartOfTerm + "*" + totalTerm + "+";
				else
					totalTerm = firstPartOfTerm + "*" + totalTerm;
				std::cout << "totalTerm after reversing = " <<  totalTerm << std::endl;
				std::cout << "numbers to add after converting = " <<  firstNum << std::endl;
				std::cout << "numbers to add after converting = " <<  secondNum << std::endl;
				std::cout << "numbers to add after converting = " <<  total << std::endl;
				//temp.erase(temp.begin()+ (1 - std::distance(temp.begin(), it)));
				//temp.erase(temp.begin() + (std::distance(temp.begin(), it)));
				vec.push_back(totalTerm);

			}
			std::cout << "to add = " << tempStr << std::endl;
			if (hold.compare(tempStr.substr(0, found - 0)) != 0)
				vec.push_back(tempStr);
		}
		if(tempStr.size() == 2)
			vec.push_back(tempStr);

		if (found != std::string::npos)
		{
			firstPartOfTerm = tempStr.substr(0, found - 0);
			lastPartOfTerm = tempStr.substr(found+1);
		}
		std::cout << "count = " << count << std::endl;
		count++;
	}

	std::size_t found1 = totalTerm.find("*");
	for(std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		tempStr = *it;
		found = tempStr.find("*");
		if (found != std::string::npos)
		{
			if (tempStr.substr(0, found - 0).compare(totalTerm.substr(0, found1 - 0)))
			{
				std::cout << "\n"; //<< tempStr << std::endl; 
			}
		}
		std::cout << "new values = " << *it << std::endl;
	}
	return vec;
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
	std::cout << "length = " << length << std::endl;
	for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
		std::cout << "elements = " << *it << std::endl;
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
	std::cout << "num = " << num << std::endl;
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
	
	std::cout << "The Square root is: " << std::setprecision(3) << root << std::endl;
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
			divisor = std::stof(temp.substr(0, found - 0));
			step2 =  " / " + temp.substr(0, found - 0);
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
	std::cout << "Step 2: " << step2 << std::endl;
	num = (sign * dividend) / divisor;
	std::cout << "Solution: \n"; 
	std::cout << std::setprecision(3) << num << std::endl;
}

void		Polynomial::degreeOfZero(void)
{
	std::size_t found;
	std::string temp;
	float num;
	for(std::vector<std::string>::iterator it = _sortedTerms.begin(); it != _sortedTerms.end(); ++it)
	{
		temp = *it;
		found = temp.find("*");
		if (found != std::string::npos)
			num = std::stof(temp.substr(0, found - 0));

	}
	std::cout << "The solution is: \n";
	std::cout << std::setprecision(3) << num << std::endl;
}

void		Polynomial::factorsOfAConstant(void)
{
	/*int length, count, i, sign;
	float mul, add, sub;
	std::vector<int> vec;

	sign = _c < 0 ? -1 : 1;
	std::cout << "sign = " << sign << std::endl;
	int c = static_cast<int>(_c);

    std::cout << "Factors of " << _c << " are: " << std::endl;  
    for(i = 1; i <= c; ++i)
    {
        if(c % i == 0)
        {
            vec.push_back(i);
            std::cout << i << std::endl;
        }
    }

    length = vec.size();
    std::cout << "length = " << length << std::endl;
    i = 0;
    count = 0;
    while(i < length)
    {
        for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            mul = (vec.at(i) * *it);
            add = (vec.at(i) + *it);
            sub = (vec.at(i) - *it);
            std::cout << "addition = " << add << std::endl;
            std::cout << "multiplication = " << mul << std::endl;
            std::cout << "subtraction = " << sub << std::endl;
            if (mul == _c && (add == _b || sub == _b))
            {
                std::cout << "i got you " << vec.at(i) << " and " << *it << std::endl;
                count++;
                break;
            }
        }

        if (count == 1)
            break;
        i++;
    }*/

    float x1, x2;

    x1 = ((-1 * _b) + (calculateRoot(_discriminant))) / (2 * _a);
    x2 = ((-1 * _b) - (calculateRoot(_discriminant))) / (2 * _a);
    std::cout << "fucking solution is \n";
    std::cout << x1 << std::endl;
    std::cout << x2 << std::endl;
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
