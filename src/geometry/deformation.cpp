#include "geometry/deformation.h"
#include <cmath>

void twist (std::vector<float>&positions,
            const std::vector<float>&original_positions,
            float strength
            )
{
    size_t N = positions.size() / 3;


    for(size_t i = 0; i < N; i++)
    {
        float x = original_positions[i*3 + 0];
        float y = original_positions[i*3 + 1];
        float z = original_positions[i*3 + 2];


        float max_angle = M_PI * 0.5f;
        float envelope = 1.0f / (1.0f + y*y); // o gaussiana
        float angle = max_angle * envelope * std::sin(strength * y);

        float c = std::cos(angle);
        float s = std::sin(angle);


        positions[i*3 + 0] = x*c - z*s;
        positions[i*3 + 2] = x*s + z*c;

        // y queda igual
        positions[i*3 + 1] = y;
    }
}