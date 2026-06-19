#include <GLFW/glfw3.h>
#include <iostream>

struct EstadoRender {
    float rotacion = 0.0f;
    float velocidadRotacion = 0.5f;
};

void dibujarCubo(const EstadoRender&estado) {
    glBegin(GL_QUADS);
        //cara de adelante- roja
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-0.3f, -0.3f,  0.3f);
        glVertex3f( 0.3f, -0.3f,  0.3f);
        glVertex3f( 0.3f,  0.3f,  0.3f);
        glVertex3f(-0.3f,  0.3f,  0.3f);

        //cara de atras - verde
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.3f, -0.3f, -0.3f);
        glVertex3f(-0.3f,  0.3f, -0.3f);
        glVertex3f( 0.3f,  0.3f, -0.3f);
        glVertex3f( 0.3f, -0.3f, -0.3f);

        //cara superior - azul
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.3f,  0.3f, -0.3f);
        glVertex3f(-0.3f,  0.3f,  0.3f);
        glVertex3f( 0.3f,  0.3f,  0.3f);
        glVertex3f( 0.3f,  0.3f, -0.3f);

        // cara inf - amarillo
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(-0.3f, -0.3f, -0.3f);
        glVertex3f( 0.3f, -0.3f, -0.3f);
        glVertex3f( 0.3f, -0.3f,  0.3f);
        glVertex3f(-0.3f, -0.3f,  0.3f);

        //cara derecha - cian
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f( 0.3f, -0.3f, -0.3f);
        glVertex3f( 0.3f,  0.3f, -0.3f);
        glVertex3f( 0.3f,  0.3f,  0.3f);
        glVertex3f( 0.3f, -0.3f,  0.3f);

        //cara izquierda - mgenta
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(-0.3f, -0.3f, -0.3f);
        glVertex3f(-0.3f, -0.3f,  0.3f);
        glVertex3f(-0.3f,  0.3f,  0.3f);
        glVertex3f(-0.3f,  0.3f, -0.3f);
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cubo 3D sin Variables Globales", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);

    EstadoRender miCuboEstado;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // Usamos los datos encapsulados localmente
        glRotatef(miCuboEstado.rotacion, 1.0f, 1.0f, 0.5f);

        dibujarCubo(miCuboEstado);

        // Modificación controlada dentro del ámbito del bucle principal
        miCuboEstado.rotacion += miCuboEstado.velocidadRotacion;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}