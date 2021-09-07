#include <iostream>
#include <cstdarg>

#define CONCAVE -1
#define CONVEX 1

struct Point {
    int x;
    int y;
};

int isConvex(Point *p,int n);
int is_convex_polygon(int count_points, ...);

int main() {

    Point p1 = {0, 2};
    Point p2 = {2, 0};
    Point p3 = {0, -2};
    Point p4 = {-2, 0};

    Point p11 = {-2, 2};
    Point p12 = {0, 1};
    Point p13 = {2, 2};
    Point p14 = {0, -1};


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

int isConvex(Point *p,int n)
{
    int i,j,k;
    int flag = 0;
    double z;

    if (n < 3)
        return(0);

    for (i=0;i<n;i++) {
        j = (i + 1) % n;
        k = (i + 2) % n;
        z  = (p[j].x - p[i].x) * (p[k].y - p[j].y);
        z -= (p[j].y - p[i].y) * (p[k].x - p[j].x);
        if (z < 0)
            flag |= 1;
        else if (z > 0)
            flag |= 2;
        if (flag == 3)
            return(CONCAVE);
    }
    if (flag != 0)
        return(CONVEX);
    else
        return(0);
}