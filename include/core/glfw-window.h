#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Window {
    GLFWwindow* handle; //handle será un puntero a GLFWwindow
    int width;
    int height;
}; //crea el tipo Window

Window window_create (int width, int height, const char* title); //puntero al primer char de title
int window_should_close (Window&win);
void window_events();
void window_swap_buffers(Window& win);
void window_destroy(Window&win);
