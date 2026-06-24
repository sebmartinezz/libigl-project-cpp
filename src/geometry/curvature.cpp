#include "geometry/curvature.h"
#include <igl/gaussian_curvature.h>
#include <igl/readOFF.h>
#include <igl/readOBJ.h>
#include <iostream>

void GaussianCurvature(const std::string& path,
                        Eigen::VectorXf& K)
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    igl::readOFF(path, V, F);
    igl::gaussian_curvature(V, F, K);
}
void setCurvatureColor(std::vector<float>& colors, const Eigen::VectorXf& K)
{   
    //me genera el vector colors para mesh a partir del vector K que genera igl
    int N = K.size();

    if ((int)colors.size() != N * 3)
    {
        std::cerr << "error: colors size mismatch\n";
        return;
    }

    float minK = K.minCoeff();
    float maxK = K.maxCoeff();
    float range = maxK - minK + 1e-6f;

    for (int ii = 0; ii < N; ii++)
    {
        float t = (K(ii) - minK) / range;

        colors[ii * 3 + 0] = t;
        colors[ii * 3 + 1] = 0.2f;
        colors[ii * 3 + 2] = 1.0f - t;
    }
}