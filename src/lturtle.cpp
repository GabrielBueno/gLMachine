#include "lturtle.h"

#include <cstdlib>
#include <cmath>

namespace glMachine {
    LTurtle::LTurtle(std::string const& lstring, Position initial_position) :
        _lstring(lstring),
        _angle_diff(30.0 * M_PI / 180.0),
        _walk_length_shrink_factor(1.2),
        _walk_length(10.0),
        _angle(90.0 * M_PI / 180.0),       
        _position(initial_position)
    {}

    LTurtle::~LTurtle() {}

    void LTurtle::execute() {
        for (size_t i = 0; i < _lstring.size(); i++) {
            const char ch = _lstring[i];

            switch (ch) {
                case 'F':
                    Line line;

                    line.x1 = _position.x;
                    line.y1 = _position.y;

                    _position.x += _walk_length * cos(_angle);
                    _position.y -= _walk_length * sin(_angle);

                    line.x2 = _position.x;
                    line.y2 = _position.y;

                    _line_stack.push(line);

                    break;

                case '[':
                    _push_state_stack();
                    _walk_length /= _walk_length_shrink_factor;

                    break;

                case ']':
                    _pop_state_stack();
                    _walk_length *= _walk_length_shrink_factor;

                    break;

                case '+':
                    _angle += _angle_diff;
                    break;

                case '-':
                    _angle -= _angle_diff;
                    break;
            }
        }
    }

    Line LTurtle::pop_line() {
        Line last_line = _line_stack.top();

        _line_stack.pop();
        return last_line;
    }

    Line LTurtle::peek_line() {
        return _line_stack.top();
    }

    bool LTurtle::has_line_on_stack() {
        return !_line_stack.empty();
    }

    void LTurtle::_push_state_stack() {
        _state_stack.push({ _position, _angle });
    }

    void LTurtle::_pop_state_stack() {
        LTurtleState prev_state = _state_stack.top();

        _position = prev_state.pos;
        _angle    = prev_state.angle;

        _state_stack.pop();
    }
}