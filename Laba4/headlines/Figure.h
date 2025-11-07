#pragma once
#include <iostream>
#include <utility>
#include <memory>
#include "Point.h"
#include "concepts.h"

template <Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual bool equals(const Figure<T>& other) const = 0;
    virtual void Print(std::ostream &os) const = 0;
    virtual void Scan(std::istream &is) = 0;
    virtual std::unique_ptr<Figure<T>> clone() const = 0;

    operator double() const {
        return area();
    }
};

template <class T>
bool operator==(const Figure<T>& lhs, const Figure<T>& rhs) {
    return lhs.equals(rhs);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &f) {
    f.Print(os);
    return os;
}

template <class T>
std::istream &operator>>(std::istream &is, Figure<T> &f) {
    f.Scan(is);
    return is;
}