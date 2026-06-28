#include "geometry/curvature.h"

#include <igl/gaussian_curvature.h>
#include <iostream>

#include <cassert>

void curvature(const Mesh&mesh, Eigen::VectorXf& K)
{
    Eigen::MatrixXd V = mesh.positions.cast<double>();
    Eigen::MatrixXi F = mesh.indices.cast<int>();

    igl::gaussian_curvature(V, F, K);
    assert(K.size() == mesh.positions.rows());
}
void map_curvature_color(Mesh& mesh, const Eigen::VectorXf& K)
{
    int N = K.size();

    if(mesh.colors.rows() != N || mesh.colors.cols() != 3)
    {
        std::cerr << "error: colors size mismatch\n";
        return;
    }

    float scale = K.cwiseAbs().mean() * 3.0f + 1e-6f;

    for(int ii = 0; ii < N; ii++)
    {
        float t = std::tanh(K(ii)/scale);

        if(t > 0)
        {
            // blanco a rojo
            mesh.colors(ii,0) = 1.0f;
            mesh.colors(ii,1) = 1.0f - t;
            mesh.colors(ii,2) = 1.0f - t;
        }
        else
        {
            // blanco a morado azulado
            float a = -t;
            mesh.colors(ii,0) = 1.0f - 0.6f*a;
            mesh.colors(ii,1) = 1.0f - 0.8f*a;
            mesh.colors(ii,2) = 1.0f;
        }
    }
}
