#include "geometry/curvature.h"
#include "io/model-loader.h"
#include "render/mesh.h"

#include <igl/readOFF.h>
#include <igl/gaussian_curvature.h>
#include <iostream>

int main()
{
    std::cout << "\n---- curvature sanity ----\n";

    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    if (!igl::readOFF(std::string(OFF_MODEL_DIR) + "/cow.off", V, F))
    {
        std::cerr << "error loading mesh\n";
        return -1;
    }

    std::cout << "mesh loaded\n";

    Eigen::VectorXf K;
    GaussianCurvature(V, F, K);

    std::cout << "curvature computed\n";

    if (K.size() != V.rows())
    {
        std::cerr << "error: curvature size mismatch\n";
        return -1;
    }

    std::vector<float> colors;
    colors.resize(V.rows() * 3);
    setCurvatureColor(colors, K); //ahora llené el colors de meshs

    std::cout << "color mapping done\n";

    for (int ii = 0; ii < 5; ii++)
    {
        std::cout << "K[" << ii << "] = " << K(ii)
                  << " | RGB = ("
                  << colors[ii * 3 + 0] << ", "
                  << colors[ii * 3 + 1] << ", "
                  << colors[ii * 3 + 2] << ")\n";
    }

    std::cout << "---- end curvature sanity ----\n";
    return 0;
}