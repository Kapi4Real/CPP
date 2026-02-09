#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	const int size = 10;
	Animal* animals[size];

	for (int i = 0; i < size / 2; ++i)
		animals[i] = new Dog();
	for (int i = size / 2; i < size; ++i)
		animals[i] = new Cat();

	std::cout << "\n--- Test Polymorphisme Tableau ---" << std::endl;
	for (int i = 0; i < size; ++i)
		animals[i]->makeSound();

	std::cout << "\n--- Test Deep Copy ---" << std::endl;
	Dog originalDog;
	originalDog.setIdea(0, "Wouf !");
	Dog copyDog = originalDog;
	originalDog.setIdea(0, "Je change l'idee du premier chien");
	std::cout << "Original: " << originalDog.getIdea(0) << std::endl;
	std::cout << "Copy: " << copyDog.getIdea(0) << std::endl;

	std::cout << "\n--- Test Polymorphisme Individuel ---" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	std::cout << "\n--- Test WrongAnimal ---" << std::endl;
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();
	std::cout << wrongCat->getType() << " " << std::endl;
	wrongCat->makeSound();
	wrongMeta->makeSound();

	delete meta;
	delete j;
	delete i;
	delete wrongMeta;
	delete wrongCat;
	for (int i = 0; i < size; ++i)
		delete animals[i];
	return 0;
}
