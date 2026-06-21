#include <igl/readOFF.h>
#include <igl/opengl/glfw/Viewer.h>
#include <iostream>

int main() {

    Eigen::MatrixXd V; //vertices matrix (posiciones x, y, z)
    Eigen::MatrixXi F; //faces matrix (indices de los triangulos)

    // cargar mesh
    std::string path = std::string(MODEL_DIR) + "/bunny.off";
    if (!igl::readOFF(path, V, F)) {
        std::cerr << "error cargando malla " << path << std::endl;
        return -1;
    }

    std::cout << "se cargo la malla" << std::endl;
    std::cout << "vertices: " << V.rows() << " | caras: " << F.rows() << std::endl;

    //visor interactivo de libigl
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    
    viewer.launch();

    return 0;
}