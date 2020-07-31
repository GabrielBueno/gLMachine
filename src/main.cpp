#include <iostream>
#include <vector>

#include "lsystem.h"
#include "lturtle.h"
#include "lrenderer.h"
#include "geometry.h"

#define ITERATIONS 6

int main(int argc, char **argv) {
    std::cout << "gl_Machine, starting..." << std::endl;

    glMachine::LSystem lsys("F");

    for (int i = 0; i < ITERATIONS; i++)
        lsys.iterate();

    glMachine::LTurtle lturtle(lsys.to_s(), { glMachine::LRenderer::SCREEN_WIDTH / 2, glMachine::LRenderer::SCREEN_HEIGHT - 30 });
    lturtle.execute();

    std::vector<glMachine::Line> lines;
    while (lturtle.has_line_on_stack()) 
        lines.push_back(lturtle.pop_line());
    
    glMachine::LRenderer renderer(lines);

    renderer.render();

    return 0;
}