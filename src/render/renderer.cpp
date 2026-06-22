#include "render/renderer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

//asume que ya hay un contexto opengl activo

void renderer_init(){
    glEnable(GL_DEPTH_TEST); //estado global de opengl
    //no en orden de draw calls, sino segun la profundidad
}

void renderer_set_viewport (int width, int height){
    glViewport(0, 0, width, height);
}

void renderer_clear(float r, float g, float b, float a){
    glClearColor(r, g, b, a); //color con el que se va a borrar la pantalla
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //borra el color buffer y el depth buffer
}