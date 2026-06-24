#pragma once
#include <vector>

void oscillate(
    std::vector<float>& positions,
    const std::vector<float>& original_positions,
    float t,
    float ampx,
    float ampy,
    float ampz
);
void compute_center(
    const std::vector<float>& positions,
    float& cx, float& cy, float& cz
);

void breathe_deform(
    std::vector<float>& positions,
    const std::vector<float>& original_positions,
    float t,
    float amplitude
);
