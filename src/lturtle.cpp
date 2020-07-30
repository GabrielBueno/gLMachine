#include "lturtle.h"

#include <cstdlib>
#include <cmath>

namespace glMachine {
    LTurtle::LTurtle(std::string const& lstring) :
        _lstring(lstring),
        _walk_length(5.0),
        _angle(90.0 * 180.0 / M_PI),
        _angle_diff(30.0 * 180.0 / M_PI),
        _canvas_width(500.0),
        _canvas_height(300.0),
        _position({ _canvas_width / 2, _canvas_height - 30 })
    {
        _push_pos_stack();
    }

    LTurtle::~LTurtle() {}

    void LTurtle::execute() {
        for (size_t i = 0; i < _lstring.size(); i++) {
            const char ch = _lstring[i];

            switch (ch) {
                case 'F':
                    _position.x += _walk_length * sin(_angle);
                    _position.y += _walk_length * cos(_angle);

                    _push_pos_stack();

                    break;

                case '[':
                    _push_state_stack();
                    break;

                case ']':
                    _pop_state_stack();
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

    Position LTurtle::pop_position() {
        Position last_pos = _pos_stack.top();

        _pos_stack.pop();
        return last_pos;
    }

    Position LTurtle::peek_position() {
        return _pos_stack.top();
    }

    bool LTurtle::position_stack_empty() {
        return _pos_stack.empty();
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

    void LTurtle::_push_pos_stack() {
        _pos_stack.push(_position);
    }
}