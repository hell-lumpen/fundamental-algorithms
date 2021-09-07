#include <iostream>
#include <cstdarg>
#include <cmath>


int polynomial_value(int x, int n, ...);

int main() {
    polynomial_value(3, 2, 3, 2, 3);
    return 0;
}

int polynomial_value(int x, int n, ...)
{
    va_list ratio;
    va_start(ratio, n);
    int result = 0;
    for (int i = 0; i < n + 1; i++)
    {
        result += pow(x, n - i) * va_arg(ratio, int);
    }
    va_end(ratio);
    std::cout << result << std::endl;
    return 0;
}