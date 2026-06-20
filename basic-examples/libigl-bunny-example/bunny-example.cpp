#include <igl/readOFF.h>
#include <igl/opengl/glfw/Viewer.h>
#include <iostream>

int main() {

    Eigen::MatrixXd V; //vertices matrix (posiciones x, y, z)
    Eigen::MatrixXi F; //faces matrix (indices de los triangulos)

    // cargar mesh
    std::string ruta = "bunny.off";
    if (!igl::readOFF(ruta, V, F)) {
        std::cerr << "Error: No se pudo encontrar o leer el archivo " << ruta << std::endl;
        return -1;
    }

    std::cout << "Malla cargada con exito." << std::endl;
    std::cout << "Vertices: " << V.rows() << " | Caras: " << F.rows() << std::endl;

    //visor interactivo de libigl
    igl::opengl::glfw::Viewer viewer;
    viewer.data().set_mesh(V, F);
    
    viewer.launch();

    return 0;
}