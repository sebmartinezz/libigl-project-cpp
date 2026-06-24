#include "core/glfw-window.h"
#include "render/renderer.h"
#include "render/shader.h"
#include "render/mesh.h"
#include "io/model-loader.h"
#include "geometry/curvature.h"

#include <igl/readOFF.h>
#include <Eigen/Dense>
#include <iostream>
#include <cmath>

static void makeModel(float angle, float* M)
{
    float c = cos(angle);
    float s = sin(angle);

    M[0] = c;  M[1] = 0; M[2] = s;  M[3] = 0;
    M[4] = 0;  M[5] = 1; M[6] = 0;  M[7] = 0;
    M[8] = -s; M[9] = 0; M[10] = c; M[11] = 0;
    M[12] = 0; M[13] = 0; M[14] = 0; M[15] = 1;
}

static void makeView(float* V)
{
    for (int i = 0; i < 16; i++) V[i] = 0;
    V[0] = 1; V[5] = 1; V[10] = 1; V[15] = 1;
    V[12] = 0.0f; //izq, derecha
    V[13] = -0.1f; //arriba, abajo
    V[14] = -0.3f; //acercar, alejar
}

static void makeProjection(float* P, float aspect)
{
    float fov = 45.0f * 3.1415926f / 180.0f;
    float n = 0.1f;
    float f = 100.0f;
    float t = tan(fov / 2.0f);

    for (int i = 0; i < 16; i++) P[i] = 0;

    P[0] = 1.0f / (aspect * t);
    P[5] = 1.0f / t;
    P[10] = -(f + n) / (f - n);
    P[11] = -1.0f;
    P[14] = -(2.0f * f * n) / (f - n);
}

int main()
{
    std::cout << "\n---- bunny demo ----\n";

    Window window = window_create(800, 600, "bunny demo");

    renderer_init();
    renderer_set_viewport(window.width, window.height);

    Shader shader(
        DATA_DIR "/vert-shader/bunny-demo.vert",
        DATA_DIR "/frag-shader/bunny-demo.frag"
    );

    std::cout << "shader created\n";
    {
        Mesh mesh = loadOFF(std::string(OFF_MODEL_DIR) + "/bunny.off");

        std::cout << "mesh loaded\n";

        Eigen::MatrixXd V;
        Eigen::MatrixXi F;

        igl::readOFF(std::string(OFF_MODEL_DIR) + "/bunny.off", V, F);

        Eigen::VectorXf K;
        GaussianCurvature(V, F, K);
        setCurvatureColor(mesh.colors, K);
        mesh.upload(); //uploadeando la mesh luego de llenar colors con la info de geometry

        std::cout << "geometry applied\n";

        float Model[16], View[16], Projection[16];

        makeView(View);
        makeProjection(Projection, 800.0f / 600.0f);

        float angle = 0.0f;

        while (!window_should_close(window))
        {
            renderer_clear(0.1f, 0.2f, 0.4f, 1.0f);

            angle += 0.01f;
            makeModel(angle, Model);

            shader.use();

            shader.setMat4("Model", Model);
            shader.setMat4("View", View);
            shader.setMat4("Projection", Projection);

            mesh.draw();

            window_swap_buffers(window);
            window_events();
        }
    }//ejecuta destructor de mesh
    window_destroy(window);

    std::cout << "\n---- end bunny demo ----\n";

    return 0;
}