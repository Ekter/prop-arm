#include <vector>
#include "vector_3.h"

class matrix_3
{
private:
    vector<vector<float>> m_;
    static i = matrix_3({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
public:
    matrix_3(vector<vector<float>> m) { this->m_ = m;}
    matrix_3(vector_3 v1, vector_3 v2, vector_3 v3) { this->m_ = {{v1.x(), v1.y(), v1.z()}, {v2.x(), v2.y(), v2.z()}, {v3.x(), v3.y(), v3.z()}}; }
    matrix_3(vector<float> v1, vector<float> v2, vector<float> v3) { this->m_ = {v1, v2, v3}; }
    matrix_3(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) { this->m_ = {{x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3}}; }
    static matrix_3();
    static matrix_3 i() { return i; }
    ~matrix_3();
    vector<vector<float>> m() { return m_; }
    matrix_3 operator+(matrix_3 m) { return matrix_3({{m_[0][0] + m.m()[0][0], m_[0][1] + m.m()[0][1], m_[0][2] + m.m()[0][2]},
                                                      {m_[1][0] + m.m()[1][0], m_[1][1] + m.m()[1][1], m_[1][2] + m.m()[1][2]},
                                                      {m_[2][0] + m.m()[2][0], m_[2][1] + m.m()[2][1], m_[2][2] + m.m()[2][2]}}); }
    matrix_3 operator-(matrix_3 m) { return matrix_3({{m_[0][0] - m.m()[0][0], m_[0][1] - m.m()[0][1], m_[0][2] - m.m()[0][2]},
                                                        {m_[1][0] - m.m()[1][0], m_[1][1] - m.m()[1][1], m_[1][2] - m.m()[1][2]},
                                                        {m_[2][0] - m.m()[2][0], m_[2][1] - m.m()[2][1], m_[2][2] - m.m()[2][2]}}); }
    matrix_3 operator*(float f) { return matrix_3({{m_[0][0] * f, m_[0][1] * f, m_[0][2] * f},
                                                        {m_[1][0] * f, m_[1][1] * f, m_[1][2] * f},
                                                        {m_[2][0] * f, m_[2][1] * f, m_[2][2] * f}}); }
    matrix_3 operator/(float f) { return matrix_3({{m_[0][0] / f, m_[0][1] / f, m_[0][2] / f},
                                                        {m_[1][0] / f, m_[1][1] / f, m_[1][2] / f},
                                                        {m_[2][0] / f, m_[2][1] / f, m_[2][2] / f}}); }
    matrix_3 operator*(matrix_3 m) { return matrix_3({{m_[0][0] * m.m()[0][0] + m_[0][1] * m.m()[1][0] + m_[0][2] * m.m()[2][0], m_[0][0] * m.m()[0][1] + m_[0][1] * m.m()[1][1] + m_[0][2] * m.m()[2][1], m_[0][0] * m.m()[0][2] + m_[0][1] * m.m()[1][2] + m_[0][2] * m.m()[2][2]},
                                                        {m_[1][0] * m.m()[0][0] + m_[1][1] * m.m()[1][0] + m_[1][2] * m.m()[2][0], m_[1][0] * m.m()[0][1] + m_[1][1] * m.m()[1][1] + m_[1][2] * m.m()[2][1], m_[1][0] * m.m()[0][2] + m_[1][1] * m.m()[1][2] + m_[1][2] * m.m()[2][2]},
                                                        {m_[2][0] * m.m()[0][0] + m_[2][1] * m.m()[1][0] + m_[2][2] * m.m()[2][0], m_[2][0] * m.m()[0][1] + m_[2][1] * m.m()[1][1] + m_[2][2] * m.m()[2][1], m_[2][0] * m.m()[0][2] + m_[2][1] * m.m()[1][2] + m_[2][2] * m.m()[2][2]}}); }
    vector_3 operator*(vector_3 v) { return vector_3(m_[0][0] * v.x() + m_[0][1] * v.y() + m_[0][2] * v.z(),
                                                        m_[1][0] * v.x() + m_[1][1] * v.y() + m_[1][2] * v.z(),
                                                        m_[2][0] * v.x() + m_[2][1] * v.y() + m_[2][2] * v.z()); }
};

matrix_3::matrix_3()
{
    this = i;
}

matrix_3::~matrix_3()
{
}
