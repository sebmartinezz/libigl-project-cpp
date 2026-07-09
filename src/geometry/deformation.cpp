#include "geometry/deformation.h"
#include <cmath>

void twist(Mesh& mesh, float strength, float y0, float max_angle)
{
    int N = mesh.positions.rows(); //vertices

    for(int ii = 0; ii < N; ii++)
    {
        float x = mesh.original_positions(ii,0);
        float y = mesh.original_positions(ii,1);
        float z = mesh.original_positions(ii,2);

        float y_rel = y - y0;

        float envelope = 1.0f / (1.0f + y_rel*y_rel);
        float angle = max_angle * envelope * std::sin(strength * y_rel);

        float c = std::cos(angle);
        float s = std::sin(angle);

        mesh.positions(ii,0) = x*c - z*s;
        mesh.positions(ii,2) = x*s + z*c;
        mesh.positions(ii,1) = y;
    }
}
void bend(Mesh& mesh, float radius)
{
    int N = mesh.positions.rows();

    for(int ii = 0; ii < N; ii++)
    {
        float x = mesh.original_positions(ii,0);
        float y = mesh.original_positions(ii,1);
        float z = mesh.original_positions(ii,2);

        // Evita división por cero
        float R = std::max(radius, 0.001f);

        // Ángulo de curvatura
        float theta = x / R;

        mesh.positions(ii,0) = R * std::sin(theta);
        mesh.positions(ii,1) = y;
        mesh.positions(ii,2) = z + R * (1.0f - std::cos(theta));
    }
}
void ripple(Mesh& mesh, float amplitude, float frequency)
{
    int N = mesh.positions.rows();

    for(int ii = 0; ii < N; ii++)
    {
        float x = mesh.original_positions(ii,0);
        float y = mesh.original_positions(ii,1);
        float z = mesh.original_positions(ii,2);

        float r = std::sqrt(x*x + z*z);

        mesh.positions(ii,0) = x;
        mesh.positions(ii,2) = z;
        mesh.positions(ii,1) = y + amplitude * std::sin(frequency * r);
    }
}

void bulge(Mesh& mesh, float strength)
{
    int N = mesh.positions.rows();

    for(int ii = 0; ii < N; ii++)
    {
        float x = mesh.original_positions(ii,0);
        float y = mesh.original_positions(ii,1);
        float z = mesh.original_positions(ii,2);

        // Distancia al origen
        float r2 = x*x + y*y + z*z;

        // Inflado suave mediante una gaussiana
        float scale = 1.0f + strength * std::exp(-2.0f * r2);

        mesh.positions(ii,0) = x * scale;
        mesh.positions(ii,1) = y * scale;
        mesh.positions(ii,2) = z * scale;
    }
}
void taper(Mesh& mesh, float strength)
{
    int N = mesh.positions.rows();

    for(int ii = 0; ii < N; ii++)
    {
        float x = mesh.original_positions(ii,0);
        float y = mesh.original_positions(ii,1);
        float z = mesh.original_positions(ii,2);

        // Factor de escala según la altura
        float scale = 1.0f + strength * y;

        mesh.positions(ii,0) = x * scale;
        mesh.positions(ii,1) = y;
        mesh.positions(ii,2) = z * scale;
    }
}
