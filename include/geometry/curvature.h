#pragma once
#include <Eigen/Dense>
#include <vector>

// calcula curvatura con libigl
void GaussianCurvature(const std::string& path,
                        Eigen::VectorXf& K);

//convierte curvatura a color rgb
void setCurvatureColor(std::vector<float>&colors, const Eigen::VectorXf& K);