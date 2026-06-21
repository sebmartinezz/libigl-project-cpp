#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // iniciar GLFW
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    // crear ventana con GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "triangulirijillo", NULL, NULL);
    if (!window) {
        std::cerr << "Error al crear la ventana" << std::endl;
        glfwTerminate();
        return -1;
    }

    //hacer que el contexto de la ventana sea el actual
    glfwMakeContextCurrent(window);

    //renderizado
    while (!glfwWindowShouldClose(window)) {
        //limpiar pantalla
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //triangulito xd
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); // Rojo
            glVertex2f(-0.5f, -0.5f);

            glColor3f(0.0f, 1.0f, 0.0f); // Verde
            glVertex2f(0.5f, -0.5f);

            glColor3f(0.0f, 0.0f, 1.0f); // Azul
            glVertex2f(0.0f, 0.5f);
        glEnd();

        //cambiar buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //limpiar y chao
    glfwTerminate();
    return 0;
}