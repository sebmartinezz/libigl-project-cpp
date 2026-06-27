#include "io/model-loader.h"

#include <igl/readOFF.h>
#include <igl/readOBJ.h>

#include <iostream>
#include <filesystem>

Mesh load_model (const std::string& path)
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    std::string ext=std::filesystem::path(path).extension().string();
    bool loaded = false;
    if (ext == ".off" || ext == ".OFF"){
        loaded = igl::readOFF(path, V, F);
    }
    else if (ext == ".obj" || ext == ".OBJ"){
        loaded = igl::readOBJ(path, V, F);
    }
    else{
        std::cerr << "unsupported mesh format: " << ext << std::endl;
        return Mesh();
    }
    if (!loaded)
    {
        std::cerr << "error loading model in this path: " << path << std::endl;
        return Mesh();
    }
    Mesh mesh;
    buildFromEigen(mesh, V.cast<float>(), F);

    std::cout << "model in this path loaded: " << path << "\n"
    << "vertices: " << V.rows() << "\n"
    << "faces: " << F.rows() << "\n";

    return mesh;
}

//eigen to cpu buffers
void buildFromEigen(Mesh&mesh, const Eigen::MatrixXf& V, const Eigen::MatrixXi& F)
{
    mesh.positions.clear();
    mesh.colors.clear();
    mesh.indices.clear();

    //importante, estructura de V es
    // [x0, y0, z0]
    // [x1, y1, z1]
    // [x2, y2, z2]
    // ...

    // vertices
    mesh.positions.reserve(V.rows() * 3);
    mesh.colors.reserve(V.rows() * 3);

    for (int ii = 0; ii < V.rows(); ii++){
        mesh.positions.push_back(V(ii, 0));
        mesh.positions.push_back(V(ii, 1));
        mesh.positions.push_back(V(ii, 2));

        mesh.colors.push_back(1.0f); //llenamos colors de blanco por defecto xd
        mesh.colors.push_back(1.0f);
        mesh.colors.push_back(1.0f);
    }

    // faces (triangles)
    mesh.indices.reserve(F.rows() * 3);

    for (int jj = 0; jj < F.rows(); jj++){
        mesh.indices.push_back(F(jj, 0));
        mesh.indices.push_back(F(jj, 1));
        mesh.indices.push_back(F(jj, 2));
    }
}