#include "core/glfw-window.h"

#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"

#include "io/model-loader.h"

#include <iostream>


int main()
{
    std::cout << "\n---- model loader sanity ----\n";

    Window window = window_create(800, 600,"model loader sanity");
    renderer_init();

    renderer_set_viewport(window.width, window.height);

    //shader
    Shader shader (DATA_DIR"/vert-shader/mesh-test.vert", DATA_DIR"/frag-shader/mesh-test.frag");
    std::cout << "shader ok\n";

    {    //LOAD MODEL
        Mesh mesh = ModelLoader::loadOFF(std::string(OFF_MODEL_DIR) + "/cow.off");
        mesh.upload();
        std::cout << "mesh loaded\n";

        //loop
        while(!window_should_close(window))
        {
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
    }//se ejecuta el destructor
    window_destroy(window);
    std::cout << "---- end model loader sanity ----\n";

    return 0;
}