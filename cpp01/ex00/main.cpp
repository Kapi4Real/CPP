#include "Zombie.hpp"

int main()
{
    Zombie* heapZombie = newZombie("HeapZombie");
    heapZombie->announce();
    delete heapZombie;
    
    randomChump("StackZombie");
    
    Zombie* kapi = newZombie("Kapi");
    kapi->announce();
    delete kapi;
    
    randomChump("Random");
    
    return 0;
}
