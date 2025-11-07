#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include "concepts.h"

template<Scalar T>
struct Point {
    
    T x, y;

    Point() : x(), y() {}
    Point(T _x, T _y) : x(_x), y(_y) {}
    
    Point(const Point& other) : x(other.x), y(other.y) {}
    Point& operator=(const Point& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    
    Point(Point&& other) noexcept : x(std::move(other.x)), y(std::move(other.y)) {}
    Point& operator=(Point&& other) noexcept {
        if (this != &other) {
            x = std::move(other.x);
            y = std::move(other.y);
        }
        return *this;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Point<T> &p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    
    friend std::istream &operator>>(std::istream &is, Point<T> &p) {
        return is >> p.x >> p.y;
    }
    
    T get_x() const { return x; }
    T get_y() const { return y; }
    
    bool operator==(const Point<T>& other) const {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Point<T>& other) const {
        return !(*this == other);
    }
};