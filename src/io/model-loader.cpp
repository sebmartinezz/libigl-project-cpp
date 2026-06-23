#include "io/model-loader.h"

#include <igl/readOFF.h>
#include <igl/readOBJ.h>
#include <igl/gaussian_curvature.h>
#include <iostream>

Mesh ModelLoader::loadOFF(const std::string& path)
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    if (!igl::readOFF(path, V, F)) //igl::es para usar libigl
    {
        std::cerr << "error loading off model: " << path << std::endl;
        return Mesh();
    }


    //curvatura
    Eigen::VectorXd K;
    igl::gaussian_curvature(V, F, K);

    Mesh mesh;
    mesh.buildFromEigen(V.cast<float>(), F);
    mesh.setCurvatureColor(K.cast<float>());

    return mesh;
}
Mesh ModelLoader::loadOBJ(const std::string& path)
{
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;

    if (!igl::readOBJ(path, V, F))
    {
        std::cerr << "error loading obj model: " << path << std::endl;
        return Mesh();
    }

    Mesh mesh;
    mesh.buildFromEigen(V.cast<float>(), F);
    mesh.upload();

    return mesh;
}