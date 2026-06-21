#include <igl/readOFF.h>
#include <igl/opengl/glfw/Viewer.h>
#include <iostream>

int main(int argc, char *argv[]) {
    
    Eigen::MatrixXd V_original;
    Eigen::MatrixXi F;

    std::string path = std::string(MODEL_DIR) + "/cow.off";

    std::cout << "cargando modelo" << std::endl;
    
    if (!igl::readOFF(path, V_original, F)) {
        std::cerr << "error al cargar modelo: " << path << std::endl;
        return 1;
    }

    igl::opengl::glfw::Viewer viewer;
    
    //initial rotation
    float angulo = 0.0f;

    // registrar callback para anim continua
    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer& v) -> bool {
        //incrementar angulo
        angulo += 0.02f; 

        //rot matrix eje y
        Eigen::Matrix3d rotacion;
        rotacion = Eigen::AngleAxisd(angulo, Eigen::Vector3d::UnitY());

        //rotar vertices
        Eigen::MatrixXd V_rotado = V_original * rotacion.transpose();

        //actualizar malla en visor
        v.data().set_mesh(V_rotado, F);

        //ret false para que libigl siga dibujando
        return false;
    };

    // cargar malla y activar animacion auto
    viewer.data().set_mesh(V_original, F);
    viewer.core().is_animating = true;

    std::cout << "going" << std::endl;
    viewer.launch();

    return 0;
}