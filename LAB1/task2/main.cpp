#include <iostream>
#include <cstdarg>
#include <cmath>

#define CONCAVE -1 // вогнутый
#define CONVEX 1 // выпуклый

struct Point {
    int x;
    int y;
};

int isConvex(Point *p,int n);
int is_convex_polygon(int count_points, ...);

int main() {

    Point p1 = {0, 1};
    Point p2 = {0, 0};
    Point p3 = {1, 0};
    Point p4 = {-1, -1};

    Point p11 = {0, 2};
    Point p12 = {2, 0};
    Point p13 = {0, -2};
    Point p14 = {-2, 0};


    is_convex_polygon(4, p1, p2, p3, p4);
    is_convex_polygon(4, p11, p12, p13, p14);
    return 0;
}

int is_convex_polygon(int count_points, ...)
{
    va_list point;
    va_start(point, count_points);
    auto *points = new Point[count_points];

    for (int i = 0; i < count_points; i++)
    {
        points[i] = va_arg(point, Point);
    }

    std::cout << isConvex(points, count_points) << std::endl;

    delete [] points;
    return 0;
}

// Многоугольник будет выпуклым, если для векторов, составляющих его периметр, выполняется условие:
// векторные произведения соседних векторов должны иметь одинаковый знак

int isConvex(Point *p, int n)
{
    double x1, x2;
    if (n < 4)
        return 1;

    for (int i = 0; i < n - 1; i++){
        x1 = p[i].x * p[i + 1].y - p[i + 1].x * p[i].y;
        x1 /= fabs(x1); // вычисляем знак векторного умножения
        x2 = p[i + 1].x * p[i + 2].y - p[i + 2].x * p[i + 1].y;
        x2 /= fabs(x2);
        if (x1 != x2)
            return 0; // вогнутый
    }
    return 1; // выпуклый
}