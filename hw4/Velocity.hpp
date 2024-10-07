#pragma once
#include "Point.hpp"
#include <cmath>

class Velocity {
  public:
    inline Velocity() = default;
        ///inline Point(double x, double y) : x{x}, y{y} {};

    // double abs{};
    // double angle{};

    // TODO: комментарии
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        vec = Point{x, y} * abs;
    } //: x{x}, y{y} {};

    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    inline void setVector(const Point& vector) {
        vec = vector;
    }

    inline Point vector() const {
        return vec;
    }

  private:
    Point vec;
};
