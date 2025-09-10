#include <string.h>

void rev(char *s) {
    int i = 0, j = (int)strlen(s) - 1;
    while (i < j) {
        char t = s[i]; s[i] = s[j]; s[j] = t;
        i++; j--;
    }
}
