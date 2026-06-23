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
        glDeleteBuffers(1, &EBO); // elimina las vainas para que no se queden en gpu
    }
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
    positions.reserve(V.rows() * 3); //V.rows en eigen significa cuántos vértices tiene
    colors.reserve(V.rows() * 3);

    for (int ii = 0; ii < V.rows(); ii++){ //recorro cada vértice
        positions.push_back(V(ii, 0));
        positions.push_back(V(ii, 1));
        positions.push_back(V(ii, 2));
        //aplana los datos, queda positions = x0, y0, z0, x1, y1, z1, ...

        // color por vértice, todos empiezan con color blanco
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        //queda colors = 1, 1, 1, ..
    }

    //importante, estructura de F
    // [0, 1, 2] ---- triangulo 0 tiene vertices 0, 1, 2
    // [2, 1, 3] ---- triangulo 1 tiene vertices 2, 1, 3
    // ...
    // no son posiciones sino índices de V

    // faces (triangles)
    indices.reserve(F.rows() * 3);

    for (int jj = 0; jj < F.rows(); jj++){ //recorro cada triángulo
        indices.push_back(F(jj, 0));
        indices.push_back(F(jj, 1));
        indices.push_back(F(jj, 2));
        //queda indices igual a F pero plano, ej indices = 0, 1, 2, 2, 1, 3
    }
}

//from curvature to color mapping
void Mesh::setCurvatureColor(const Eigen::VectorXf& K)
{
    //a cada vertice le corresponde un k con la curvatura, eso me lo da igl
    if (K.size() != positions.size() / 3){
        std::cerr << "error, curvature size mismatch\n";
        return;
    }

    float minK = K.minCoeff();
    float maxK = K.maxCoeff();

    for (int ii = 0; ii < K.size(); ii++)
    {
        float t = (K(ii) - minK) / (maxK - minK + 1e-6f); //t en rango normalizado, +1e-ef evita div por 0

        // colormap blue to red
        colors[ii * 3 + 0] = t;         // r
        colors[ii * 3 + 1] = 0.2f;       // g ta quieto
        colors[ii * 3 + 2] = 1.0f - t;   // b

        //colors es r, g, b, r, g, b, r, g, b, ..
    }
}

//upload from cpu to gpu UNA sola vezzzz
void Mesh::upload()
{
    if (uploaded)
        return;

    setupGL(); //crea VAO VBO EBO, sube datos a gpu, define atributos de posicion, color, etc
    //es la funcion de abajo
    uploaded = true; //es un bool que me dice si ya se subio la mesh pa no volver a subirla
}


//gpu setup VAO, VBO, EBO
void Mesh::setupGL()
{   //crea la rep de este mesh en gpu

    std::vector<float> buffer; //array plano final que la gpu leerá
    //buffer será [x, y, z, r, g, b,     x, y, z, r, g, b,     ...]

    buffer.reserve(positions.size() + colors.size());

    // interleaving position and color
    for (size_t ii = 0; ii < positions.size() / 3; ii++)
    {
        // position, obtengo x, y, z
        buffer.push_back(positions[ii * 3 + 0]);
        buffer.push_back(positions[ii * 3 + 1]);
        buffer.push_back(positions[ii * 3 + 2]);

        // color, obtengo r, g, b
        buffer.push_back(colors[ii * 3 + 0]);
        buffer.push_back(colors[ii * 3 + 1]);
        buffer.push_back(colors[ii * 3 + 2]);
    }

    //create gpu objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); //todo lo que configure ahora se guarda en este VAO

    //VBO vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //modificaré el VBO
    glBufferData(GL_ARRAY_BUFFER, //buffer de vertices
        buffer.size() * sizeof(float), //indica el tamaño que necesito en vram de gpu
        buffer.data(), //puntero crudo a memoria cpp
        GL_STATIC_DRAW); //no cambia
 

    //EBO inidices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    //queda VBO [x, y, z, r, g, b,       x, y, z, r, g, b,      ]
    //queda EBO [0, 1, 2, 2, 1, 3]


    //cómo leer el vbo??
    // ATTRIBUTE 0: position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //IMPORTANTE, configuré layout(location = 0) in vec3 aPos; para el vertshader
    //3 floats, no normalizar, cuanto avanza la gpu para el siguiente vértice, donde empieza position dentro del bloque
    glEnableVertexAttribArray(0); //activa atributo


    // ATTRIBUTE 1: color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //IMPORTANTE, configuré layout(location = 1) in vec3 aColor; para el vertshader
    //mismo significado de entradas pero esta vez no agarra x, y, z sino r, g, b
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); //cierra config de VAO
}

//draw call
void Mesh::draw() const
{
    glBindVertexArray(VAO); //para que lea el mesh
    glDrawElements(GL_TRIANGLES, //cada 3 indices un triangulo
                   indices.size(), //cuantos indices va a usar
                   GL_UNSIGNED_INT, //tipo de datos de EBO
                   0); //0 de offset
    glBindVertexArray(0); //desactiva el bao
}