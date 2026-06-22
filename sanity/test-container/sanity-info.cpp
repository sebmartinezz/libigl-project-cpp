//genera ejecutable con informacion de sanidad en la build

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

int main() {
    std::cout << "----sanity check----\n\n";

    std::cout << "GLFW version:\n";
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    std::cout << "  " << major << "." << minor << "." << rev << "\n\n";

    std::cout << "OpenGL context (after init):\n";

    if (!glfwInit()) {
        std::cout << "  GLFW init FAILED\n";
        return -1;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(1, 1, "test", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "  GLAD init FAILED\n";
        return -1;
    }

    std::cout << "  Vendor  : " << glGetString(GL_VENDOR) << "\n";
    std::cout << "  Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "  Version : " << glGetString(GL_VERSION) << "\n\n";

    std::cout << "Eigen version:\n";
    std::cout << "  " << EIGEN_WORLD_VERSION << "."
              << EIGEN_MAJOR_VERSION << "."
              << EIGEN_MINOR_VERSION << "\n\n";

    std::cout << "GLAD loaded OK\n";
    std::cout << "GLFW working OK\n";
    std::cout << "Eigen compiling OK\n";

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "\n----end sanity :3----\n";
}