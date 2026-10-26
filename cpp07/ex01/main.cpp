#include <iostream>
#include <cstddef>

template <typename T>
void iter(T* array, size_t length, void (*func)(T const&))
{
    for (size_t i = 0; i < length; ++i)
        func(array[i]);
}

template <typename T>
void printValue(T const& value)
{
    std::cout << value << " ";
}

int main()
{
    int values[] = {1, 2, 3, 4};
    iter(values, 4, printValue);
    std::cout << std::endl;
    return 0;
}
