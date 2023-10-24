#include <vector>
#include <iostream>
#include <cmath>

// Base class Curve
class Curve {
public:
    virtual ~Curve() = default;
    virtual std::vector<double> getPoint(double t) const = 0;
    virtual std::vector<double> getDerivative(double t) const = 0;
};

// Circle class, derived from Curve
class Circle : public Curve {
    double radius;
public:
    Circle(double r) : radius(r) {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive.");
        }
    }

    ~Circle() {}

    std::vector<double> getPoint(double t) const override {
        double x = radius * std::cos(t);
        double y = radius * std::sin(t);
        double z = 0.0;
        return {x, y, z};
    }

    std::vector<double> getDerivative(double t) const override {
        double dx = -radius * std::sin(t);
        double dy = radius * std::cos(t);
        double dz = 0.0;
        return {dx, dy, dz};
    }

    double getRadius() const {
        return radius;
    }
};

// Ellipse class, derived from Curve
class Ellipse : public Curve {
    double a, b;
public:
    Ellipse(double a, double b) : a(a), b(b) {
        if (a <= 0 || b <= 0) {
            throw std::invalid_argument("Semi-axes must be positive.");
        }
    }

    ~Ellipse() {}

    std::vector<double> getPoint(double t) const override {
        double x = a * std::cos(t);
        double y = b * std::sin(t);
        double z = 0.0;
        return {x, y, z};
    }

    std::vector<double> getDerivative(double t) const override {
        double dx = -a * std::sin(t);
        double dy = b * std::cos(t);
        double dz = 0.0;
        return {dx, dy, dz};
    }
};

// Spiral class, derived from Curve
class Helix : public Curve {
    double radius;
    double step;
public:
    Helix(double r, double s) : radius(r), step(s) {
        if (radius <= 0 || step <= 0) {
            throw std::invalid_argument("Radius and step must be positive.");
        }
    }

    ~Helix() {}

    std::vector<double> getPoint(double t) const override {
        double x = radius * std::cos(t);
        double y = radius * std::sin(t);
        double z = step * t / (2 * M_PI);
        return {x, y, z};
    }

    std::vector<double> getDerivative(double t) const override {
        double dx = -radius * std::sin(t);
        double dy = radius * std::cos(t);
        double dz = step / (2 * M_PI);
        return {dx, dy, dz};
    }
};