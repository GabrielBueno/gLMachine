#ifndef _GL_MACHINE__LRENDERER
#define _GL_MACHINE__LRENDERER

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <string>
#include <cstdlib>

#include "geometry.h"

namespace glMachine {
    class LRenderer {
    public:
        LRenderer(std::vector<Line> lines);
        ~LRenderer();

        void render();

        static const size_t SCREEN_WIDTH  = 1024;
        static const size_t SCREEN_HEIGHT = 768; 

    private:
        void  _link_program();
        void  _load_vbo();
        void  _render();
        void  _main_loop();
        char* _read_file(const char* path);

        const size_t N_LINES;

        SDL_Window *_window;
        GLuint _path_vbo;
        GLuint _gl_program;
        GLint  _attr_position;

        std::vector<Line> _lines;
        GLuint *_vbos;
    };
}

#endif