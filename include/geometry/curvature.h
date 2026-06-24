#pragma once
#include <Eigen/Dense>
#include <vector>

// calcula curvatura con libigl
void GaussianCurvature(const Eigen::MatrixXd& V,
                              const Eigen::MatrixXi& F,
                              Eigen::VectorXf& K);

//convierte curvatura a color rgb
void setCurvatureColor(std::vector<float>&colors, const Eigen::VectorXf& K);