//la idea es que podamos convertir archivos .off, .obj a eigen, para que luego mesh los suba
#pragma once

#include <string>
#include <Eigen/Dense>
#include "render/mesh.h"

Mesh load_model(const std::string& path); //me devuelve un objeto mesh
void buildFromEigen(Mesh&mesh, const Eigen::MatrixXf& V, const Eigen::MatrixXi& F);