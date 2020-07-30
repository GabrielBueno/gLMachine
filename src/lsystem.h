#ifndef _GL_MACHINE__LSYSTEM
#define _GL_MACHINE__LSYSTEM

#include <string>
#include <cstdint>

namespace glMachine {
    class LSystem {
    public:
        LSystem(const char* axiom);
        ~LSystem();

        void iterate();
        std::string const& to_s();

    private:
        std::string get_production(char ch);

        std::string _lstring;
        uint32_t _n_iters;
    };
}

#endif