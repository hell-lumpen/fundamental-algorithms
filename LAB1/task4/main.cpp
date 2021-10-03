#include <iostream>
#include <fstream>

int valid_symbol(char a)
{
    a = toupper(a);
    return ((a >= 'A' && a <= 'Z' || a >= '0' && a <= '9') ? 1 : 0);
}

int toTen(const char* num, int base) {
    int result = 0;
    int i = 0;
    while (*(num + i) != 0) {
        result = result * base + (isdigit(num[i]) ? num[i] - '0' : toupper(num[i]) - 'A' + 10);
        i++;
    }
    return result;
}

int count_base(char c, int base){
    int a = (isdigit(c) ? c - '0' : toupper(c) - 'A' + 10);
    a++;
    return (a > base) ? a : base;
}

int main() {
    std::ifstream file("1.txt");
    if (!file)
    {
        std::cerr << "Uh, could not be opened for reading!" << std::endl;
        exit(1);
    }

    std::ofstream outfile("out.txt");
    if (!file)
    {
        std::cerr << "Uh, could not be opened for reading!" << std::endl;
        exit(1);
    }

    outfile << "Converting a number to another number system.\nFormat: number_base\nExample: 11100011_2\n" << std::endl;

    std::string buffer;
    std::string number;
    while (getline(file, buffer))
    {
        std::string::const_iterator iter_buf;
        iter_buf = buffer.begin();
        int flag = 1, base = 0;
        while (iter_buf <= buffer.end()) {
            if (valid_symbol(*iter_buf) && flag){
                number.push_back(*iter_buf);
                base = count_base(*iter_buf, base);
            }
            if (!valid_symbol(*iter_buf) && *iter_buf != ' ' && *iter_buf != '\t' && iter_buf != buffer.end()){
                flag = 0;
                number.clear();
                base = 0;
                outfile << "invalid number" << std::endl;
            }
            if (*iter_buf == ' ' || *iter_buf == '\t' || iter_buf == buffer.end()){
                if (flag && !number.empty()) {
                    outfile << toTen(number.c_str(), base) << "_" << base << std::endl;
                    number.clear();
                    base = 0;
                }
                flag = 1;
            }
            iter_buf++;
        }
    }

    file.close();
    outfile.close();
    return 0;
}