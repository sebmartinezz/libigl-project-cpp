#pragma once

#include <glm/glm.hpp>


struct Camera{
    //estado
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    // perspectiva
    float fov;
    float aspect;
    float near_plane;
    float far_plane;

    // constructor
    Camera();

    // matrices que usa el shader
    glm::mat4 view_matrix() const;
    glm::mat4 projection_matrix() const;

    //mov con click
    float yaw;
    float pitch;
    float distance;
    
    void set_target(glm::vec3 t);
    void set_distance(float d); //setear la distancia al centro
    void update_position();
    void orbit(float dx, float dy); //que orbite con el mouseee
};