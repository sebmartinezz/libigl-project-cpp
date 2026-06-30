#include "core/glfw-window.h"

#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"
#include "render/camera.h"

#include "io/model-loader.h"
#include "geometry/curvature.h"

#include <iostream>

int main()
{
    std::cout << "\n---- curvature fertility example ----\n";

    Window window = window_create(800,600,"curvature fertility example");

    renderer_init();
    renderer_set_viewport(window.width,window.height);

    Shader shader(
        DATA_DIR"/vert-shader/curv-demo.vert",
        DATA_DIR"/frag-shader/curv-demo.frag"
    );

    std::cout<<"shader created";

    Camera camera;
    camera.set_distance(200.0f);
    {
        Mesh mesh = load_model(std::string(OFF_MODEL_DIR)+"/fertility.off");
        std::cout<<"mesh loaded\n";

        Eigen::VectorXf K;
        curvature(mesh,K);
        map_curvature_color(mesh,K);

        mesh.upload();
        std::cout<<"curvature applied\n";

        double lastX=0.0;
        double lastY =0.0;

        while(!window_should_close(window))
        {
            double xpos,ypos;

            window_get_mouse_position(window,xpos,ypos);

            double dx = xpos-lastX;
            double dy = ypos-lastY;

            lastX = xpos;
            lastY = ypos;

            if(window_mouse_pressed(window)){
                camera.orbit(dx,dy);
            }
            renderer_clear(0.08f, 0.08f, 0.08f, 1.0f);

            shader.use();

            shader.setMat4("model",glm::mat4(1.0f));
            shader.setMat4("view",camera.view_matrix());
            shader.setMat4("projection",camera.projection_matrix());

            mesh.draw();

            window_swap_buffers(window);
            window_events();
        }
    }

    window_destroy(window);

    std::cout<<"\n---- end curvature fertility example ----\n";

    return 0;
}