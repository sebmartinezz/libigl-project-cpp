#pragma once

struct Window;

void renderer_init();
void renderer_set_viewport(int width, int height);
void renderer_clear(float r, float g, float b, float a);