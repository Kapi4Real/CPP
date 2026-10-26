#include "Data.hpp"
#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data original;
	original.value = 42;
	original.label = "cpp06";
	uintptr_t raw = Serializer::serialize(&original);
	Data* restored = Serializer::deserialize(raw);
	std::cout << "same address: " << (restored == &original) << std::endl;
	if (restored)
		std::cout << restored->value << " " << restored->label << std::endl;
	if (restored == &original)
		return 0;
	return 1;
}
