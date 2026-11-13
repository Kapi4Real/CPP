#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>

template <typename T>
class Array
{
private:
	T* _data;
	unsigned int _size;

public:
	Array() : _data(NULL), _size(0) {}

	explicit Array(unsigned int n) : _data(NULL), _size(n)
	{
		if (n != 0)
			_data = new T[n]();
	}

	Array(const Array& other) : _data(NULL), _size(other._size)
	{
		if (_size != 0)
		{
			_data = new T[_size]();
			try
			{
				for (unsigned int i = 0; i < _size; ++i)
					_data[i] = other._data[i];
			}
			catch (...)
			{
				delete[] _data;
				throw;
			}
		}
	}

	~Array() { delete[] _data; }

	Array& operator=(const Array& other)
	{
		if (this != &other)
		{
			T* newData = NULL;
			if (other._size != 0)
			{
				newData = new T[other._size]();
				try
				{
					for (unsigned int i = 0; i < other._size; ++i)
						newData[i] = other._data[i];
				}
				catch (...)
				{
					delete[] newData;
					throw;
				}
			}
			delete[] _data;
			_data = newData;
			_size = other._size;
		}
		return *this;
	}

	T& operator[](unsigned int index)
	{
		if (index >= _size)
			throw std::out_of_range("Array index out of bounds");
		return _data[index];
	}

	const T& operator[](unsigned int index) const
	{
		if (index >= _size)
			throw std::out_of_range("Array index out of bounds");
		return _data[index];
	}

	unsigned int size() const { return _size; }
};

#endif
