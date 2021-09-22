#include <iostream>
#include <cstdarg>
#include <fstream>

int search_substr(const char* string, const char* substring);
int search_substring_in_files(int (*fcnPtr)(const char*, const char*), const char* substr, int count_paths...);


int main() {
    search_substring_in_files(search_substr, "12", 4, "1.txt", "2.txt", "3.txt", "4.txt");
    return 0;
}

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

int search_substring_in_files(int (*fcnPtr)(const char*, const char*), const char* substr, int count_paths...)
{
    va_list file_paths;
    va_start(file_paths, count_paths);

    for (int i = 0; i < count_paths; i++)
    {
        char* path = va_arg(file_paths, char*);
        std::ifstream inf(path);
        if (!inf)
        {
            std::cerr << "Uh oh, could not be opened for reading!" << std::endl;
            exit(1);
        }
        std::string buffer;
        while(getline(inf, buffer))
        {
            if (fcnPtr(buffer.c_str(), substr))
                std::cout << path << std::endl;
        }
        inf.close();
    }

    va_end(file_paths);
    
    return 0;
}