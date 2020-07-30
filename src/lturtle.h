#ifndef _GL_MACHINE__LTURTLE
#define _GL_MACHINE__LTURTLE

#include <string>
#include <stack>

#include "position.h"

namespace glMachine {
    typedef struct _lturtle_state {
        Position pos;
        double angle;
    } LTurtleState;

    class LTurtle {
    public:
        LTurtle(std::string const& lstring);
        ~LTurtle();

        void execute();
        Position pop_position();
        Position peek_position();
        bool position_stack_empty();
    private:
        void _push_state_stack();
        void _pop_state_stack();
        void _push_pos_stack();

        std::string const&       _lstring;
        std::stack<Position>     _pos_stack;
        std::stack<LTurtleState> _state_stack;

        double   _walk_length;
        double   _angle;
        double   _angle_diff;
        double   _canvas_width;
        double   _canvas_height;
        Position _position;
    };
}

#endif