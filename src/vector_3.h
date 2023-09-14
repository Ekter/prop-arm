#include <vector>



class vector_3
{
private:
    vector<float> v_;
public:
    vector_3(float x, float y, float z);
    vector_3(vector<float> v) { this->v_ = v; }
    ~vector_3();
    float x() { return v_[0]; }
    float y() { return v_[1]; }
    float z() { return v_[2]; }
    float norm() { return sqrt(pow(v_[0], 2) + pow(v_[1], 2) + pow(v_[2], 2)); }
    vector_3 operator+(vector_3 v) { return vector_3(v_[0] + v.x(), v_[1] + v.y(), v_[2] + v.z()); }
    vector_3 operator-(vector_3 v) { return vector_3(v_[0] - v.x(), v_[1] - v.y(), v_[2] - v.z()); }
    vector_3 operator*(float f) { return vector_3(v_[0] * f, v_[1] * f, v_[2] * f); }
    vector_3 operator/(float f) { return vector_3(v_[0] / f, v_[1] / f, v_[2] / f); }
};

vector_3::vector_3(float x, float y, float z)
{
    this->v_ = {x, y, z};
}

vector_3::~vector_3()
{
}
