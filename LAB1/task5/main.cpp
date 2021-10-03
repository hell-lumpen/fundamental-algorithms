#include <iostream>
#include <cstring>

void sum(const char* n1, const char* n2, int base) {
    char *n3;
    int len_n1 = strlen(n1);
    int len_n2 = strlen(n2);
    int len_n3 = (len_n1 > len_n2) ? len_n1 : len_n2;
    len_n3 ++;
    n3 = (char *) malloc(len_n3 + 1);
    memset(n3, ' ', len_n3);
    n3[len_n3] = '\0';
    int z = 0;  // В уме
    for (int i=1; i <= len_n3; i++) {
        int a1 = (i > len_n1) ? 0 : (isdigit(n1[len_n1 - i]) ? n1[len_n1 - i] - '0' : toupper(n1[len_n1 - i]) - 'A' + 10);
        int b1 = (i > len_n2) ? 0 : (isdigit(n2[len_n2 - i]) ? n2[len_n2 - i] - '0' : toupper(n2[len_n2 - i]) - 'A' + 10);
        int c1 = a1 + b1 + z;
        n3[len_n3 - i] = (c1 % base > 9) ? c1 % base + 'A' - 10 : c1 % base + '0';
        std::cout << c1 % base << std::endl;
        z = (c1 / base);
    }
    std::cout << n3 << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    sum("2bcdef", "5edcbaa", 16);
    return 0;
}
