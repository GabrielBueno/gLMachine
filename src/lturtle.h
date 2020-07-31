#ifndef _GL_MACHINE__LTURTLE
#define _GL_MACHINE__LTURTLE

#include <string>
#include <stack>

#include "geometry.h"

namespace glMachine {
    typedef struct _lturtle_state {
        Position pos;
        double angle;
    } LTurtleState;

    class LTurtle {
    public:
        LTurtle(std::string const& lstring, Position initial_position);
        ~LTurtle();

        void execute();
        Line pop_line();
        Line peek_line();
        bool has_line_on_stack();
    private:
        void _push_state_stack();
        void _pop_state_stack();

        std::string const&       _lstring;
        std::stack<Line>         _line_stack;
        std::stack<LTurtleState> _state_stack;
        
        const double _angle_diff;
        const double _walk_length_shrink_factor;

        double _walk_length;
        double _angle;
        Position _position;
    };
}

#endif