#pragma once

#include <iostream>
#include <random>

constexpr float PI = 3.14159265f;

class Vec3 {
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    Vec3() = default;
    Vec3(float x, float y, float z);

    static Vec3 minOfTwo(const Vec3& v1, const Vec3& v2);
    static Vec3 maxOfTwo(const Vec3& v1, const Vec3& v2);

    static Vec3 reflect(const Vec3& inDir, const Vec3& normal);

    Vec3 &operator=(const Vec3 &rhs);
    Vec3 &operator+=(const Vec3 &rhs);
    Vec3 &operator-=(const Vec3 &rhs);
    Vec3 &operator*=(float rhs);
    Vec3 &operator/=(float rhs);

    static float dot(const Vec3& v1, const Vec3& v2);
    static Vec3 cross(const Vec3& v1, const Vec3& v2);

    float getLength() const;
    void normalize();
};

Vec3 operator+(Vec3 lhs, const Vec3 &rhs);
Vec3 operator-(Vec3 lhs, const Vec3 &rhs);
Vec3 operator*(Vec3 lhs, float rhs);
Vec3 operator*(float lhs, Vec3 rhs);
Vec3 operator/(Vec3 lhs, float rhs);
Vec3 operator+(const Vec3 &rhs);
Vec3 operator-(const Vec3 &rhs);

std::ostream& operator<<(std::ostream& os, const Vec3& v);

class Random {
    static std::mt19937 generator;
    static std::uniform_real_distribution<float> distribution;
public:
    // Generate a random float in [0, 1)
    static float randUniformFloat();
    static Vec3 randomHemisphereDirection(const Vec3& normal);
    static Vec3 cosWeightedHemisphere(const Vec3& normal);
};
