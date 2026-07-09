#pragma once
#include "render/mesh.h"
#include <vector>

void twist (Mesh&mesh, float strength, float y0, float max_angle);
void bend(Mesh& mesh, float radius);
void ripple(Mesh& mesh, float amplitude, float frequency);
void bulge(Mesh& mesh, float strength);
