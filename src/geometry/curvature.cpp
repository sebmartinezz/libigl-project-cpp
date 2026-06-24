#include "geometry/curvature.h"
#include <igl/gaussian_curvature.h>
#include <iostream>

void GaussianCurvature(const Eigen::MatrixXd& V,
                              const Eigen::MatrixXi& F,
                              Eigen::VectorXf& K)
{
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