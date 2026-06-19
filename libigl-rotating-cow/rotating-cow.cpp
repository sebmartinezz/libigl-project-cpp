#include <igl/readOFF.h>
#include <igl/opengl/glfw/Viewer.h>
#include <iostream>

int main(int argc, char *argv[]) {
    
    Eigen::MatrixXd V_original;
    Eigen::MatrixXi F;

    std::cout << "cargando modelo" << std::endl;
    if (!igl::readOFF("cow.off", V_original, F)) {
        std::cerr << "error al cargar modelo" << std::endl;
        return 1;
    }

    igl::opengl::glfw::Viewer viewer;
    
    // Ángulo de rotación inicial
    float angulo = 0.0f;

    // Registramos el callback para la animación continua
    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer& v) -> bool {
        // Incrementar el ángulo en cada fotograma
        angulo += 0.02f; 

        // Crear una matriz de rotación en el eje Y usando Eigen
        Eigen::Matrix3d rotacion;
        rotacion = Eigen::AngleAxisd(angulo, Eigen::Vector3d::UnitY());

        // Multiplicar los vértices originales por la matriz de rotación
        // V_rotado = V_original * R^T (por la disposición por filas de Eigen)
        Eigen::MatrixXd V_rotado = V_original * rotacion.transpose();

        // Actualizar la malla en el visor en tiempo real
        v.data().set_mesh(V_rotado, F);

        // Retornar false para decirle a libigl que siga redibujando continuamente
        return false;
    };

    // Cargar la malla inicial y activar la animación automática
    viewer.data().set_mesh(V_original, F);
    viewer.core().is_animating = true; // ¡Esto fuerza al visor a refrescarse sin parar!

    std::cout << "going" << std::endl;
    viewer.launch();

    return 0;
}