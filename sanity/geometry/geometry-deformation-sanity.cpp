#include "core/glfw-window.h"

#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"
#include "render/camera.h"

#include "geometry/deformation.h"

#include <iostream>

int main()
{
    std::cout << "\n---- deformation sanity ----\n";

    Window window = window_create(800,600,"deformation sanity");

    renderer_init();
    renderer_set_viewport(window.width,window.height);

    Shader shader(
        DATA_DIR"/vert-shader/cam-test.vert",
        DATA_DIR"/frag-shader/cam-test.frag"
    );

    Camera camera;
    camera.set_distance(5.0f);

    {
        Mesh mesh;

        mesh.positions.resize(8,3);
        mesh.positions <<
            -0.5f,-1.0f,0.0f,
             0.5f,-1.0f,0.0f,
             0.5f,-1.0f,1.0f,
            -0.5f,-1.0f,1.0f,

            -0.5f,1.0f,0.0f,
             0.5f,1.0f,0.0f,
             0.5f,1.0f,1.0f,
            -0.5f,1.0f,1.0f;

        mesh.original_positions = mesh.positions;

        mesh.colors.resize(8,3);
        mesh.colors <<
            1,0,0,
            0,1,0,
            0,0,1,
            1,1,0,

            1,0,1,
            0,1,1,
            1,1,1,
            0.5,0.5,0.5;

        mesh.indices.resize(12,3);
        mesh.indices <<
            0,1,2,
            2,3,0,

            4,5,6,
            6,7,4,

            0,4,5,
            5,1,0,

            1,5,6,
            6,2,1,

            2,6,7,
            7,3,2,

            3,7,4,
            4,0,3;

        mesh.upload();

        double lastX = 0.0;
        double lastY = 0.0;

        while(!window_should_close(window))
        {
            double xpos,ypos;
            window_get_mouse_position(window,xpos,ypos);

            double dx = xpos-lastX;
            double dy = ypos-lastY;

            lastX = xpos;
            lastY = ypos;

            if(window_mouse_pressed(window))
                camera.orbit(dx,dy);

            float t = (float)glfwGetTime();

            twist(mesh,t*0.8f, 0);

            mesh.update_positions();

            renderer_clear(0.1f,0.1f,0.1f,1.0f);

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

    std::cout << "\n---- end deformation sanity ----\n";

    return 0;
}