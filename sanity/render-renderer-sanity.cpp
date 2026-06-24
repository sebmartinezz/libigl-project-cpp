#include "core/glfw-window.h"
#include "render/renderer.h"

#include <iostream>

int main(){

    std::cout << "\n----renderer sanity----\n";
    Window win = window_create(800, 600, "renderer sanity");

    if (!win.handle){

        std::cout << "window creation FAILED\n";
        return -1;
    }
    std::cout << "window created\n";

    renderer_init();

    std::cout << "renderer initialized\n";

    renderer_set_viewport(800,600);

    std::cout << "viewport OK\n";


    while(!window_should_close(win)){

        window_events();

        renderer_clear(//la f para decirle que es un float
            1.0f, // rojo
            0.4f, // verde
            0.5f, // azul
            1.0f
        );

        window_swap_buffers(win);
    }


    window_destroy(win);

    std::cout << "\n----end renderer sanity----\n";
}