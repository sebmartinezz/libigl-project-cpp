#include "render/mesh.h"
#include <iostream>

void Mesh::upload()
{
    if (uploaded){
        return;
    }
    setupGL();
    uploaded = true;
}

Mesh::~Mesh()
{
    cleanup();
}

void Mesh::cleanup()
{
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);

    VAO = VBO = EBO = 0;
    uploaded = false;
}

void Mesh::setupGL()
{
    std::cout << "setupGL called\n";

    std::vector<float> buffer;
    int N = (int)positions.size() / 3;

    buffer.reserve(N * 6);

    //interleaving positions and rgb
    for (int ii = 0; ii < N; ii++)
    {
        buffer.push_back(positions[ii * 3 + 0]);
        buffer.push_back(positions[ii * 3 + 1]);
        buffer.push_back(positions[ii * 3 + 2]);

        buffer.push_back(colors[ii * 3 + 0]);
        buffer.push_back(colors[ii * 3 + 1]);
        buffer.push_back(colors[ii * 3 + 2]);
    }

    //buffer sera el que lee gpu
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        buffer.size() * sizeof(float),
        buffer.data(),
        GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    // attribute 0: position
    glVertexAttribPointer(
        0, //atributo 0
        3, //tamaño de la vaina
        GL_FLOAT, //son float
        GL_FALSE,
        6 * sizeof(float), //tamaño total de un vertice
        (void*)0 //0 de offset
    );
    glEnableVertexAttribArray(0);

    // attribute 1: color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::draw() const
{
    if (!uploaded)
    {
        std::cerr << "error: mesh not uploaded\n";
        return;
    }

    glBindVertexArray(VAO);

    glDrawElements(
        GL_TRIANGLES,
        (GLsizei)indices.size(),
        GL_UNSIGNED_INT,
        0
    );

    glBindVertexArray(0);
}
void Mesh::update_positions()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    int N = positions.size() / 3;

    for (int i = 0; i < N; i++)
    {
        float pos[3] = {
            positions[i * 3 + 0],
            positions[i * 3 + 1],
            positions[i * 3 + 2]
        };

        glBufferSubData(
            GL_ARRAY_BUFFER,
            i * 6 * sizeof(float),   // offset dentro del interleaved buffer
            3 * sizeof(float),       // SOLO posiciones
            pos
        );
    }
}