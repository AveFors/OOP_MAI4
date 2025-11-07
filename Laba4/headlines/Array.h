#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include "Figure.h"

template <class T>
class Array {
private:
    std::unique_ptr<T[]> figures;
    size_t current_size;
    size_t current_capacity;

    void resize(size_t new_capacity) {
        if (new_capacity <= current_capacity) {
            return;
        }
        
        std::unique_ptr<T[]> new_figures = std::make_unique<T[]>(new_capacity);
        for (size_t i = 0; i < current_size; ++i) {
            new_figures[i] = std::move(figures[i]);
        }
        
        figures = std::move(new_figures);
        current_capacity = new_capacity;
    }

public:
    Array() : figures(nullptr), current_size(0), current_capacity(0) {
        resize(10);
    }
    
    ~Array() = default;
    
    Array(Array&& other) noexcept 
        : figures(std::move(other.figures))
        , current_size(other.current_size)
        , current_capacity(other.current_capacity) {
        
        other.current_size = 0;
        other.current_capacity = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            figures = std::move(other.figures);
            current_size = other.current_size;
            current_capacity = other.current_capacity;
            
            other.current_size = 0;
            other.current_capacity = 0;
        }
        return *this;
    }

    Array(const Array& other) : current_size(other.current_size), current_capacity(other.current_capacity) {
        figures = std::make_unique<T[]>(current_capacity);
        for (size_t i = 0; i < current_size; ++i) {
            figures[i] = other.figures[i];
        }
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            std::unique_ptr<T[]> new_figures = std::make_unique<T[]>(other.current_capacity);
            for (size_t i = 0; i < other.current_size; ++i) {
                new_figures[i] = other.figures[i];
            }
            
            figures = std::move(new_figures);
            current_size = other.current_size;
            current_capacity = other.current_capacity;
        }
        return *this;
    }
    
    void Add(const T& f) {
        if (current_size == current_capacity) {
            resize(current_capacity == 0 ? 1 : current_capacity * 2);
        }
        figures[current_size] = f;
        current_size++;
    }
    
    void Add(T&& f) {
        if (current_size == current_capacity) {
            resize(current_capacity == 0 ? 1 : current_capacity * 2);
        }
        figures[current_size] = std::move(f);
        current_size++;
    }

    void Remove(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < current_size - 1; ++i) {
            figures[i] = std::move(figures[i + 1]);
        }
        current_size--;
    }

    const T& Get(size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return figures[index];
    }
    
    T& Get(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return figures[index];
    }
    
    void PrintAll(std::ostream& os) const {
        for (size_t i = 0; i < current_size; ++i) {
            os << "Item " << i << ": " << figures[i] << std::endl;
        }
    }
    
    double TotalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < current_size; ++i) {
            if constexpr (std::is_same_v<T, std::shared_ptr<Figure<double>>>) {
                total += figures[i]->area(); 
            }
            else {
                total += figures[i].area(); 
            }
        }
        return total;
    }

    size_t Size() const { return current_size; }
    size_t Capacity() const { return current_capacity; }

    void Clear() {
        current_size = 0;
    }
    
    T& operator[](size_t index) {
        return Get(index);
    }
    
    const T& operator[](size_t index) const {
        return Get(index);
    }
};