#include <string.h>

int strcmp(const char* lhs, const char* rhs) {
    while(*lhs && (*lhs == *rhs))
    {
        lhs++;
        rhs++;
    }
    return *(const unsigned char*)lhs - *(const unsigned char*)rhs;
}
