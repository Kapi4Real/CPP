#include "ScalarConverter.hpp"
#include <cerrno>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

static bool parseNumber(const std::string& input, double& value, bool& isFloat)
{
	std::string text(input);
	isFloat = false;
	if (!text.empty() && (text[text.size() - 1] == 'f' || text[text.size() - 1] == 'F'))
	{
		isFloat = true;
		text.erase(text.size() - 1);
	}
	if (text.empty())
		return false;
	if (isFloat && text.find_first_of(".eE") == std::string::npos)
		return false;
	size_t i = 0;
	if (text[i] == '+' || text[i] == '-')
		++i;
	size_t digits = 0;
	while (i < text.size() && std::isdigit(static_cast<unsigned char>(text[i])))
	{
		++digits;
		++i;
	}
	if (i < text.size() && text[i] == '.')
	{
		++i;
		while (i < text.size() && std::isdigit(static_cast<unsigned char>(text[i])))
		{
			++digits;
			++i;
		}
	}
	if (digits == 0)
		return false;
	if (i < text.size() && (text[i] == 'e' || text[i] == 'E'))
	{
		++i;
		if (i < text.size() && (text[i] == '+' || text[i] == '-'))
			++i;
		size_t exponentDigits = 0;
		while (i < text.size() && std::isdigit(static_cast<unsigned char>(text[i])))
		{
			++exponentDigits;
			++i;
		}
		if (exponentDigits == 0)
			return false;
	}
	if (i != text.size())
		return false;
	char* end = NULL;
	errno = 0;
	value = std::strtod(text.c_str(), &end);
	if (errno == ERANGE || end == text.c_str() || *end != '\0')
		return false;
	return true;
}

static bool isSpecial(const std::string& text)
{
	return text == "nan" || text == "nanf" || text == "NaN" || text == "NaNf"
		|| text == "+inf" || text == "-inf" || text == "inf"
		|| text == "+inff" || text == "-inff" || text == "inff"
		|| text == "+INF" || text == "-INF" || text == "INF"
		|| text == "+INFF" || text == "-INFF" || text == "INFF";
}

static std::string normalizeSpecial(std::string text, bool wantFloat)
{
	if (text == "nanf" || text == "NaNf") text = "nan";
	if (text == "NaN") text = "nan";
	if (text == "inff") text = "inf";
	if (text == "+inff") text = "+inf";
	if (text == "-inff") text = "-inf";
	if (text == "+INF") text = "+inf";
	if (text == "-INF") text = "-inf";
	if (text == "INF") text = "inf";
	if (text == "+INFF") text = "+inf";
	if (text == "-INFF") text = "-inf";
	if (text == "INFF") text = "inf";
	if (wantFloat && (text == "nan" || text == "inf" || text == "+inf" || text == "-inf"))
		text += "f";
	return text;
}

static void printNumeric(double value, bool valid, bool isSpecialValue)
{
	if (!valid || isSpecialValue || value < std::numeric_limits<int>::min()
		|| value > std::numeric_limits<int>::max())
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(value) << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
	if (literal.empty())
	{
		std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << std::endl;
		return;
	}
	if (literal.size() == 1 && !std::isdigit(static_cast<unsigned char>(literal[0])))
	{
		char c = literal[0];
		std::cout << "char: ";
		if (std::isprint(static_cast<unsigned char>(c))) std::cout << "'" << c << "'" << std::endl;
		else std::cout << "Non displayable" << std::endl;
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
		return;
	}
	if (literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'')
	{
		char c = literal[1];
		std::cout << "char: ";
		if (std::isprint(static_cast<unsigned char>(c))) std::cout << "'" << c << "'" << std::endl;
		else std::cout << "Non displayable" << std::endl;
		std::cout << "int: " << static_cast<int>(c) << std::endl;
		std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
		return;
	}
	const bool special = isSpecial(literal);
	bool isFloat = false;
	double value = 0.0;
	const bool valid = special || parseNumber(literal, value, isFloat);
	if (special)
	{
		if (literal.find("nan") != std::string::npos || literal.find("NaN") != std::string::npos) value = std::numeric_limits<double>::quiet_NaN();
		else if (literal[0] == '-') value = -std::numeric_limits<double>::infinity();
		else value = std::numeric_limits<double>::infinity();
	}
	std::cout << "char: ";
	if (!valid || special || value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(static_cast<unsigned char>(static_cast<char>(value))))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;
	std::cout << "int: ";
	printNumeric(value, valid, special);
	std::cout << "float: ";
	if (!valid) std::cout << "impossible" << std::endl;
	else if (special) std::cout << normalizeSpecial(literal, true) << std::endl;
	else if (value > std::numeric_limits<float>::max() || value < -std::numeric_limits<float>::max()) std::cout << "impossible" << std::endl;
	else std::cout << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
	std::cout << "double: ";
	if (!valid) std::cout << "impossible" << std::endl;
	else if (special) std::cout << normalizeSpecial(literal, false) << std::endl;
	else std::cout << std::fixed << std::setprecision(1) << value << std::endl;
}
