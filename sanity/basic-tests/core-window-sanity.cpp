#include "core/glfw-window.h"
#include <iostream>

int main() {
    std::cout << "\n----window sanity----\n";

    Window win = window_create(800, 600, "window sanity");
    
    if (!win.handle) {
        std::cout << "Window creation FAILED\n";
        return -1;
    }

    std::cout<<"window created\n";
    
    while (!window_should_close(win)) {
        window_events();
        window_swap_buffers(win);
    }

    window_destroy(win);

    std::cout << "\n----end window sanity----\n";

}