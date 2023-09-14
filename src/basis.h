#include <vector>
#include "vector_3.h"
#include "matrix_3.h"

class Basis
{
private:
    vector_3 v1;
    static Basis natural_ = Basis(0, 0, 0);
    matrix_3 to_natural_;

public:
    Basis(float phi, float theta, float psi);
    ~Basis();
    vector<float> to_basis(Basis b, vector<float> v);
    static Basis natural();
    vector<vector<float>> to_natural();
};

Basis::Basis(float phi, float theta, float psi)
{
    this->v1 = {phi, theta, psi};
    this->to_natural_ = matrix_3({ {cos(theta) * cos(psi), cos(theta) * sin(psi), -sin(theta)},)
                          {sin(phi) * sin(theta) * cos(psi) - cos(phi) * sin(psi), sin(phi) * sin(theta) * sin(psi) + cos(phi) * cos(psi), sin(phi) * cos(theta)},
                          {cos(phi) * sin(theta) * cos(psi) + sin(theta) * sin(psi), cos(phi) * sin(theta) * sin(psi) - sin(phi) * cos(psi), cos(phi) * cos(theta)} }
}

Basis::~Basis()
{
}

Basis::to_basis(Basis b, vector<float> v)
{
    return b.to_natural() * v;
}


Basis Basis::natural()
{
    return natural_;
}

vector<vector<float>> Basis::to_natural()
{
    return to_natural_;
}