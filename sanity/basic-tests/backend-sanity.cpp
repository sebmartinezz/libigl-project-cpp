#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "\n----backend sanity----\n";

    if (!glfwInit()) {
        std::cout << "glfw init failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(1, 1, "backend sanity", nullptr, nullptr);

    if (!window) {
        std::cout << "Window creation FAILED\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "GLAD init FAILED\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    std::cout << "GLFW OK\n";
    std::cout << "GLAD OK\n";

    std::cout << "opengl version: "
              << glGetString(GL_VERSION) << "\n";
    std::cout << "renderer: "
              << glGetString(GL_RENDERER) << "\n";
    std::cout << "vendor: "
              << glGetString(GL_VENDOR) << "\n";

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "\n----end backend sanity----\n";
}