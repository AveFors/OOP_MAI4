#pragma once
#include "Figure.h"
#include <cmath>
#include <utility>
#include <memory>

template <Scalar T>
class Triangle : public Figure<T> {
private:
    std::unique_ptr<Point<T>> a, b, c;

public:
    Triangle() = default;

    Triangle(Point<T> a_point, Point<T> b_point, Point<T> c_point)
        : a(std::make_unique<Point<T>>(a_point))
        , b(std::make_unique<Point<T>>(b_point))
        , c(std::make_unique<Point<T>>(c_point)) {}
    
    Triangle(const Triangle& other)
        : a(std::make_unique<Point<T>>(*other.a))
        , b(std::make_unique<Point<T>>(*other.b))
        , c(std::make_unique<Point<T>>(*other.c)) {}
    
    Triangle(Triangle&& other) noexcept = default;
    
    Triangle& operator=(const Triangle& other) {
        if (this != &other) {
            a = std::make_unique<Point<T>>(*other.a);
            b = std::make_unique<Point<T>>(*other.b);
            c = std::make_unique<Point<T>>(*other.c);
        }
        return *this;
    }
    
    Triangle& operator=(Triangle&& other) noexcept = default;
    
    ~Triangle() override = default;

    Point<T> center() const override {
        T cx = (a->get_x() + b->get_x() + c->get_x());
        T cy = (a->get_y() + b->get_y() + c->get_y());
        return Point<T>(cx / 3.0, cy / 3.0);
    }

    double area() const override {
        return 0.5 * std::abs(
            (double)(a->get_x() * (b->get_y() - c->get_y()) +
                     b->get_x() * (c->get_y() - a->get_y()) +
                     c->get_x() * (a->get_y() - b->get_y()))
        );
    }

    bool equals(const Figure<T>& other) const override {
        const auto* t = dynamic_cast<const Triangle<T>*>(&other);
        if (!t) return false;
        return (*a == *(t->a) && *b == *(t->b) && *c == *(t->c));
    }

    void Print(std::ostream &os) const override {
        os << "Triangle: "
           << *a << " " << *b << " " << *c
           << " | Center: " << center()
           << " | Area: " << area();
    }

    void Scan(std::istream &is) override {
        Point<T> temp_a, temp_b, temp_c;
        is >> temp_a >> temp_b >> temp_c;
        a = std::make_unique<Point<T>>(temp_a);
        b = std::make_unique<Point<T>>(temp_b);
        c = std::make_unique<Point<T>>(temp_c);
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Triangle<T>>(*this);
    }
};