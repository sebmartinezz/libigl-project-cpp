#include <iostream>
#include <eigen3/Eigen/Dense>

int main() {
    // Create a 3x3 matrix
    Eigen::Matrix3d matrix;
    matrix << 1, 2, 3,
              4, 5, 6,
              7, 8, 9;
    
    std::cout << "Matrix:\n" << matrix << std::endl;
    
    // Calculate determinant
    double det = matrix.determinant();
    std::cout << "Determinant: " << det << std::endl;
    
    // Create a vector and multiply
    Eigen::Vector3d vector(1, 2, 3);
    Eigen::Vector3d result = matrix * vector;
    
    std::cout << "Matrix * Vector result:\n" << result << std::endl;
    
    return 0;
}