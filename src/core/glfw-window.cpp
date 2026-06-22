#include "core/glfw-window.h"

#include <iostream>
#include <glad/glad.h>

Window window_create (int width, int height, const char* title){
    Window win;
    win.width=width;
    win.height=height;

    glfwInit(); //inicia glfw, el sistema de ventanas

    
    win.handle = glfwCreateWindow(width, height, title, NULL, NULL); //los null son fullscreen, sharing
    //ahora win.handle apunta a una ventana real del OS
    glfwMakeContextCurrent(win.handle); //dice que win.handle apunta a la ventana que va a controlar a Opengl, es el contexto activo

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // glad llena los punteros de las funciones de opengl, glfwGetProcAddress busca las direcciones de funciones de opengl
    // glad apunta al driver, el driver le da los punteros, glad llena las funciones de opengl con ellos

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
