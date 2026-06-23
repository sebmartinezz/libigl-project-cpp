#include "render/mesh.h"
#include <iostream>

//constructor
Mesh::Mesh(const Eigen::MatrixXf& V, const Eigen::MatrixXi& F)
{
    buildFromEigen(V, F); //traduce de libigl a estructura cpu
}

//destructor
Mesh::~Mesh()
{
    if (uploaded)
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
}

// ----------------------------
// CONVERT IRONICALLY: Eigen → CPU buffers
// ----------------------------
void Mesh::buildFromEigen(const Eigen::MatrixXf& V,
                          const Eigen::MatrixXi& F)
{
    positions.clear();
    colors.clear();
    indices.clear();

    // ------------------------
    // vertices
    // ------------------------
    positions.reserve(V.rows() * 3);
    colors.reserve(V.rows() * 3);

    for (int i = 0; i < V.rows(); i++)
    {
        positions.push_back(V(i, 0));
        positions.push_back(V(i, 1));
        positions.push_back(V(i, 2));

        // default color (white)
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
    }

    // ------------------------
    // faces (triangles)
    // ------------------------
    indices.reserve(F.rows() * 3);

    for (int i = 0; i < F.rows(); i++)
    {
        indices.push_back(F(i, 0));
        indices.push_back(F(i, 1));
        indices.push_back(F(i, 2));
    }
}

// ----------------------------
// CURVATURE → COLOR MAPPING
// ----------------------------
void Mesh::setCurvatureColor(const Eigen::VectorXf& K)
{
    if (K.size() != positions.size() / 3)
    {
        std::cerr << "ERROR: curvature size mismatch\n";
        return;
    }

    float minK = K.minCoeff();
    float maxK = K.maxCoeff();

    for (int i = 0; i < K.size(); i++)
    {
        float t = (K(i) - minK) / (maxK - minK + 1e-6f);

        // simple colormap: blue → red
        colors[i * 3 + 0] = t;         // R
        colors[i * 3 + 1] = 0.2f;       // G fixed
        colors[i * 3 + 2] = 1.0f - t;   // B
    }
}

// ----------------------------
// UPLOAD CPU → GPU
// ----------------------------
void Mesh::upload()
{
    if (uploaded)
        return;

    setupGL();
    uploaded = true;
}

// ----------------------------
// GPU SETUP (VAO / VBO / EBO)
// ----------------------------
void Mesh::setupGL()
{
    std::vector<float> buffer;
    buffer.reserve(positions.size() + colors.size());

    // interleave: pos + color
    for (size_t i = 0; i < positions.size() / 3; i++)
    {
        // position
        buffer.push_back(positions[i * 3 + 0]);
        buffer.push_back(positions[i * 3 + 1]);
        buffer.push_back(positions[i * 3 + 2]);

        // color
        buffer.push_back(colors[i * 3 + 0]);
        buffer.push_back(colors[i * 3 + 1]);
        buffer.push_back(colors[i * 3 + 2]);
    }

    // ------------------------
    // CREATE GPU OBJECTS
    // ------------------------
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // ------------------------
    // VBO (vertex data)
    // ------------------------
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 buffer.size() * sizeof(float),
                 buffer.data(),
                 GL_STATIC_DRAW);

    // ------------------------
    // EBO (indices)
    // ------------------------
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int),
                 indices.data(),
                 GL_STATIC_DRAW);

    // ------------------------
    // ATTRIBUTE 0: position
    // ------------------------
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    // ------------------------
    // ATTRIBUTE 1: color
    // ------------------------
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

// ----------------------------
// DRAW CALL (GPU executes pipeline)
// ----------------------------
void Mesh::draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,
                   indices.size(),
                   GL_UNSIGNED_INT,
                   0);
    glBindVertexArray(0);
}