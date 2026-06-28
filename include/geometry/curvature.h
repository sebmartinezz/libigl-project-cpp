#pragma once
#include "render/mesh.h"

#include <Eigen/Dense>

// calcula curvatura con libigl
void curvature(const Mesh&mesh, Eigen::VectorXf& K);

//convierte curvatura a color rgb
void map_curvature_color(Mesh&mesh, const Eigen::VectorXf& K);