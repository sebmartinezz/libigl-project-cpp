#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/glfw-window.h"

#include "render/shader.h"
#include "render/renderer.h"

#include <iostream>

int main()
{
    std::cout <<"\n----shader sanity----\n";

    Window win = window_create(800, 600, "shader sanity");
    if(!win.handle){
        std::cerr<<"window failed\n";
        return -1;
    }
    renderer_init();
    renderer_set_viewport(800, 600);


    //datos del triangulo que va a pintar el shader
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3*sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    //shader PRIMERO VERT LUEGO FRAG AAAAAAAAAAA
    Shader sanityshader (DATA_DIR"/vert-shader/shader-test.vert", DATA_DIR"/frag-shader/shader-test.frag");

    //loop
    while(!window_should_close(win)){
        window_events();
        renderer_clear(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );
        sanityshader.use();
        glBindVertexArray(VAO);
        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );
        window_swap_buffers(win);
    }

    //cleanup
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);

    window_destroy(win);

    std::cout<<"\n----end shader sanity----\n";

}