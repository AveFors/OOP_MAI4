#pragma once
#include "Figure.h"
#include <cmath>
#include <utility>
#include <memory>

template <Scalar T>
class Hexagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4, p5, p6;

public:
    Hexagon() = default;

    Hexagon(Point<T> p1_point, Point<T> p2_point, Point<T> p3_point,
            Point<T> p4_point, Point<T> p5_point, Point<T> p6_point)
        : p1(std::make_unique<Point<T>>(p1_point))
        , p2(std::make_unique<Point<T>>(p2_point))
        , p3(std::make_unique<Point<T>>(p3_point))
        , p4(std::make_unique<Point<T>>(p4_point))
        , p5(std::make_unique<Point<T>>(p5_point))
        , p6(std::make_unique<Point<T>>(p6_point)) {}
    
    Hexagon(const Hexagon& other)
        : p1(std::make_unique<Point<T>>(*other.p1))
        , p2(std::make_unique<Point<T>>(*other.p2))
        , p3(std::make_unique<Point<T>>(*other.p3))
        , p4(std::make_unique<Point<T>>(*other.p4))
        , p5(std::make_unique<Point<T>>(*other.p5))
        , p6(std::make_unique<Point<T>>(*other.p6)) {}
    
    Hexagon(Hexagon&& other) noexcept = default;
    
    Hexagon& operator=(const Hexagon& other) {
        if (this != &other) {
            p1 = std::make_unique<Point<T>>(*other.p1);
            p2 = std::make_unique<Point<T>>(*other.p2);
            p3 = std::make_unique<Point<T>>(*other.p3);
            p4 = std::make_unique<Point<T>>(*other.p4);
            p5 = std::make_unique<Point<T>>(*other.p5);
            p6 = std::make_unique<Point<T>>(*other.p6);
        }
        return *this;
    }
    
    Hexagon& operator=(Hexagon&& other) noexcept = default;
    
    ~Hexagon() override = default;

    Point<T> center() const override {
        T cx = (p1->get_x() + p2->get_x() + p3->get_x() + p4->get_x() + p5->get_x() + p6->get_x());
        T cy = (p1->get_y() + p2->get_y() + p3->get_y() + p4->get_y() + p5->get_y() + p6->get_y());
        return Point<T>(cx / 6.0, cy / 6.0);
    }

    double area() const override {
        double area = 0.5 * std::abs(
            ((double)p1->get_x() * p2->get_y() + p2->get_x() * p3->get_y() + p3->get_x() * p4->get_y() +
             p4->get_x() * p5->get_y() + p5->get_x() * p6->get_y() + p6->get_x() * p1->get_y()) -
            (p2->get_x() * p1->get_y() + p3->get_x() * p2->get_y() + p4->get_x() * p3->get_y() +
             p5->get_x() * p4->get_y() + p6->get_x() * p5->get_y() + p1->get_x() * p6->get_y())
        );
        return area;
    }

    bool equals(const Figure<T>& other) const override {
        const auto* h = dynamic_cast<const Hexagon<T>*>(&other);
        if (!h) return false;
        return (*p1 == *(h->p1) && *p2 == *(h->p2) && *p3 == *(h->p3) &&
                *p4 == *(h->p4) && *p5 == *(h->p5) && *p6 == *(h->p6));
    }

    void Print(std::ostream &os) const override {
        os << "Hexagon: "
           << *p1 << " " << *p2 << " " << *p3 << " "
           << *p4 << " " << *p5 << " " << *p6
           << " | Center: " << center()
           << " | Area: " << area();
    }

    void Scan(std::istream &is) override {
        Point<T> temp1, temp2, temp3, temp4, temp5, temp6;
        is >> temp1 >> temp2 >> temp3 >> temp4 >> temp5 >> temp6;
        p1 = std::make_unique<Point<T>>(temp1);
        p2 = std::make_unique<Point<T>>(temp2);
        p3 = std::make_unique<Point<T>>(temp3);
        p4 = std::make_unique<Point<T>>(temp4);
        p5 = std::make_unique<Point<T>>(temp5);
        p6 = std::make_unique<Point<T>>(temp6);
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Hexagon<T>>(*this);
    }
};