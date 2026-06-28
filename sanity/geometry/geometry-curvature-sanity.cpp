#include "geometry/curvature.h"
#include "io/model-loader.h"

#include <iostream>

int main()
{
    std::cout << "\n---- curvature sanity ----\n";

    std::string path = std::string(OFF_MODEL_DIR) + "/cow.off";

    Mesh mesh = load_model(path);
    std::cout << "mesh loaded\n";

    Eigen::VectorXf K;
    curvature(mesh, K);
    std::cout << "curvature computed\n";

    map_curvature_color(mesh, K);
    std::cout << "color mapping done\n";


    for(int ii = 0; ii < 5; ii++)
    {
        std::cout
        << "K[" << ii << "] = "
        << K(ii)
        << " | RGB = ("
        << mesh.colors(ii,0) << ", "<< mesh.colors(ii,1) << ", "<< mesh.colors(ii,2)<< ")\n";
    }

    std::cout << "---- end curvature sanity ----\n";

    return 0;
}