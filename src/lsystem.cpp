#include "lsystem.h"

#include <cstdlib>

namespace glMachine {
    LSystem::LSystem(const char* axiom) : 
        _lstring(axiom),
        _n_iters(0) 
    {}

    LSystem::~LSystem() {}

    void LSystem::iterate() {
        std::string result = "";

        for (size_t i = 0; i < _lstring.size(); i++) {
            result += get_production(_lstring[i]);
        }

        _lstring  = result;
        _n_iters += 1;
    }

    std::string const& LSystem::to_s() {
        return _lstring;
    }

    std::string LSystem::get_production(char ch) {
        switch (ch) {
            case 'F':
                return "F[+F[+F-F]][-F][[-F]+F]";

            case 'f':
                return "F";
        }

        return std::string(1, ch);
    }
}