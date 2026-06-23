#include "core/glfw-window.h"
#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"

#include <iostream>

int main()
{
    std::cout << "\n----mesh sanity----\n";

    Window window = window_create(800, 600, "shader sanity");

    std::cout << "window created\n";

    renderer_init();

    renderer_set_viewport(window.width, window.height);

    //shader
    Shader shader (DATA_DIR"/vert-shader/mesh-test.vert", DATA_DIR"/frag-shader/mesh-test.frag");

    shader.use();

    std::cout << "shader created ok\n";

    //mesh, simple triangle
    {   
        //mesh, simple triangle
        Mesh mesh;

        // positions (triangulo)
        mesh.positions = {
            -0.5f, -0.5f, 0.0f, //primer vertice x0, y0, z0
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };

        // colors
        mesh.colors = {
            1.0f, 0.0f, 0.0f, // color del primer vertice es rojo
            0.0f, 1.0f, 0.0f, // verde
            0.0f, 0.0f, 1.0f  // azul
        };

        // indices
        mesh.indices = {
            0, 1, 2 //triangulo va con v0, v1, v2
        };
        mesh.upload();

        std::cout << "mesh uploaded ok\n";

        //loop
        while (!window_should_close(window))
        {
            renderer_clear(0.1f, 0.1f, 0.1f, 1.0f);
            shader.use();

            mesh.draw();

            window_swap_buffers(window);
            window_events();
        }
    }//aquí se ejecuta el destructor de mesh, ANTES DE BORRAR EL CONTEXTO DE OPENGL aaaaaaaaaaaaaaaaaaaaaaaaaaaa
    window_destroy(window);

    std::cout << "\n----end mesh sanity----\n";

    return 0;
}