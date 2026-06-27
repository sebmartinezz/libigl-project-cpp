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

    GaussianCurvature(
        path,
        K
    );

    std::cout << "curvature computed\n";

    if (K.size() != mesh.positions.size()/3)
    {
        std::cerr << "error: curvature size mismatch\n";
        return -1;
    }

    std::vector<float> colors(K.size()*3);//tiene que ser de ese tamaño para llenarlo
    setCurvatureColor(
        colors,
        K
    );

    std::cout << "color mapping done\n";


    for(int ii = 0; ii < 5; ii++)
    {
        std::cout
        << "K[" << ii << "] = "
        << K(ii)
        << " | RGB = ("
        << colors[ii*3+0] << ", "
        << colors[ii*3+1] << ", "
        << colors[ii*3+2]
        << ")\n";
    }


    std::cout << "---- end curvature sanity ----\n";

    return 0;
}