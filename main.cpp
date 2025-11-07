#include <iostream>
#include <memory>
#include <vector>

#include "Laba4/headlines/Point.h"
#include "Laba4/headlines/Array.h"
#include "Laba4/headlines/Triangle.h"
#include "Laba4/headlines/Octagon.h"
#include "Laba4/headlines/Hexagon.h"
#include "Laba4/headlines/Figure.h"

void demonstrateFigureArray() {
    std::cout << "=== Демонстрация Array<std::shared_ptr<Figure<double>>> ===" << std::endl;
    
    Array<std::shared_ptr<Figure<double>>> figure_array;
    
    figure_array.Add(std::make_shared<Hexagon<double>>(
        Point<double>{1.0, 0.0}, Point<double>{3.0, 0.0}, Point<double>{4.0, 2.0},
        Point<double>{3.0, 4.0}, Point<double>{1.0, 4.0}, Point<double>{0.0, 2.0}
    ));
    
    figure_array.Add(std::make_shared<Octagon<double>>(
        Point<double>{1,0}, Point<double>{2,0}, Point<double>{3,1}, Point<double>{3,2},
        Point<double>{2,3}, Point<double>{1,3}, Point<double>{0,2}, Point<double>{0,1}
    ));
    
    figure_array.Add(std::make_shared<Triangle<double>>(
        Point<double>{0.0, 0.0}, Point<double>{5.0, 0.0}, Point<double>{2.5, 5.0}
    ));
    
    std::cout << "\nВсе фигуры в массиве:" << std::endl;
    figure_array.PrintAll(std::cout);
    
    std::cout << "\nОбщая площадь фигур: " << figure_array.TotalArea() << std::endl;
    
    std::cout << "\nУдаляем фигуру с индексом 1..." << std::endl;
    figure_array.Remove(1);
    
    std::cout << "\nФигуры после удаления:" << std::endl;
    figure_array.PrintAll(std::cout);
    std::cout << "Общая площадь после удаления: " << figure_array.TotalArea() << std::endl;
}

void demonstrateIntArray() {
    std::cout << "\n\n=== Демонстрация Array<int> (базовый тип) ===" << std::endl;
    
    Array<int> int_array;
    
    for (int i = 0; i < 5; ++i) {
        int_array.Add(i * 10);
    }
    
    std::cout << "Содержимое массива int:" << std::endl;
    for (size_t i = 0; i < int_array.Size(); ++i) {
        std::cout << "int_array[" << i << "] = " << int_array.Get(i) << std::endl;
    }
    
    std::cout << "Размер массива: " << int_array.Size() << std::endl;
    std::cout << "Емкость массива: " << int_array.Capacity() << std::endl;
}

void demonstrateMoveSemantics() {
    std::cout << "\n\n=== Демонстрация move семантики ===" << std::endl;
    
    Array<std::shared_ptr<Figure<double>>> source_array;
    
    source_array.Add(std::make_shared<Triangle<double>>(
        Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{2, 3}
    ));
    
    std::cout << "Исходный массив (перед move): " << source_array.Size() << " элементов" << std::endl;
    
    Array<std::shared_ptr<Figure<double>>> target_array = std::move(source_array);
    
    std::cout << "Целевой массив (после move): " << target_array.Size() << " элементов" << std::endl;
    std::cout << "Исходный массив (после move): " << source_array.Size() << " элементов" << std::endl;
    
    target_array.PrintAll(std::cout);
}

int main() {
    try {
        demonstrateFigureArray();
        demonstrateIntArray();
        demonstrateMoveSemantics();
        
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}