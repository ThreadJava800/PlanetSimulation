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

struct Point2D {
    DOUBLE x = 0;
    DOUBLE y = 0;

    Point2D() :
        x (0),
        y (0)
    {}
    Point2D(const double _x, const double _y) :
        x (_x),
        y (_y)
    {}
    explicit Point2D(const sf::Vector2f _point) :
        x (_point.x),
        y (_point.y)
    {}
    explicit Point2D(const sf::Vector2i _point) :
        x (_point.x),
        y (_point.y)
    {}

    operator sf::Vector2f() const {
        return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
    }

    bool isNan() {
        return std::isnan(x) || std::isnan(y);
    }

    DOUBLE getLen() {
        return std::sqrt(x * x + y * y);
    }

    friend void operator+=(Point2D& a, const Point2D& b) {
        a.x += b.x;
        a.y += b.y;
    }
    friend Point2D operator+(const Point2D& a, const Point2D& b) {
        Point2D res = a;
        res += b;
        return res;
    }
    friend void operator-=(Point2D& a, const Point2D& b) {
        a.x -= b.x;
        a.y -= b.y;
    }
    friend Point2D operator-(const Point2D& a, const Point2D& b) {
        Point2D res = a;
        res -= b;
        return res;
    }
    friend bool operator==(const Point2D& a, const Point2D& b) {
        return doubleCmp(a.x, b.x) && doubleCmp(a.y, b.y);
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

    DOUBLE getLen() {
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

static sf::Vector2f normalize(const sf::Vector2f &v) {
    double len = sqrt(v.x * v.x + v.y * v.y);

    return sf::Vector2f(v.x / len, v.y / len);
}

static sf::Vector2f makeVector(const Point2D &a, const Point2D &b) {
    return sf::Vector2f(b.x - a.x, b.y - a.y);
}

static sf::Vector2f ortogVector(const sf::Vector2f &v) {
    return sf::Vector2f(-v.y, v.x);
}

using Size2D = Point2D;
using Size3D = Point3D;

#endif