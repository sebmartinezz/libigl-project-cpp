#include "render/mesh.h"
#include <iostream>

void Mesh::upload()
{
    if (uploaded){
        return;
    }
    setup_gl();
    uploaded = true;
}

Mesh::~Mesh(){
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

void Mesh::setup_gl()
{
    std::cout << "setupgl called\n";
    std::vector<float> buffer;

    int N = positions.rows();
    buffer.reserve(N * 6);

    //interleaving positions and rgb
    for (int ii=0; ii<N; ii++)
    {
        // position
        buffer.push_back(positions(ii,0));
        buffer.push_back(positions(ii,1));
        buffer.push_back(positions(ii,2));

        // color
        buffer.push_back(colors(ii,0));
        buffer.push_back(colors(ii,1));
        buffer.push_back(colors(ii,2));
    }


    glGenVertexArrays(1, &VAO); //crea 1 vertex array y guarda el ID en la dir de VAO
    glGenBuffers(1, &VBO); //crea 1 buffer y guarda el ID en la direccion de memoria de VBO
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); //haz que este VAO sea el activo en opengl

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        buffer.size() * sizeof(float),
        buffer.data(),
        GL_STATIC_DRAW
    );


    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );


    // position
    glVertexAttribPointer(
        0, //atributo 0
        3, //tamaño del atributo
        GL_FLOAT, //tipo
        GL_FALSE, //normalized
        6 * sizeof(float), //tamaño de un vertice
        (void*)0 //0 de offset
    );
    glEnableVertexAttribArray(0); //activa el atributo 0


    // color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float)) //3 de offset
    );
    glEnableVertexAttribArray(1);

    //guardó todo eso en el VAO
    glBindVertexArray(0); //terminamos de configurarlo, lo apagamos
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
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //le indica a las operaciones de buffer vayan con este vbo

    int N = positions.rows(); //cantidad de vertices

    for (int jj=0; jj<N; jj++)
    {
        Eigen::Vector3f pos = positions.row(jj); //posicion del vertice jj

        glBufferSubData(
            GL_ARRAY_BUFFER,
            jj * 6 * sizeof(float), // offset dentro del interleaved buffer
            3 * sizeof(float),      // tamaño de info posición
            pos.data()
        );
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::update_colors()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    int N = colors.rows(); //numero de vertices

    for (int jj = 0; jj < N; jj++)
    {
        Eigen::Vector3f color = colors.row(jj); //rgb del vertice jj

        glBufferSubData(
            GL_ARRAY_BUFFER,
            jj * 6 * sizeof(float) + 3 * sizeof(float), // saltar xyz
            3 * sizeof(float), // tamaño de info rgb
            color.data()
        );
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}