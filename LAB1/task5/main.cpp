#include <iostream>
#include <cstring>
#include <cstdarg>

class StringNumber{
private:
    char* str_number;
    int base;
public:
    StringNumber(char* str, int base){
        this->str_number = str;
        this->base = base;
    }

    StringNumber(int len, int base){
        this->str_number = (char* ) malloc(sizeof(char) * (len));
        memset(this->str_number, ' ', len);
        this->str_number[len] = '\0';
        this->base = base;
    }
    ~StringNumber(){
        free(this->str_number);
    }
    StringNumber (const StringNumber &number){
        size_t len = strlen(number.str_number);
        this->str_number = (char* ) malloc(sizeof(char) * len);
        for (size_t i = 0; i < len; ++i) {
            this->str_number[i] = number.str_number[i];
        }
        this->base = number.base;
    }

    StringNumber operator = (const StringNumber &number){
        size_t len = strlen(number.str_number);
        this->str_number = (char* ) malloc(sizeof(char) * len);
        for (size_t i = 0; i < len; ++i) {
            this->str_number[i] = number.str_number[i];
        }
        this->base = number.base;
        return *this;
    }

    friend StringNumber operator + (StringNumber &number1, const StringNumber &number2){

        int len_n1 = std::strlen(number1.str_number);
        int len_n2 = std::strlen(number2.str_number);
        int len_n3 = (len_n1 > len_n2) ? len_n1 + 1: len_n2 + 1;

        StringNumber number3(len_n3, number1.base);

        int carry = 0;
        for (int i = 1; i <= len_n3; i++) {
            int last_digit_1 = (i > len_n1) ? 0 : (isdigit(number1.str_number[len_n1 - i]) ? number1.str_number[len_n1 - i] - '0' : toupper(number1.str_number[len_n1 - i]) - 'A' + 10);
            int last_digit_2 = (i > len_n2) ? 0 : (isdigit(number2.str_number[len_n2 - i]) ? number2.str_number[len_n2 - i] - '0' : toupper(number2.str_number[len_n2 - i]) - 'A' + 10);
            int last_res_digit = last_digit_1 + last_digit_2 + carry;
            number3.str_number[len_n3 - i] = (last_res_digit % number1.base > 9) ? last_res_digit % number1.base + 'A' - 10 : last_res_digit % number1.base + '0';
            carry = (last_res_digit / number1.base);
        }

        return number3;
    }

    friend std::ostream& operator<< (std::ostream &out, const StringNumber &number) {
        int i = 0;
        while (number.str_number[i] == '0')
            i++;
        for (; i < strlen(number.str_number); ++i) {
                out << number.str_number[i];
        }
        out << "_" << number.base << std::endl;
        return out;
    }
};

void sum(const char* number1, const char* number2, int base) {
    int len_n1 = strlen(number1);
    int len_n2 = strlen(number2);
    int len_n3 = (len_n1 >= len_n2) ? len_n1 + 1: len_n2 + 1;
    char* number3 = (char* ) malloc(sizeof(char) * (len_n3));
    memset(number3, ' ', len_n3);
    number3[len_n3] = '\0';
    int carry = 0;
    for (int i = 1; i <= len_n3; i++) {
        int last_digit_1 = (i > len_n1) ? 0 : (isdigit(number1[len_n1 - i]) ? number1[len_n1 - i] - '0' : toupper(number1[len_n1 - i]) - 'A' + 10);
        int last_digit_2 = (i > len_n2) ? 0 : (isdigit(number2[len_n2 - i]) ? number2[len_n2 - i] - '0' : toupper(number2[len_n2 - i]) - 'A' + 10);
        int last_res_digit = last_digit_1 + last_digit_2 + carry;
        number3[len_n3 - i] = (last_res_digit % base > 9) ? last_res_digit % base + 'A' - 10 : last_res_digit % base + '0';
        carry = (last_res_digit / base);
    }
    std::cout << number3 << std::endl;
    free(number3);
}

void add(StringNumber &n1, StringNumber &n2, int base, int count_number, ...){
    va_list numbers;
    va_start(numbers, count_number);
    StringNumber result = n1 + n2;
    for (int i = 0; i < count_number; i++) {
        result = result + *va_arg(numbers, StringNumber*);
    }
    va_end(numbers);
    std::cout << "----" << result << std::endl;
}

int main() {
    StringNumber C("111", 2);
    StringNumber B("111", 2);
    StringNumber A("111", 2);
    add(A, B, 2, 1, &C);
    return 0;
}