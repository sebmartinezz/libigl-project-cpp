#pragma once

#include<vector>
#include<glad/glad.h>

struct Mesh{ // objeto que representa malla
    
    void upload();
    void draw() const;
    void update_positions();

    ~Mesh();

public:

    std::vector<float> positions;
    std::vector<float> original_positions;
    std::vector<float> colors;
    std::vector<unsigned int> indices;

    // objetos de gpu
    unsigned int VAO = 0; //vertex array object
    unsigned int VBO = 0; //vertex buffer object
    unsigned int EBO = 0; //element buffer object

    bool uploaded = false;

private:
    void setupGL();
    void cleanup();
};