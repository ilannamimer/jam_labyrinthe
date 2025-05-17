#include <iostream>
#include "./labyrinthe.hpp"

int main(int argc, char **argv)
{
    labyrinthe lab;

    if (argc == 2)
        lab.create_lab(argv[1]);
    else
        lab.create_lab();
    while (lab.display()){
        lab.take_commande();
    }
    return 0;
}
