#pragma once

#include<Eigen/Dense>
#include <vector> //para el buffer
#include<glad/glad.h>
#include <functional>

using Matrixui = Eigen::Matrix<unsigned int, Eigen::Dynamic, 3, Eigen::RowMajor>;
using Matrixf = Eigen::Matrix<float,Eigen::Dynamic, 3 ,Eigen::RowMajor>;

struct Mesh{ // objeto que representa malla
    
    void upload();
    void draw() const;

    void update_positions();
    void update_colors();

    Mesh()=default;
    ~Mesh();

public:

    Matrixf positions;
    Matrixf original_positions;
    Matrixf colors;
    Matrixui indices;

    // objetos de gpu
    unsigned int VAO = 0; //vertex array object
    unsigned int VBO = 0; //vertex buffer object
    unsigned int EBO = 0; //element buffer object

    bool uploaded = false;

private:
    void setup_gl();
    void cleanup();
};