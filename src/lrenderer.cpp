#include "lrenderer.h"

#include <iostream>
#include <cstdlib>

namespace glMachine {
    LRenderer::LRenderer(std::vector<Line> lines) :
        N_LINES(lines.size()),
        _window(nullptr),
        _path_vbo(0),
        _gl_program(0),
        _lines(lines)
    {}

    LRenderer::~LRenderer() {
        glDeleteBuffers(N_LINES, _vbos);

        free(_vbos);
        _vbos = nullptr;

        glDeleteProgram(_gl_program);

        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    void LRenderer::render() {
        SDL_Init(SDL_INIT_VIDEO);

        _window = SDL_CreateWindow("glMachine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
        if (_window == nullptr) {
            std::cerr << "Error initializing window: " << SDL_GetError() << std::endl;
            exit(1);
        }

        SDL_GL_CreateContext(_window);

        GLenum glewStatus = glewInit();
        if (glewStatus != GLEW_OK) {
            std::cerr << "Error initializing glew: " << glewGetErrorString(glewStatus) << std::endl;
            exit(1);
        }

        glEnable(GL_PROGRAM_POINT_SIZE);

        _link_program();
        std::cout << "Linked GLSL program" << std::endl;

        _load_vbo();
        std::cout << "Loaded VBOs" << std::endl;

        _main_loop();
    }

    void LRenderer::_link_program() {
        _gl_program = glCreateProgram();

        GLuint v_shader = glCreateShader(GL_VERTEX_SHADER);
        GLuint f_shader = glCreateShader(GL_FRAGMENT_SHADER);

        GLint v_compile_ok = GL_FALSE;
        GLint f_compile_ok = GL_FALSE;
        GLint link_ok      = GL_FALSE;

        const char *v_src = _read_file("./shaders/shader.v.glsl");
        const char *f_src = _read_file("./shaders/shader.f.glsl");

        if (v_src == NULL) {
            fprintf(stderr, "Could not read vertex shader file\n");
            exit(1);
        }

        if (f_src == NULL) {
            fprintf(stderr, "Could not read fragment shader file\n");
            exit(1);
        }

        glShaderSource(v_shader, 1, &v_src, NULL);
        glShaderSource(f_shader, 1, &f_src, NULL);

        glCompileShader(v_shader);
        glCompileShader(f_shader);

        glGetShaderiv(v_shader, GL_COMPILE_STATUS, &v_compile_ok);
        glGetShaderiv(f_shader, GL_COMPILE_STATUS, &f_compile_ok);

        if (!v_compile_ok) {
            fprintf(stderr, "Could not compile vertex shader\n");
            exit(1);
        }

        if (!f_compile_ok) {
            fprintf(stderr, "Could not compile fragment shader\n");
            exit(1);
        }

        glAttachShader(_gl_program, v_shader);
        glAttachShader(_gl_program, f_shader);
        glLinkProgram(_gl_program);

        glGetProgramiv(_gl_program, GL_LINK_STATUS, &link_ok);

        if (!link_ok) {
            fprintf(stderr, "Could not link program\n");
            exit(1);
        }

        _attr_position = glGetAttribLocation(_gl_program, "position");

        if (_attr_position == -1) {
            fprintf(stderr, "Could not bind attribute position");
            exit(1);
        }

        free((void*)v_src);
        free((void*)f_src);

        v_src = NULL;
        f_src = NULL;
    }

    void LRenderer::_load_vbo() {
        _vbos = (GLuint*)malloc(sizeof(GLfloat) * N_LINES);
        glGenBuffers(N_LINES, _vbos);

        float _width_ratio  = 2.0f / SCREEN_WIDTH;
        float _height_ratio = 2.0f / SCREEN_HEIGHT;

        for (size_t i = 0; i < N_LINES; i++) {
            GLfloat data[] = {
                (GLfloat)_lines[i].x1 * _width_ratio  - 1.0f,
                (GLfloat)_lines[i].y1 * _height_ratio - 1.0f,

                (GLfloat)_lines[i].x2 * _width_ratio  - 1.0f,
                (GLfloat)_lines[i].y2 * _height_ratio - 1.0f
            };

            // std::cout << "(" << data[0] << ", " << data[1] << ") - ";
            // std::cout << "(" << data[2] << ", " << data[3] << ")" << std::endl;

            glBindBuffer(GL_ARRAY_BUFFER, _vbos[i]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        }

        std::cout << N_LINES << std::endl;
    }

    void LRenderer::_render() { 
        // glClearColor(0.84, 0.78, 0.66, 1.0);
        glClearColor(0.04, 0.01, 0.02, 1.0);
        // glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(_gl_program);

        for (size_t i = 0; i < N_LINES; i++) {
            glBindBuffer(GL_ARRAY_BUFFER, _vbos[i]);

            glEnableVertexAttribArray(_attr_position);
            glVertexAttribPointer(_attr_position, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glDrawArrays(GL_LINES, 0, 2);
        }

        SDL_GL_SwapWindow(_window);
    }

    void LRenderer::_main_loop() {
        bool running = true;
        SDL_Event e;

        while (running) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT)
                    running = false;
            }

            _render();
        }
    }

    char* LRenderer::_read_file(const char* path) {
        FILE *file   = NULL;
        char *buffer = NULL;
        size_t size  = 0;

        file = fopen(path, "r");

        if (file == NULL) {
            fprintf(stderr, "I couldn't open the file...\n");
            return NULL;
        }

        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);

        buffer = (char*)malloc(size * sizeof(char) + sizeof(char));

        fread(buffer, sizeof(char), size, file);
        fclose(file);
        
        buffer[size] = '\0';

        return buffer;
    }
}