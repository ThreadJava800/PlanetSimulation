#ifndef __POINT_H__
#define __POINT_H__

#include <cmath>
#include <SFML/Graphics.hpp>

#include "settings.h"

/// constant used to compare doubles
static const DOUBLE epsilon = 1e-12;

inline bool doubleCmp(const DOUBLE a, const DOUBLE b) {
    return std::abs(a - b) < epsilon;
}

struct Vector2D {
    DOUBLE x = 0;
    DOUBLE y = 0;

    Vector2D() :
        x (0),
        y (0)
    {}
    Vector2D(const double _x, const double _y) :
        x (_x),
        y (_y)
    {}
    explicit Vector2D(const sf::Vector2f _point) :
        x (_point.x),
        y (_point.y)
    {}
    explicit Vector2D(const sf::Vector2i _point) :
        x (_point.x),
        y (_point.y)
    {}

    // Vector AB
    explicit Vector2D(const sf::Vector2f _a, const sf::Vector2f _b):
        x (_b.x - _a.x),
        y (_b.y - _a.y)
    {}
    explicit Vector2D(const Vector2D _a, const Vector2D _b):
        x (_b.x - _a.x),
        y (_b.y - _a.y)
    {}

    operator sf::Vector2f() const {
        return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
    }

    bool isNan() {
        return std::isnan(x) || std::isnan(y);
    }

    DOUBLE getLen() const {
        return std::sqrt(x * x + y * y);
    }

    friend void operator+=(Vector2D& a, const Vector2D& b) {
        a.x += b.x;
        a.y += b.y;
    }
    friend Vector2D operator+(const Vector2D& a, const Vector2D& b) {
        Vector2D res = a;
        res += b;
        return res;
    }
    friend void operator-=(Vector2D& a, const Vector2D& b) {
        a.x -= b.x;
        a.y -= b.y;
    }
    friend Vector2D operator-(const Vector2D& a, const Vector2D& b) {
        Vector2D res = a;
        res -= b;
        return res;
    }
    friend bool operator==(const Vector2D& a, const Vector2D& b) {
        return doubleCmp(a.x, b.x) && doubleCmp(a.y, b.y);
    }
    friend Vector2D operator*(const double scalar, const Vector2D& a) {
        return Vector2D(a.x * scalar, a.y * scalar);
    }
    friend Vector2D operator*(const Vector2D& a, const double scalar) {
        return Vector2D(a.x * scalar, a.y * scalar);
    }
    friend Vector2D operator/(const Vector2D& a, const double scalar) {
        return Vector2D(a.x / scalar, a.y / scalar);
    }
    friend DOUBLE operator,(const Vector2D &a, const Vector2D &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend DOUBLE operator^(const Vector2D &a, const Vector2D &b) {
        return a.x * b.y - a.y * b.x;
    }
};

struct Point3D {
    DOUBLE x = 0;
    DOUBLE y = 0;
    DOUBLE z = 0;

    Point3D() :
        x (0),
        y (0),
        z (0)
    {}
    Point3D(const double _x, const double _y, const double _z) :
        x (_x),
        y (_y),
        z (_z)
    {}
    explicit Point3D(const sf::Vector3f _point) :
        x (_point.x),
        y (_point.y),
        z (_point.z)
    {}
    explicit Point3D(const sf::Vector3i _point) :
        x (_point.x),
        y (_point.y),
        z (_point.z)
    {}

    operator sf::Vector3<DOUBLE>() const {
        return sf::Vector3<DOUBLE>(x, y, z);
    }

    bool isNan() {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }

    DOUBLE getLen() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    friend void operator+=(Point3D& a, const Point3D& b) {
        a.x += b.x;
        a.y += b.y;
        a.z += b.z;
    }
    friend Point3D operator+(const Point3D& a, const Point3D& b) {
        Point3D res = a;
        res += b;
        return res;
    }
    friend void operator-=(Point3D& a, const Point3D& b) {
        a.x -= b.x;
        a.y -= b.y;
        a.z -= b.z;
    }
    friend Point3D operator-(const Point3D& a, const Point3D& b) {
        Point3D res = a;
        res -= b;
        return res;
    }
    friend bool operator==(const Point3D& a, const Point3D& b) {
        return doubleCmp(a.x, b.x) && doubleCmp(a.y, b.y) && doubleCmp(a.z, b.z);
    }
};

#endif