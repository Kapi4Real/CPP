#include "RPN.hpp"

#include <cctype>
#include <limits>
#include <sstream>
#include <stack>
#include <string>

namespace
{
bool calculate(long long left, long long right, char operation,
    long long& result, std::string& error)
{
    const long long maximum = std::numeric_limits<long long>::max();
    const long long minimum = std::numeric_limits<long long>::min();

    if (operation == '+')
    {
        if ((right > 0 && left > maximum - right)
            || (right < 0 && left < minimum - right))
        {
            error = "integer overflow";
            return false;
        }
        result = left + right;
    }
    else if (operation == '-')
    {
        if ((right < 0 && left > maximum + right)
            || (right > 0 && left < minimum + right))
        {
            error = "integer overflow";
            return false;
        }
        result = left - right;
    }
    else if (operation == '*')
    {
        long double product = static_cast<long double>(left)
            * static_cast<long double>(right);
        if (product > static_cast<long double>(maximum)
            || product < static_cast<long double>(minimum))
        {
            error = "integer overflow";
            return false;
        }
        result = left * right;
    }
    else if (operation == '/')
    {
        if (right == 0)
        {
            error = "division by zero";
            return false;
        }
        if (left == minimum && right == -1)
        {
            error = "integer overflow";
            return false;
        }
        result = left / right;
    }
    else
    {
        error = "invalid operator";
        return false;
    }
    return true;
}
}

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
    static_cast<void>(other);
}

RPN& RPN::operator=(const RPN& other)
{
    static_cast<void>(other);
    return *this;
}

RPN::~RPN()
{
}

bool RPN::evaluate(const std::string& expression, long long& result,
    std::string& error) const
{
    std::istringstream input(expression);
    std::stack<long long> numbers;
    std::string token;
    bool hasToken = false;

    while (input >> token)
    {
        hasToken = true;
        if (token.size() == 1
            && std::isdigit(static_cast<unsigned char>(token[0])))
        {
            numbers.push(token[0] - '0');
        }
        else if (token.size() == 1
            && (token[0] == '+' || token[0] == '-' || token[0] == '*'
                || token[0] == '/'))
        {
            if (numbers.size() < 2)
            {
                error = "not enough operands";
                return false;
            }
            long long right = numbers.top();
            numbers.pop();
            long long left = numbers.top();
            numbers.pop();
            long long partialResult = 0;
            if (!calculate(left, right, token[0], partialResult, error))
                return false;
            numbers.push(partialResult);
        }
        else
        {
            error = "invalid token: " + token;
            return false;
        }
    }

    if (!hasToken || numbers.size() != 1)
    {
        error = "invalid expression";
        return false;
    }
    result = numbers.top();
    return true;
}
