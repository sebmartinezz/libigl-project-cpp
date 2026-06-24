#include "geometry/deformation.h"
#include <cmath>


void oscillate(
    std::vector<float>& positions,
    const std::vector<float>& original_positions,
    float t,
    float ampx,
    float ampy,
    float ampz
)
{
    for (size_t ii = 0; ii < positions.size(); ii += 3)
    {
        float x0 = original_positions[ii + 0];
        float y0 = original_positions[ii + 1];
        float z0 = original_positions[ii + 2];

        float phase = t;

        positions[ii + 0] = x0 + ampx * std::sin(phase);
        positions[ii + 1] = y0 + ampy * std::sin(phase);
        positions[ii + 2] = z0 + ampz * std::sin(phase);
    }
}

void compute_center(
    const std::vector<float>& positions,
    float& cx, float& cy, float& cz
)
{
    cx = cy = cz = 0.0f;

    size_t N = positions.size() / 3;

    for (size_t ii = 0; ii < N; ii++)
    {
        cx += positions[ii * 3 + 0];
        cy += positions[ii * 3 + 1];
        cz += positions[ii * 3 + 2];
    }

    cx /= N;
    cy /= N;
    cz /= N;
}

void breathe_deform(
    std::vector<float>& positions,
    const std::vector<float>& original_positions,
    float t,
    float amplitude
)
{
    float cx, cy, cz;
    compute_center(original_positions, cx, cy, cz);

    float base = std::sin(t);

    size_t N = positions.size() / 3;

    for (size_t jj = 0; jj < N; jj++)
    {
        float x0 = original_positions[jj * 3 + 0];
        float y0 = original_positions[jj * 3 + 1];
        float z0 = original_positions[jj * 3 + 2];

        float dx = x0 - cx;
        float dy = y0 - cy;
        float dz = z0 - cz;

        float r = std::sqrt(dx*dx + dy*dy + dz*dz);

        //atenuacion, mas lejos menos mov
        float w = 1.0f / (1.0f + 5.0f * r);

        float s = 1.0f + 0.5f * amplitude * (sin(t) + 1.0f) * w;

        positions[jj * 3 + 0] = cx + dx * s;
        positions[jj * 3 + 1] = cy + dy * s;
        positions[jj * 3 + 2] = cz + dz * s;
    }
}