#include <iostream>
#include <crypt.h>
#include <string>
#include <cstdio>
#include <cstring>

#define MIN_ASCII 32
#define MAX_ASCII 126

bool increase(std::string *bruteforce, unsigned long index, char min, char max) {
    if (index == (*bruteforce).length()) {
        (*bruteforce).push_back((char) MIN_ASCII);
        return false;
    }
    if ((*bruteforce)[index] == max) {
        (*bruteforce)[index] = min;
        return increase(bruteforce, index + 1, MIN_ASCII, MAX_ASCII);
    }
    (*bruteforce)[index] += 1;
    return false;
}

int bruteforce_with_salt(std::string *salt, char *hash) {
    char *res = NULL;
    const char *csalt = (*salt).c_str();
    std::string bruteforce;

    while (!increase(&bruteforce, 0, MIN_ASCII, MAX_ASCII)) {
        res = crypt(bruteforce.c_str(), csalt);
        if (res == NULL) {
            std::cerr << "Error while hashing the password!" << std::endl;
            return 84;
        }
        if (strcmp(res, hash) == 0)
            break;
    }
    std::cout << "RES: [" << bruteforce << "]" << std::endl;
    return 0;
}

int main(int argc, char **argv) {
    char *hash = NULL;
    std::string salt;
    int last_dollar_char = -1;

    if (argc != 2) {
        std::cout << "Invalid number of arguments!" << std::endl;
        return 84;
    }
    hash = argv[1];
    last_dollar_char = std::string(hash).rfind('$');
    salt = std::string(hash).substr(0, last_dollar_char);
    bruteforce_with_salt(&salt, hash);
    return 0;
}
