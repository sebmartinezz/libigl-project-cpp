#include "core/glfw-window.h"

#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"

#include <iostream>

int main()
{
    std::cout << "\n----mesh sanity----\n";

    Window window = window_create(800, 600, "mesh sanity");
    renderer_init();
    renderer_set_viewport(window.width, window.height);

    Shader shader(
        DATA_DIR"/vert-shader/mesh-test.vert",
        DATA_DIR"/frag-shader/mesh-test.frag"
    );

    shader.use();
    {
        //mesh, simple triangle
        Mesh mesh;

        mesh.positions.resize(3,3);
        mesh.positions <<
            -0.5f,-0.5f,0.0f,
             0.5f,-0.5f,0.0f,
             0.0f, 0.5f,0.0f;

        mesh.colors.resize(3,3);
        mesh.colors <<
            1.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,0.0f,1.0f;

        mesh.indices.resize(1,3);
        mesh.indices << 0,1,2;

        mesh.upload();
        std::cout << "mesh uploaded ok\n";

        while (!window_should_close(window))
        {
            mesh.update_positions();

            renderer_clear(0.1f,0.1f,0.1f,1.0f);

            shader.use();
            mesh.draw();

            window_swap_buffers(window);
            window_events();
        }
    }

    window_destroy(window);

    std::cout << "\n----end mesh sanity----\n";
    return 0;
}