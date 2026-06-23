#include "render/mesh.h"
#include <iostream>

//constructor
Mesh::Mesh(const Eigen::MatrixXf& V, const Eigen::MatrixXi& F)
{
    //inicializacion segura
    VAO = 0;
    VBO = 0;
    EBO = 0;
    uploaded = false;

    buildFromEigen(V, F); //traduce de libigl a estructura cpu
}

//destructor, usar ANTES de cerrar el conexto de opengl aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
//sino va a salir un seg fault
Mesh::~Mesh()
{
    // FIX IMPORTANTE: NO DEPENDER SOLO DE uploaded
    if (VAO == 0) {
        return;
    }
        std::cout << "deleting VAO " << VAO << std::endl;
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO); // elimina las vainas para que no se queden en gpu
}

//eigen to cpu buffers
void Mesh::buildFromEigen(const Eigen::MatrixXf& V, const Eigen::MatrixXi& F)
{
    positions.clear(); //son std::vector<float>
    colors.clear();
    indices.clear(); //es std::vector<int>

    //importante, estructura de V es
    // [x0, y0, z0]
    // [x1, y1, z1]
    // [x2, y2, z2]
    // ...

    // vertices
    positions.reserve(V.rows() * 3);
    colors.reserve(V.rows() * 3);

    for (int ii = 0; ii < V.rows(); ii++){
        positions.push_back(V(ii, 0));
        positions.push_back(V(ii, 1));
        positions.push_back(V(ii, 2));

        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
    }

    // faces (triangles)
    indices.reserve(F.rows() * 3);

    for (int jj = 0; jj < F.rows(); jj++){
        indices.push_back(F(jj, 0));
        indices.push_back(F(jj, 1));
        indices.push_back(F(jj, 2));
    }
}

//from curvature to color mapping
void Mesh::setCurvatureColor(const Eigen::VectorXf& K)
{
    if (K.size() != positions.size() / 3){
        std::cerr << "error, curvature size mismatch\n";
        return;
    }

    float minK = K.minCoeff();
    float maxK = K.maxCoeff();

    for (int ii = 0; ii < K.size(); ii++)
    {
        float t = (K(ii) - minK) / (maxK - minK + 1e-6f);

        colors[ii * 3 + 0] = t;
        colors[ii * 3 + 1] = 0.2f;
        colors[ii * 3 + 2] = 1.0f - t;
    }
}

//upload from cpu to gpu UNA sola vezzzz
void Mesh::upload()
{
    if (uploaded)
        return;

    setupGL(); //crea VAO VBO EBO, sube datos a gpu, define atributos de posicion, color, etc

    uploaded = true;
}

//gpu setup VAO, VBO, EBO
void Mesh::setupGL()
{
    std::cout << "setupGL called\n";

    std::vector<float> buffer;
    buffer.reserve(positions.size() + colors.size());

    // interleaving position and color
    for (size_t ii = 0; ii < positions.size() / 3; ii++)
    {
        buffer.push_back(positions[ii * 3 + 0]);
        buffer.push_back(positions[ii * 3 + 1]);
        buffer.push_back(positions[ii * 3 + 2]);

        buffer.push_back(colors[ii * 3 + 0]);
        buffer.push_back(colors[ii * 3 + 1]);
        buffer.push_back(colors[ii * 3 + 2]);
    }

    //create gpu objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    //VBO vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        buffer.size() * sizeof(float),
        buffer.data(),
        GL_STATIC_DRAW);

    //EBO indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    // ATTRIBUTE 0: position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ATTRIBUTE 1: color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

//draw call
void Mesh::draw() const
{
    if (!uploaded)
    {
        std::cerr << "error, mesh not uploaded\n";
        return;
    }

    glBindVertexArray(VAO);

    glDrawElements(
        GL_TRIANGLES,
        (GLsizei)indices.size(), // FIX IMPORTANTE: CAST EXPLÍCITO
        GL_UNSIGNED_INT,
        0
    );

    glBindVertexArray(0);
}

Mesh::Mesh(Mesh&& other) noexcept
{
    VAO = other.VAO;
    VBO = other.VBO;
    EBO = other.EBO;
    uploaded = other.uploaded;

    positions = std::move(other.positions);
    colors = std::move(other.colors);
    indices = std::move(other.indices);

    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
    other.uploaded = false;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other)
    {
        // cleanup actual
        if (VAO != 0)
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }

        VAO = other.VAO;
        VBO = other.VBO;
        EBO = other.EBO;
        uploaded = other.uploaded;

        positions = std::move(other.positions);
        colors = std::move(other.colors);
        indices = std::move(other.indices);

        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
        other.uploaded = false;
    }

    return *this;
}