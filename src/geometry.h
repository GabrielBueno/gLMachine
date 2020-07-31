#ifndef _GL_MACHINE__GEOMETRY
#define _GL_MACHINE__GEOMETRY

namespace glMachine {
    typedef struct _position {
        double x;
        double y;
    } Position;

    typedef struct _line {
        double x1;
        double y1;

        double x2;
        double y2;
    } Line;
}

#endif