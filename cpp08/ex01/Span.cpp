#include "Span.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>

Span::Span() : _numbers(), _maxSize(0) {}

Span::Span(unsigned int maxSize) : _numbers(), _maxSize(maxSize) {}

Span::Span(const Span& other) : _numbers(other._numbers), _maxSize(other._maxSize) {}

Span::~Span() {}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_numbers = other._numbers;
		_maxSize = other._maxSize;
	}
	return *this;
}

void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw std::overflow_error("Span is full");
	_numbers.push_back(number);
}

int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers to find a span");
	std::vector<int> sorted(_numbers);
	std::sort(sorted.begin(), sorted.end());
	long shortest = static_cast<long>(sorted[1]) - static_cast<long>(sorted[0]);
	for (std::size_t i = 2; i < sorted.size(); ++i)
	{
		long distance = static_cast<long>(sorted[i]) - static_cast<long>(sorted[i - 1]);
		if (distance < shortest)
			shortest = distance;
	}
	if (shortest > std::numeric_limits<int>::max())
		throw std::overflow_error("Shortest span exceeds int range");
	return static_cast<int>(shortest);
}

int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Not enough numbers to find a span");
	std::vector<int>::const_iterator smallest = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator largest = std::max_element(_numbers.begin(), _numbers.end());
	long distance = static_cast<long>(*largest) - static_cast<long>(*smallest);
	if (distance > std::numeric_limits<int>::max())
		throw std::overflow_error("Longest span exceeds int range");
	return static_cast<int>(distance);
}
