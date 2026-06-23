#include "render/shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vPath, const std::string& fPath) //los dos tipos de paths de shader
{
    std::string vSrc = loadFile(vPath);
    std::string fSrc = loadFile(fPath);
    //leer los archivos de texto nomas, los combierteh a string glsl y guarda en ram(lenguaje gpu)

    unsigned int v = compile(GL_VERTEX_SHADER, vSrc);
    unsigned int f = compile(GL_FRAGMENT_SHADER, fSrc);
    //opengl recibe el texto, lo compila a glsl, gpu ejecuta instrucciones ya compiladas y devuelve id de opengl

    ID = glCreateProgram();
    glAttachShader(ID, v);
    glAttachShader(ID, f);
    glLinkProgram(ID);
    //une el vertex y fragment en ID

    check(ID, true, "PROGRAM");
    std::cout<<"shader ok\n";

    glDeleteShader(v);
    glDeleteShader(f);
    //borra los shaders individuales, ya estan unidos
}

void Shader::use() const
{
    glUseProgram(ID); //le dice a gl que este es el shader activo ahora
}
void Shader::setInt(const char* name, int value) const
{
    //uniform es variable de gpu
    glUniform1i(glGetUniformLocation(ID, name), value);
    //busca la locacion de la variable "name" en el shader "ID"
    //pon el int "value" en esa location
}

void Shader::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::setMat4(const char* name, const float* mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, mat);
    //envia una matriz 4x4, re util para las animaciones y eso
}


//private functions
std::string Shader::loadFile(const std::string& path)
{
    std::ifstream file(path); //recibe la ubicacion del archivo
    std::stringstream ss; //stringstream es memoria dinamica en RAM para hacer texto

    if (!file.is_open())
    {
        std::cerr << "no se encontro el shaderfile" << path << std::endl;
        return ""; //retorna el shaderfile vacio
    }

    ss << file.rdbuf(); //rdbuf lee el buffer interno de file y lo direcciona a ss
    return ss.str(); //convierte ss a string y lo devuelve, eso leerá opengl

}

unsigned int Shader::compile(unsigned int type, const std::string& src) //compila el glsl para que la gpu lo pueda ejecutarrrrr
{
    //devuelve un id de opengl
    //type es el tipo de shader (vertex o fragment)
    //src es el codigo glsl como string

    unsigned int shader = glCreateShader(type); //reservar shader vacio del tipo x

    const char* csrc = src.c_str(); //convierte el string a c pointer, porque opengl lee eso
    glShaderSource(shader, 1, &csrc, nullptr); //envia el codigo a opengl
    //id, #strings, pointer to glsl, longitud automatica

    
    glCompileShader(shader);//gl compila el glsl

    //por si falla xdd
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        char log[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, log);

        std::cerr << "-----------------------------\n";
        std::cerr << "SHADER COMPILE ERROR: "
                  << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") //operador ternario, si es vertex imprime vertex y sino imprime fragment :)
                  << "\n";
        std::cerr << log << "\n";
        std::cerr << "-----------------------------\n";

        throw std::runtime_error("shader compilation failed");
    }

    return shader; //devuelvo el numero que apunta al shader en la gpu
}

void Shader::check(unsigned int obj, bool isProgram, const std::string& type)
{
    int success;
    char log[1024];

    if (!isProgram)
    {
        glGetShaderiv(obj, GL_COMPILE_STATUS, &success); //revisa los shaders vertex, fragment individuales
        if (!success)
        {
            glGetShaderInfoLog(obj, 1024, nullptr, log);
            std::cerr << type << " ERROR:\n" << log << std::endl;
        }
    }
    else
    {
        glGetProgramiv(obj, GL_LINK_STATUS, &success); //revisa los dos juntos
        if (!success)
        {
            glGetProgramInfoLog(obj, 1024, nullptr, log);
            std::cerr << "PROGRAM ERROR:\n" << log << std::endl;
        }
    }
}