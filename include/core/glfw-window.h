#pragma once
#include <string>
#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow* handle; //handle será un puntero a GLFWwindow
    int width;
    int height;
} Window; //crea el tipo Window

Window window_create (int width, int height, const char* title); //puntero al primer char de title
int window_should_close (Window&win);
void window_events();
void window_swap_buffers(Window& win);
void window_destroy(Window&win);
