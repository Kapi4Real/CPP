#include "MutantStack.hpp"
#include <iostream>
#include <stack>

int main()
{
	MutantStack<int> values;
	values.push(5);
	values.push(17);
	std::cout << "top: " << values.top() << std::endl;
	values.pop();
	std::cout << "size after pop: " << values.size() << std::endl;
	values.push(3);
	values.push(5);
	values.push(737);
	values.push(0);

	std::cout << "iteration:" << std::endl;
	for (MutantStack<int>::iterator it = values.begin(); it != values.end(); ++it)
		std::cout << *it << std::endl;

	const MutantStack<int>& constValues = values;
	std::cout << "const iteration:" << std::endl;
	for (MutantStack<int>::const_iterator it = constValues.begin(); it != constValues.end(); ++it)
		std::cout << *it << std::endl;

	std::stack<int> ordinary(values);
	std::cout << "copied into std::stack: " << ordinary.top() << std::endl;
	return 0;
}
