#include "io/model-loader.h"

#include <igl/readOFF.h>
#include <igl/readOBJ.h>

#include <iostream>
#include <filesystem>

Mesh load_model(const std::string& path)
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    std::string ext = std::filesystem::path(path).extension().string();
    bool loaded = false;

    if (ext == ".off" || ext == ".OFF"){
        loaded = igl::readOFF(path, V, F);
    }
    else if (ext == ".obj" || ext == ".OBJ"){
        loaded = igl::readOBJ(path, V, F);
    }
    else{
        std::cerr << "unsupported mesh format: " << ext << "\n";
        return Mesh();
    }

    if (!loaded){
        std::cerr << "error loading model in this path: " << path << "\n";
        return Mesh();
    }

    Mesh mesh;

    mesh.positions = V.cast<float>(); //volverlos float
    mesh.indices = F.cast<unsigned int>(); //volverlos unsigned int
    mesh.original_positions = mesh.positions;

    mesh.colors.resize(V.rows(),3);
    mesh.colors.setOnes(); //por defecto colors va a ser todo 1, entonces el modelo va a ser blanco

    std::cout
        << "\nmodel loaded in this path: " << path << "\n"
        << "vertices: " << V.rows() << "\n"
        << "faces: " << F.rows() << "\n";

    return mesh;
}