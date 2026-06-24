#include "core/glfw-window.h"
#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"
#include "geometry/deformation.h"

#include <iostream>


int main()
{
    std::cout << "\n---- deformation sanity ----\n";
    Window window = window_create(
        800,
        600,
        "deformation sanity"
    );
    renderer_init();
    renderer_set_viewport(window.width, window.height);

    Shader shader(
        DATA_DIR"/vert-shader/mesh-test.vert",
        DATA_DIR"/frag-shader/mesh-test.frag"
    );

    shader.use();
    std::cout << "shader created ok\n";
    {
        Mesh mesh;
        // triangulo simple pa probar

        mesh.positions = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
        };
        mesh.original_positions = mesh.positions;
        mesh.colors = {
            1.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,0.0f,1.0f
        };
        mesh.indices = {
            0,1,2
        };
        mesh.upload();

        while(!window_should_close(window)){
            float t = glfwGetTime();
            //oscillate(mesh.positions, mesh.original_positions, t, -0.1f, 0.15f, 0.95f); //testing these two
            breathe_deform(mesh.positions, mesh.original_positions, t, 4.0f);
            mesh.update_positions();
            renderer_clear(
                0.1f,
                0.1f,
                0.1f,
                1.0f
            );
            shader.use();
            mesh.draw();
            window_swap_buffers(window);
            window_events();
        }
    }//dest mesh
    window_destroy(window);
    std::cout<<"\n---- end deformation sanity ----\n";
    return 0;
}