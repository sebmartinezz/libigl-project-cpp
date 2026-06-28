#include "geometry/deformation.h"
#include <cmath>

void twist(Mesh& mesh, float strength, float y0)
{
    int N = mesh.positions.rows(); //vertices

    for(int ii = 0; ii < N; ii++)
    {
        float x = mesh.original_positions(ii,0);
        float y = mesh.original_positions(ii,1);
        float z = mesh.original_positions(ii,2);

        float y_rel = y - y0;

        float max_angle = M_PI * 0.5f;
        float envelope = 1.0f / (1.0f + y_rel*y_rel);
        float angle = max_angle * envelope * std::sin(strength * y_rel);

        float c = std::cos(angle);
        float s = std::sin(angle);

        mesh.positions(ii,0) = x*c - z*s;
        mesh.positions(ii,2) = x*s + z*c;
        mesh.positions(ii,1) = y;
    }
}
