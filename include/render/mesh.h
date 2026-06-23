#pragma once

#include<vector>
#include<glad/glad.h>
#include<Eigen/Dense>

struct Mesh{ //un objeto que representa una malla 3d lista para ser renderizada
    Mesh() = default;

    Mesh(const Eigen::MatrixXf& V, const Eigen::MatrixXi& F); //constructor con eigen
    ~Mesh(); //destructor


    void upload();   // sube datos a GPU
    void draw() const;

    //convierte curvatura a color rgb
    void setCurvatureColor(const Eigen::VectorXf& K);

private:
    //cpu data, antes de subirla a gpu
    std::vector<float> positions;   // vertices
    std::vector<float> colors;      //color por vértice
    std::vector<unsigned int> indices; // faces

    // objetos de gpu
    unsigned int VAO = 0; //como leer datos
    unsigned int VBO = 0; //vertices en gpu
    unsigned int EBO = 0; //triangulos por indices

    bool uploaded = false;

    //internal helper
    void buildFromEigen(const Eigen::MatrixXf& V, const Eigen::MatrixXi& F);

    void setupGL();
};