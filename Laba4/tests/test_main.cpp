#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <cmath>

#include "../headlines/Point.h"
#include "../headlines/Array.h"
#include "../headlines/Triangle.h"
#include "../headlines/Octagon.h"
#include "../headlines/Hexagon.h"
#include "../headlines/Figure.h"

// Тесты для Point
TEST(PointTest, ConstructionAndAccess) {
    Point<int> p1(5, 10);
    EXPECT_EQ(p1.get_x(), 5);
    EXPECT_EQ(p1.get_y(), 10);
    
    Point<double> p2(3.14, 2.71);
    EXPECT_DOUBLE_EQ(p2.get_x(), 3.14);
    EXPECT_DOUBLE_EQ(p2.get_y(), 2.71);
}

TEST(PointTest, OutputOperator) {
    Point<int> p(3, 4);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "(3, 4)");
}

TEST(PointTest, InputOperator) {
    Point<int> p;
    std::stringstream ss("7 9");
    ss >> p;
    EXPECT_EQ(p.get_x(), 7);
    EXPECT_EQ(p.get_y(), 9);
}

// Тесты для Triangle
TEST(TriangleTest, Construction) {
    Triangle<double> triangle(
        Point<double>{0, 0},
        Point<double>{4, 0}, 
        Point<double>{2, 3}
    );
    
    Point<double> center = triangle.center();
    EXPECT_NEAR(center.get_x(), 2.0, 1e-9);
    EXPECT_NEAR(center.get_y(), 1.0, 1e-9);
}

TEST(TriangleTest, AreaCalculation) {
    Triangle<double> triangle(
        Point<double>{0, 0},
        Point<double>{4, 0},
        Point<double>{2, 3}
    );
    
    double area = triangle.area();
    EXPECT_NEAR(area, 6.0, 1e-9);
}

TEST(TriangleTest, Equality) {
    Triangle<double> triangle1(
        Point<double>{0, 0},
        Point<double>{4, 0},
        Point<double>{2, 3}
    );
    
    Triangle<double> triangle2(
        Point<double>{0, 0},
        Point<double>{4, 0},
        Point<double>{2, 3}
    );
    
    Triangle<double> triangle3(
        Point<double>{1, 1},
        Point<double>{5, 1},
        Point<double>{3, 4}
    );
    
    EXPECT_TRUE(triangle1.equals(triangle2));
    EXPECT_FALSE(triangle1.equals(triangle3));
}

TEST(TriangleTest, DoubleConversion) {
    Triangle<double> triangle(
        Point<double>{0, 0},
        Point<double>{4, 0},
        Point<double>{2, 3}
    );
    
    double area = static_cast<double>(triangle);
    EXPECT_NEAR(area, 6.0, 1e-9);
}

// Тесты для Hexagon
TEST(HexagonTest, ConstructionAndArea) {
    Hexagon<double> hexagon(
        Point<double>{1.0, 0.0},
        Point<double>{3.0, 0.0},
        Point<double>{4.0, 2.0},
        Point<double>{3.0, 4.0},
        Point<double>{1.0, 4.0},
        Point<double>{0.0, 2.0}
    );
    
    Point<double> center = hexagon.center();
    EXPECT_NEAR(center.get_x(), 2.0, 1e-9);
    EXPECT_NEAR(center.get_y(), 2.0, 1e-9);
    
    double area = hexagon.area();
    EXPECT_NEAR(area, 12.0, 0.1);
}

// Тесты для Octagon
TEST(OctagonTest, ConstructionAndArea) {
    Octagon<double> octagon(
        Point<double>{1, 0},
        Point<double>{2, 0},
        Point<double>{3, 1},
        Point<double>{3, 2},
        Point<double>{2, 3},
        Point<double>{1, 3},
        Point<double>{0, 2},
        Point<double>{0, 1}
    );
    
    Point<double> center = octagon.center();
    EXPECT_NEAR(center.get_x(), 1.5, 1e-9);
    EXPECT_NEAR(center.get_y(), 1.5, 1e-9);
    
    double area = octagon.area();
    EXPECT_GT(area, 0.0);
}

// Тесты для Array с shared_ptr
TEST(ArraySharedPtrTest, AddAndAccess) {
    Array<std::shared_ptr<Figure<double>>> array;
    
    auto triangle = std::make_shared<Triangle<double>>(
        Point<double>{0, 0},
        Point<double>{4, 0},
        Point<double>{2, 3}
    );
    
    array.Add(triangle);
    EXPECT_EQ(array.Size(), 1);
    EXPECT_EQ(array.Get(0), triangle);
}

TEST(ArraySharedPtrTest, TotalAreaWithSharedPtr) {
    Array<std::shared_ptr<Figure<double>>> array;
    
    array.Add(std::make_shared<Triangle<double>>(
        Point<double>{0, 0},
        Point<double>{4, 0},
        Point<double>{2, 3}
    ));
    
    array.Add(std::make_shared<Hexagon<double>>(
        Point<double>{1.0, 0.0},
        Point<double>{3.0, 0.0},
        Point<double>{4.0, 2.0},
        Point<double>{3.0, 4.0},
        Point<double>{1.0, 4.0},
        Point<double>{0.0, 2.0}
    ));
    
    double total_area = array.TotalArea();
    EXPECT_GT(total_area, 0.0);
}

TEST(ArraySharedPtrTest, RemoveElement) {
    Array<std::shared_ptr<Figure<double>>> array;
    
    auto fig1 = std::make_shared<Triangle<double>>(
        Point<double>{0, 0}, Point<double>{1, 0}, Point<double>{0, 1}
    );
    auto fig2 = std::make_shared<Triangle<double>>(
        Point<double>{0, 0}, Point<double>{2, 0}, Point<double>{0, 2}
    );
    
    array.Add(fig1);
    array.Add(fig2);
    
    EXPECT_EQ(array.Size(), 2);
    array.Remove(0);
    EXPECT_EQ(array.Size(), 1);
    EXPECT_EQ(array.Get(0), fig2);
}

// Тесты для Array с объектами
TEST(ArrayObjectTest, AddAndAccessObjects) {
    Array<Triangle<int>> array;
    
    Triangle<int> triangle(
        Point<int>{0, 0},
        Point<int>{4, 0},
        Point<int>{2, 3}
    );
    
    array.Add(triangle);
    EXPECT_EQ(array.Size(), 1);
    
    Triangle<int> retrieved = array.Get(0);
    EXPECT_TRUE(retrieved.equals(triangle));
}

TEST(ArrayObjectTest, TotalAreaWithObjects) {
    Array<Triangle<double>> array;
    
    array.Add(Triangle<double>(
        Point<double>{0, 0},
        Point<double>{4, 0},
        Point<double>{2, 3}
    ));
    
    array.Add(Triangle<double>(
        Point<double>{0, 0},
        Point<double>{3, 0},
        Point<double>{1, 2}
    ));
    
    double total_area = array.TotalArea();
    EXPECT_GT(total_area, 0.0);
}

// Тесты для Array с базовым типом
TEST(ArrayIntTest, BasicOperations) {
    Array<int> array;
    
    for (int i = 0; i < 5; ++i) {
        array.Add(i * 10);
    }
    
    EXPECT_EQ(array.Size(), 5);
    EXPECT_EQ(array.Get(0), 0);
    EXPECT_EQ(array.Get(2), 20);
    EXPECT_EQ(array.Get(4), 40);
}

TEST(ArrayIntTest, RemoveAndClear) {
    Array<int> array;
    
    array.Add(10);
    array.Add(20);
    array.Add(30);
    
    array.Remove(1);
    EXPECT_EQ(array.Size(), 2);
    EXPECT_EQ(array.Get(0), 10);
    EXPECT_EQ(array.Get(1), 30);
    
    array.Clear();
    EXPECT_EQ(array.Size(), 0);
}

// Тесты для move семантики
TEST(ArrayMoveTest, MoveConstructor) {
    Array<std::shared_ptr<Figure<double>>> source;
    
    source.Add(std::make_shared<Triangle<double>>(
        Point<double>{0, 0}, Point<double>{1, 0}, Point<double>{0, 1}
    ));
    
    size_t original_size = source.Size();
    Array<std::shared_ptr<Figure<double>>> target = std::move(source);
    
    EXPECT_EQ(target.Size(), original_size);
    EXPECT_EQ(source.Size(), 0);
}

TEST(ArrayMoveTest, MoveAssignment) {
    Array<std::shared_ptr<Figure<double>>> source;
    Array<std::shared_ptr<Figure<double>>> target;
    
    source.Add(std::make_shared<Triangle<double>>(
        Point<double>{0, 0}, Point<double>{1, 0}, Point<double>{0, 1}
    ));
    
    size_t original_size = source.Size();
    target = std::move(source);
    
    EXPECT_EQ(target.Size(), original_size);
    EXPECT_EQ(source.Size(), 0);
}

// Тесты для копирования
TEST(ArrayCopyTest, CopyConstructor) {
    Array<int> original;
    original.Add(1);
    original.Add(2);
    original.Add(3);
    
    Array<int> copy(original);
    
    EXPECT_EQ(original.Size(), copy.Size());
    for (size_t i = 0; i < original.Size(); ++i) {
        EXPECT_EQ(original.Get(i), copy.Get(i));
    }
}

TEST(ArrayCopyTest, CopyAssignment) {
    Array<int> original;
    Array<int> copy;
    
    original.Add(10);
    original.Add(20);
    
    copy = original;
    
    EXPECT_EQ(original.Size(), copy.Size());
    for (size_t i = 0; i < original.Size(); ++i) {
        EXPECT_EQ(original.Get(i), copy.Get(i));
    }
}

// Тест на увеличение capacity
TEST(ArrayCapacityTest, ResizeBehavior) {
    Array<int> array;
    size_t initial_capacity = array.Capacity();
    
    // Добавляем больше элементов чем начальная capacity
    for (int i = 0; i < 20; ++i) {
        array.Add(i);
    }
    
    EXPECT_GT(array.Capacity(), initial_capacity);
    EXPECT_EQ(array.Size(), 20);
}

// Тест на исключения
TEST(ArrayExceptionTest, OutOfRangeAccess) {
    Array<int> array;
    array.Add(42);
    
    EXPECT_THROW(array.Get(1), std::out_of_range);
    EXPECT_THROW(array.Remove(5), std::out_of_range);
}

TEST(ArrayIOTest, PrintAll) {
    Array<std::shared_ptr<Figure<double>>> array;
    
    auto triangle = std::make_shared<Triangle<double>>(
        Point<double>{0, 0}, Point<double>{1, 0}, Point<double>{0, 1}
    );
    
    array.Add(triangle);
    
    std::stringstream ss;
    array.PrintAll(ss);
    
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    
    // Сначала проверим что PrintAll работает
    EXPECT_NE(output.find("Item 0:"), std::string::npos);
    
    // Затем отдельно проверим вывод самой фигуры
    std::stringstream triangle_ss;
    triangle->Print(triangle_ss);
    std::string triangle_output = triangle_ss.str();
    
    // Проверим что треугольник выводит "Triangle"
    EXPECT_NE(triangle_output.find("Triangle"), std::string::npos);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}