#include "render/camera.h"

#include <glm/gtc/matrix_transform.hpp> //toco ponerlo en el container xd
#include<cmath>
#include <iostream>

Camera::Camera()
{
    target = glm::vec3(0,0,0); //orbitará alrededor del origen por defecto
    up = glm::vec3(0,1,0); //que direccion es arriba pa la cam

    //angulos de orbita
    yaw = 0.0f; //rot horizontal
    pitch = 0.0f; //rot vertical
    distance = 5.0f; //distancia al centro es por defecto 5.0f

    position = glm::vec3(0,0,distance);

    fov = 45.0f; //campo de vision literal el fov 45 grados
    aspect = 800.0f/600.0f; //aspect radio, debe coincidir con la ventana y con el render
    //planos de corte
    near_plane = 0.1f;
    far_plane = 100.0f;
}

glm::mat4 Camera::view_matrix() const
{
    //cam space
    return glm::lookAt(
        position,
        target,
        up
    );
    //lookat recibe eye, center, up
}

glm::mat4 Camera::projection_matrix() const //cómo proyecta en la ventana
{
    //clip space
    return glm::perspective(
        glm::radians(fov),
        aspect,
        near_plane,
        far_plane
    ); //recibe estos parametros del objeto
}
void Camera::set_distance(float d)
{
    distance = d;
    update_position();
}
void Camera::set_target(glm::vec3 t)
{
    target = t;
    update_position();
}
void Camera::update_position()
{
    position.x = target.x + distance * std::cos(pitch) * std::sin(yaw);
    position.y = target.y + distance * std::sin(pitch);
    position.z = target.z + distance * std::cos(pitch) * std::cos(yaw);
}
void Camera::orbit(float dx, float dy) //necesitamos el mov del mouse en core
{
    std::cout << "orbit: " << dx << " " << dy <<"\n"; //movimiento horizontal y vertical del mouse
    float sensitivity = 0.005f;

    //modificamos los angulos segun el movimiento del mouse
    yaw += dx * sensitivity;
    pitch -= dy * sensitivity;

    // evitar voltear la camara
    if(pitch> 1.5f){
        pitch = 1.5f;
    }
    if(pitch < -1.5f){
        pitch = -1.5f;
    }

    //esfericas a cartesianas
    update_position();
}