#include <iostream>

#include "lsystem.h"

int main(int argc, char **argv) {
    std::cout << "gl_Machine, starting..." << std::endl;

    glMachine::LSystem lsys("F");

    std::cout << lsys.to_s() << std::endl;

    for (int i = 0; i < 2; i++) {
        lsys.iterate();
        std::cout << lsys.to_s() << std::endl;
    }

    return 0;
}