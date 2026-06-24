#pragma once

#include <string>

struct Shader {
    unsigned int ID; //id opengl for gpu

    //no es funcion sino constructor, construye shader
    Shader(const std::string& vertexPath, const std::string& fragmentPath); //vert and frag


    void use() const; //const - no modifica constructor

    void setInt(const char* name, int value) const;
    void setFloat(const char* name, float value) const;
    void setMat4(const char* name, const float* mat) const;

private:
    std::string loadFile(const std::string& path);
    unsigned int compile(unsigned int type, const std::string& src);
    void check(unsigned int obj, bool isProgram, const std::string& type);
};