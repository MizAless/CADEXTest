#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>

class Curve {
public:
    virtual double getRadius() const = 0;
    virtual double getStep() const = 0;
    virtual double getX(double t) const = 0;
    virtual double getY(double t) const = 0;
    virtual double getZ(double t) const = 0;
    virtual double getDerivativeX(double t) const = 0;
    virtual double getDerivativeY(double t) const = 0;
    virtual double getDerivativeZ(double t) const = 0;
};

class Circle : public Curve {
private:
    double radius;
public:
    Circle(double radius) : radius(radius) {
        if (radius <= 0) {
            throw std::invalid_argument("Radius must be positive");
        }
    }

    double getRadius() const override {
        return radius;
    }

    double getStep() const override {
        return 0;
    }

    double getX(double t) const override {
        return radius * cos(t);
    }

    double getY(double t) const override {
        return radius * sin(t);
    }

    double getZ(double t) const override {
        return 0;
    }

    double getDerivativeX(double t) const override {
        return -radius * sin(t);
    }

    double getDerivativeY(double t) const override {
        return radius * cos(t);
    }

    double getDerivativeZ(double t) const override {
        return 0;
    }
};

class Ellipse : public Curve {
private:
    double radiusX;
    double radiusY;
public:
    Ellipse(double radiusX, double radiusY) : radiusX(radiusX), radiusY(radiusY) {
        if (radiusX <= 0 || radiusY <= 0) {
            throw std::invalid_argument("Radii must be positive");
        }
    }

    double getRadius() const override {
        return std::max(radiusX, radiusY);
    }

    double getStep() const override {
        return 0;
    }

    double getX(double t) const override {
        return radiusX * cos(t);
    }

    double getY(double t) const override {
        return radiusY * sin(t);
    }

    double getZ(double t) const override {
        return 0;
    }

    double getDerivativeX(double t) const override {
        return -radiusX * sin(t);
    }

    double getDerivativeY(double t) const override {
        return radiusY * cos(t);
    }

    double getDerivativeZ(double t) const override {
        return 0;
    }
};

class Helix : public Curve {
private:
    double radius;
    double step;
public:
    Helix(double radius, double step) : radius(radius), step(step) {
        if (radius <= 0 || step <= 0) {
            throw std::invalid_argument("Radius and step must be positive");
        }
    }

    double getRadius() const override {
        return radius;
    }

    double getStep() const override {
        return step;
    }

    double getX(double t) const override {
        return radius * cos(t);
    }

    double getY(double t) const override {
        return radius * sin(t);
    }

    double getZ(double t) const override {
        return step * t / (2 * M_PI);
    }

    double getDerivativeX(double t) const override {
        return -radius * sin(t);
    }

    double getDerivativeY(double t) const override {
        return radius * cos(t);
    }

    double getDerivativeZ(double t) const override {
        return step / (2 * M_PI);
    }
};

void printCoordinatesAndDerivatives(const Curve& curve, double t) {
    std::cout << "Coordinates at t = " << t << ": (" << curve.getX(t) << ", " << curve.getY(t) << ", " << curve.getZ(t) << ")" << std::endl;
    std::cout << "Derivatives at t = " << t << ": (" << curve.getDerivativeX(t) << ", " << curve.getDerivativeY(t) << ", " << curve.getDerivativeZ(t) << ")" << std::endl;
}

bool compareCirclesByRadius(const Circle* circle1, const Circle* circle2) {
    return circle1->getRadius() < circle2->getRadius();
}

int main() {
    std::vector<Curve*> curves;
    std::list<Circle*> circles;

    curves.push_back(new Circle(5.0));
    curves.push_back(new Circle(3.0));
    curves.push_back(new Circle(9.0));
    curves.push_back(new Circle(2.0));
    curves.push_back(new Ellipse(2.0, 4.0));
    curves.push_back(new Helix(5.0, 1.0));

    double t = M_PI / 4.0;

    // Print coordinates and derivatives of all curves at t = PI/4
    for (const auto& curve : curves) {
        printCoordinatesAndDerivatives(*curve, t);
    }

    // Populate the second container with circles from the first container
    for (const auto& curve : curves) {
        if (dynamic_cast<Circle*>(curve)) {
            circles.push_back(static_cast<Circle*>(curve));
        }
    }

    // Sort the second container in ascending order of circles' radii
    circles.sort(compareCirclesByRadius);

    std::cout << "Circles after sort:" << std::endl;

    for (const auto& circle : circles) {
        printCoordinatesAndDerivatives(*circle, t);
    }

    // Compute the total sum of radii of all curves in the second container
    double totalSum = 0.0;
    for (const auto& circle : circles) {
        totalSum += circle->getRadius();
    }

    std::cout << "Total sum of radii: " << totalSum << std::endl;

    // Clean up memory
    for (const auto& curve : curves) {
        delete curve;
    }

    return 0;
}