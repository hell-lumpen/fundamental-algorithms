#include <iostream>
#include <cstdarg>

int search_substr(const char* string, const char* substring);

int main() {
    std::cout << search_substr("12345678", "1") << std::endl;
    int (*fcnPtr)(const char*, const char*) = search_substr;


    return 0;
}

int sum(int n, ...)
{
    int result = 0;
    va_list factor;         //указатель va_list
    va_start(factor, n);    // устанавливаем указатель
    for(int i=0;i<n; i++)
    {
        result += va_arg(factor, int);  // получаем значение текущего параметра типа int
    }
    va_end(factor); // завершаем обработку параметров
    return result;
}

//// поиск подстроки в строке

/*
int boo();
double doo();
int moo(int a);

// Присваивание значений указателям на функции
int (*fcnPtr1)() = boo; // ок
int (*fcnPtr2)() = doo; // не ок: тип указателя и тип возврата функции не совпадают!
double (*fcnPtr4)() = doo; // ок
fcnPtr1 = moo; // не ок: fcnPtr1 не имеет параметров, но moo() имеет
int (*fcnPtr3)(int) = moo; // ок
 */

int search_substr(const char* string, const char* substring)
{
    int i = 0, k = 0;
    while (*(string + i) != '\0'){
        if (*(string + i) == *(substring + k))
        {
            if ((*(substring + (++k)) == '\0'))
                return 1;
        }
        else
        {
            if ((*(substring + k) == '\0'))
                return 1;
            k = 0;
        }
        i++;
    }
    return 0;
}

int search_substring_in_files(char* (*fcnPtr)(const char*, const char*), ...)
{
    va_list file_paths;
    va_start(file_paths, fcnPtr);

    int count_paths = 3;
    for (int i = 0; i < count_paths; i++)
    {
        char* path = va_arg(file_paths, char*);

    }
    
    return 0;
}