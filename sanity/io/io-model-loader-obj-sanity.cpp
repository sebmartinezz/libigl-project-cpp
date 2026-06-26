#include "core/glfw-window.h"

#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"
#include "render/camera.h"

#include "io/model-loader.h"

#include <iostream>

int main()
{
    std::cout << "\n---- model loader (obj) sanity ----\n";

    Window window = window_create(800, 600, "model loader (obj) sanity");
    renderer_init();

    renderer_set_viewport(window.width, window.height);

    Shader shader(
        DATA_DIR"/vert-shader/cam-test.vert",
        DATA_DIR"/frag-shader/cam-test.frag"
    );

    Camera camera; //constructor de Camera
    camera.set_distance(1.5f);
    {
        Mesh mesh = loadOBJ(std::string(OBJ_MODEL_DIR) + "/armadillo.obj");
        std::cout << "vertices: " << mesh.positions.size() << "\n";
        std::cout << "indices: " << mesh.indices.size() << "\n";
        mesh.upload();

        std::cout << "mesh loaded\n";

        double lastX = 0;
        double lastY = 0;
        while (!window_should_close(window))
        {
            double xpos;
            double ypos;

            window_get_mouse_position(window, xpos, ypos);

            double dx = xpos-lastX;
            double dy = ypos-lastY;

            lastX = xpos;
            lastY = ypos;

            if(window_mouse_pressed(window)){
                camera.orbit(dx, dy);
            }

            renderer_clear(0.1f, 0.1f, 0.1f, 1.0f);
            shader.use();

            glm::mat4 model = glm::mat4(1.0f);

             //.vert necesita esto
            shader.setMat4("model", model); //objeto-mundo
            shader.setMat4("view",camera.view_matrix());
            shader.setMat4("projection", camera.projection_matrix());
            mesh.draw();

            window_swap_buffers(window);
            window_events();
        }
    }//aca se ejecuta el destructor de mesh

    window_destroy(window);

    std::cout << "---- end model loader (obj) sanity ----\n";

    return 0;
}