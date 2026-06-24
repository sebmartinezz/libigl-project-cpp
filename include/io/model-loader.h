//la idea es que podamos convertir archivos .off, .obj a eigen, para que luego mesh los suba
#pragma once

#include <string>
#include <Eigen/Dense>
#include "render/mesh.h"

Mesh loadOFF(const std::string& path); //me devuelve un objeto mesh
Mesh loadOBJ(const std::string& path);
void buildFromEigen(Mesh&mesh, const Eigen::MatrixXf& V, const Eigen::MatrixXi& F);