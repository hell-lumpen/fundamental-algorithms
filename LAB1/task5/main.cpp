#include <iostream>
#include <string>
#include <cstdarg>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;

int _to_number(char character) {
    if (character >= '0' && character <= '9') return (character - '0');
    if (character >= 'a' && character <= 'z') return (character - 'a' + 10);
    if (character >= 'A' && character <= 'Z') return (character - 'A' + 10);
    return -1;
}

char _to_char(int number) {
    if (number >= 0 && number <= 9) return (number + '0');
    else return (number + 'A' - 10);
}

void remove_leading_zeros(string &result) {
    while(result.size() > 1 && result.back() == '0')
        result.pop_back();
}

string sum(int base, string num_1, string num_2) {
    reverse(num_1.begin(), num_1.end());
    reverse(num_2.begin(), num_2.end());

    string result;

    int carry = 0;
    size_t index_1 = 0, index_2 = 0;

    for(; index_1 < num_1.length() && index_2 < num_2.length(); index_1++, index_2++) {
        auto digit_1 = _to_number(num_1[index_1]);
        auto digit_2 = _to_number(num_2[index_2]);
        if (digit_1 == -1 || digit_2 == -1) return "ERROR:\tundefined character in number";
        if (digit_1 + 1 > base || digit_2 + 1 > base) return "ERROR:\tincorrect number for the entered number system";
        result += _to_char((digit_1 + digit_2 + carry) % base);
        carry = (digit_1 + digit_2 + carry) / base;
    }

    for(;index_1 < num_1.length(); index_1++) {
        auto digit = _to_number(num_1[index_1]);
        if (digit == -1) return "ERROR:\tundefined character in number";
        if (digit + 1 > base) return "ERROR:\tincorrect number for the entered number system";
        result += _to_char((digit + carry) % base);
        carry = (digit + carry) / base;
    }

    for(;index_2 < num_2.length(); index_2++) {
        auto digit = _to_number(num_2[index_2]);
        if (digit == -1) return "ERROR:\tundefined character in number";
        if (digit + 1 > base) return "ERROR:\tincorrect number for the entered number system";
        result += _to_char((digit + carry) % base);
        carry = (digit + carry) / base;
    }

    if (carry != 0) result += _to_char(carry);

    remove_leading_zeros(result);

    reverse(result.begin(), result.end());
    return result;
}

string total_amount(int number_base, int numbers_amount, ...)
{
    va_list args;
    va_start(args, numbers_amount);
    string result = "0";
    if (number_base > 36) return string("ERROR:\tMax number number_base = 36!");
    for (int i = 0; i < numbers_amount; ++i) {
        result = sum(number_base, result, string(va_arg(args, char*)));
    }
    va_end(args);
    return result;
}

int main() {
    cout << total_amount(16, 2, "AAAAA", "10z0000") << endl;
    cout << total_amount(2, 3, "1000111", "10000000000000000000000000000000000000000001", "1") << endl;
    cout << total_amount(36, 3, "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZz", "11111111111111111111111111111111111111111111111111111", "0") << endl;
    return 0;
}
