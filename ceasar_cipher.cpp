#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int k;
    char m[128], c[128];
    scanf("%s", m);
    scanf("%d", &k);
    strcpy(c, m);
    for (int i = 0; c[i]; i++) {
        if ('a' > (c[i] | (1<<5)) or (c[i] | (1<<5)) > 'z') continue;
        char b = 'A' | ((1<<5) & c[i]);
        c[i] = (c[i] - b + 26 + k) % 26 + b; 
    }
    puts(c);
}