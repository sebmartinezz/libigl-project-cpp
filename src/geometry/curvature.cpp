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

    float scale = K.cwiseAbs().mean()*3.0f + 1e-6f;

    for(int ii = 0; ii < N; ii++)
    {
        float t = std::tanh(K(ii)/scale);
        float u = (t + 1.0f)*0.5f;

        float r,g,b;

        if(u < 0.33f)
        {
            // morado a azul
            float a = u/0.33f;

            r = 0.45f*(1-a);
            g = 0.15f + 0.25f*a;
            b = 0.85f + 0.15f*a;
        }
        else if(u < 0.66f)
        {
            // azul a verde suave a amarillo claro
            float a = (u-0.33f)/0.33f;

            r = 0.2f + 0.75f*a;
            g = 0.55f + 0.35f*a;
            b = 1.0f - 0.55f*a;
        }
        else
        {
            // amarillo claro a rojo
            float a = (u-0.66f)/0.34f;

            r = 1.0f;
            g = 0.90f - 0.70f*a;
            b = 0.45f*(1-a);
        }

        mesh.colors(ii,0)=r;
        mesh.colors(ii,1)=g;
        mesh.colors(ii,2)=b;
    }
}