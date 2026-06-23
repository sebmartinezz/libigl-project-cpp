//la idea es que podamos convertir archivos .off, .obj a eigen, para que luego mesh los suba
#pragma once

#include <string>
#include <Eigen/Dense>
#include "../render/mesh.h"

class ModelLoader
{
public:
    static Mesh loadOFF(const std::string& path);
    static Mesh loadOBJ(const std::string& path);
};