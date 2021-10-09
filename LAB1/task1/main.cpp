#include <iostream>
#include <vector>
#include <cstdarg>
#include <fstream>
#include <string>

std::vector<int> search_substr(const std::string& s) {
    std::vector<int> pi(s.length(), 0);
    for (int i = 1; i < s.length(); i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            pi[i] = j + 1;
        } else {
            pi[i] = j;
        }
    }
    return pi;
}

int search_substring_in_files(std::vector<int> (*fcnPtr)(const std::string&), const char* substr, int count_paths...)
{
    va_list file_paths;
    va_start(file_paths, count_paths);
    auto *file_names = new std::string[count_paths];
    int k = 0;

    for (int i = 0; i < count_paths; i++)
    {
        char* path = va_arg(file_paths, char*);

        std::ifstream inf(path);
        if (!inf)
        {
            std::cerr << "could not be opened for reading!" << std::endl;
            exit(1);
        }

        std::string buffer;
        std::string substring(substr);
        while(getline(inf, buffer))
        {
            std::vector<int> pi = fcnPtr(substring + "#" + buffer);
            size_t substr_len = substring.length();

            for (size_t j = 0; j < buffer.length(); j++) {
                if (pi[substr_len + 1 + j] == substr_len) {
                    std::cout << "string[" << j - substr_len + 1 << ".." << j << "] = substring in file: " << path << std::endl;
                }
            }
        }
        inf.close();
    }

    for (int i = 0; i <= k; i++)
        std::cout << file_names[i] << std::endl;

    delete [] file_names;
    va_end(file_paths);

    return 0;
}

int main() {
    search_substring_in_files(search_substr, "12", 4, "1.txt", "2.txt", "3.txt", "4.txt");

    return 0;
}



