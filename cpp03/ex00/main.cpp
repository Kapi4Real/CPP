#include "ClapTrap.hpp"
#include <iostream>

int main()
{
    ClapTrap bot1("Alpha");
    ClapTrap bot2("Beta");

    bot1.attack("Beta");
    bot2.takeDamage(5);
    bot2.beRepaired(3);

    bot1.attack("Gamma");
    bot1.takeDamage(15);
    bot1.beRepaired(5);

    for (int i = 0; i < 11; ++i)
        bot2.attack("Alpha");

    bot2.beRepaired(2);

    return 0;
}
