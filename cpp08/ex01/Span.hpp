#ifndef SPAN_HPP
#define SPAN_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>

class Span
{
private:
	std::vector<int> _numbers;
	unsigned int _maxSize;

public:
	Span();
	explicit Span(unsigned int maxSize);
	Span(const Span& other);
	~Span();
	Span& operator=(const Span& other);

	void addNumber(int number);

	template <typename InputIterator>
	void addNumbers(InputIterator first, InputIterator last)
	{
		std::vector<int> pending;
		const std::size_t available = _maxSize - _numbers.size();
		for (; first != last; ++first)
		{
			if (pending.size() >= available)
				throw std::overflow_error("Span is full");
			pending.push_back(*first);
		}
		_numbers.insert(_numbers.end(), pending.begin(), pending.end());
	}

	int shortestSpan() const;
	int longestSpan() const;
};

#endif
