#include "core/glfw-window.h"

#include <iostream>

Window window_create (int width, int height, const char* title){
    Window win;
    win.width=width;
    win.height=height;

    if(!glfwInit()){

        std::cerr<<"glfw init failed";
        return win;
    } //inicia glfw, el sistema de ventanas

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win.handle = glfwCreateWindow(width, height, title, NULL, NULL); //los null son fullscreen, sharing
    //ahora win.handle apunta a una ventana real del OS

    if(!win.handle){
        std::cerr << "window creation failed";
        glfwTerminate();
        return win;
    }

    glfwMakeContextCurrent(win.handle); //dice que win.handle apunta a la ventana que va a controlar a Opengl, es el contexto activo

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "glad init failed";
    }
    // glad llena los punteros de las funciones de opengl, glfwGetProcAddress busca las direcciones de funciones de opengl
    // glad apunta al driver, el driver le da los punteros, glad llena las funciones de opengl con ellos
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    return win;
}

int window_should_close (Window&win){
    return glfwWindowShouldClose(win.handle);
}

void window_events(){
    glfwPollEvents(); //le pide al OS que procese eventos
}

void window_swap_buffers(Window&win){
    glfwSwapBuffers(win.handle);
    //intercambia los buffers, opengl usa dos buffers:
    //back dibuja, front muestra, swap muestra en pantalla lo que estaba en back
}
void window_destroy(Window&win){
    glfwDestroyWindow(win.handle); //destruye la ventana
    glfwTerminate(); //apaga glfw
}
