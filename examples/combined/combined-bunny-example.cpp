#include "core/glfw-window.h"

#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"
#include "render/camera.h"

#include "io/model-loader.h"

#include "geometry/curvature.h"
#include "geometry/deformation.h"

#include <Eigen/Dense>
#include <iostream>
#include <cmath>


int main()
{
    std::cout << "\n---- deformation bend example ----\n";

    Window window = window_create(800,600,"deformation bend example");

    renderer_init();
    renderer_set_viewport(window.width,window.height);

    Shader shader(
        DATA_DIR "/vert-shader/curv-demo.vert",
        DATA_DIR "/frag-shader/curv-demo.frag"
    );

    Camera camera;
    camera.set_distance(0.25f);
    camera.set_target(glm::vec3(-0.02, 0.1, 0));

    {
        Mesh mesh = load_model(std::string(OFF_MODEL_DIR)+"/bunny.off");

        Eigen::VectorXf K;
        mesh.upload();

        double lastX = 0.0;
        double lastY = 0.0;

        while (!window_should_close(window))
        {
            double xpos, ypos;

            window_get_mouse_position(window, xpos, ypos);

            double dx = xpos - lastX;
            double dy = ypos - lastY;

            lastX = xpos;
            lastY = ypos;

            if(window_mouse_pressed(window))
            {
                camera.orbit(dx, dy);
            }

            float t = (float)glfwGetTime();
            float strength = 2.0f * std::sin(t);
            twist(mesh,strength, 0.1, M_PI*4.0);

            curvature (mesh, K);
            map_curvature_color(mesh, K);

            mesh.update_positions();
            mesh.update_colors();



            renderer_clear(0.08f, 0.08f, 0.08f, 1.0f);

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
    }

    window_destroy(window);

    std::cout << "\n---- end deformation bend example ----\n";

    return 0;
}