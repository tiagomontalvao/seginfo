#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    char m[128], k[128], c[128];
    scanf("%s", m);
    scanf("%s", k);
    strcpy(c, m);
    int kk = strlen(k);
    for (int i = 0; c[i]; i++) {
        if ('a' > (c[i] | (1<<5)) or (c[i] | (1<<5)) > 'z') continue;
        char b = 'A' | ((1<<5) & c[i]);
        int inc = k[i%kk] - ('A' | ((1<<5) & k[i%kk]));
        c[i] = (c[i] - b + 26 + inc) % 26 + b; 
    }
    puts(c);
}