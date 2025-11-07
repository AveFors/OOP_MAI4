#pragma once
#include "Figure.h"
#include <cmath>
#include <utility>
#include <memory>

template <Scalar T>
class Octagon : public Figure<T> {
private:
    std::unique_ptr<Point<T>> p1, p2, p3, p4, p5, p6, p7, p8;

public:
    Octagon() = default;

    Octagon(Point<T> p1_point, Point<T> p2_point, Point<T> p3_point, Point<T> p4_point,
            Point<T> p5_point, Point<T> p6_point, Point<T> p7_point, Point<T> p8_point)
        : p1(std::make_unique<Point<T>>(p1_point))
        , p2(std::make_unique<Point<T>>(p2_point))
        , p3(std::make_unique<Point<T>>(p3_point))
        , p4(std::make_unique<Point<T>>(p4_point))
        , p5(std::make_unique<Point<T>>(p5_point))
        , p6(std::make_unique<Point<T>>(p6_point))
        , p7(std::make_unique<Point<T>>(p7_point))
        , p8(std::make_unique<Point<T>>(p8_point)) {}
    
    Octagon(const Octagon& other)
        : p1(std::make_unique<Point<T>>(*other.p1))
        , p2(std::make_unique<Point<T>>(*other.p2))
        , p3(std::make_unique<Point<T>>(*other.p3))
        , p4(std::make_unique<Point<T>>(*other.p4))
        , p5(std::make_unique<Point<T>>(*other.p5))
        , p6(std::make_unique<Point<T>>(*other.p6))
        , p7(std::make_unique<Point<T>>(*other.p7))
        , p8(std::make_unique<Point<T>>(*other.p8)) {}
    
    Octagon(Octagon&& other) noexcept = default;
    
    Octagon& operator=(const Octagon& other) {
        if (this != &other) {
            p1 = std::make_unique<Point<T>>(*other.p1);
            p2 = std::make_unique<Point<T>>(*other.p2);
            p3 = std::make_unique<Point<T>>(*other.p3);
            p4 = std::make_unique<Point<T>>(*other.p4);
            p5 = std::make_unique<Point<T>>(*other.p5);
            p6 = std::make_unique<Point<T>>(*other.p6);
            p7 = std::make_unique<Point<T>>(*other.p7);
            p8 = std::make_unique<Point<T>>(*other.p8);
        }
        return *this;
    }
    
    Octagon& operator=(Octagon&& other) noexcept = default;
    
    ~Octagon() override = default;

    Point<T> center() const override {
        T cx = (p1->get_x() + p2->get_x() + p3->get_x() + p4->get_x() +
                p5->get_x() + p6->get_x() + p7->get_x() + p8->get_x());
        T cy = (p1->get_y() + p2->get_y() + p3->get_y() + p4->get_y() +
                p5->get_y() + p6->get_y() + p7->get_y() + p8->get_y());
        return Point<T>(cx / 8.0, cy / 8.0);
    }

    double area() const override {
        double area = 0.5 * std::abs(
            ((double)p1->get_x() * p2->get_y() + p2->get_x() * p3->get_y() + p3->get_x() * p4->get_y() + p4->get_x() * p5->get_y() +
             p5->get_x() * p6->get_y() + p6->get_x() * p7->get_y() + p7->get_x() * p8->get_y() + p8->get_x() * p1->get_y()) -
            (p2->get_x() * p1->get_y() + p3->get_x() * p2->get_y() + p4->get_x() * p3->get_y() + p5->get_x() * p4->get_y() +
             p6->get_x() * p5->get_y() + p7->get_x() * p6->get_y() + p8->get_x() * p7->get_y() + p1->get_x() * p8->get_y())
        );
        return area;
    }
   
    bool equals(const Figure<T>& other) const override {
        const auto* o = dynamic_cast<const Octagon<T>*>(&other);
        if (!o) return false;
        return (*p1 == *(o->p1) && *p2 == *(o->p2) && *p3 == *(o->p3) && *p4 == *(o->p4) &&
                *p5 == *(o->p5) && *p6 == *(o->p6) && *p7 == *(o->p7) && *p8 == *(o->p8));
    }

    void Print(std::ostream &os) const override {
        os << "Octagon: "
           << *p1 << " " << *p2 << " " << *p3 << " " << *p4 << " "
           << *p5 << " " << *p6 << " " << *p7 << " " << *p8
           << " | Center: " << center()
           << " | Area: " << area();
    }

    void Scan(std::istream &is) override {
        Point<T> temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8;
        is >> temp1 >> temp2 >> temp3 >> temp4 >> temp5 >> temp6 >> temp7 >> temp8;
        p1 = std::make_unique<Point<T>>(temp1);
        p2 = std::make_unique<Point<T>>(temp2);
        p3 = std::make_unique<Point<T>>(temp3);
        p4 = std::make_unique<Point<T>>(temp4);
        p5 = std::make_unique<Point<T>>(temp5);
        p6 = std::make_unique<Point<T>>(temp6);
        p7 = std::make_unique<Point<T>>(temp7);
        p8 = std::make_unique<Point<T>>(temp8);
    }
    
    std::unique_ptr<Figure<T>> clone() const override {
        return std::make_unique<Octagon<T>>(*this);
    }
};