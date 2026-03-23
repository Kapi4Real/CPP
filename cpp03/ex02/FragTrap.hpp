#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
public:
	FragTrap();
	virtual ~FragTrap();
	FragTrap(const FragTrap &other);
	FragTrap(const std::string &name);
	FragTrap &operator=(const FragTrap &other);
	void highFivesGuys(void);

};

#endif

