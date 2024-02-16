#define zero 0
#define mone -1
#define one 1
#define hdr 100
#include <stdio.h>
#include <string.h>

void sir(char *s2, unsigned int i) {
    unsigned int j = zero;
    for (j = i; j < strlen(s2); j++) {
        s2[j] = s2[j + 1];
    }
}

int main() {
    unsigned int N = zero, i = zero, j = zero, cpyN = zero;
    float v[hdr], result = zero;
    scanf("%u", &N);
    cpyN = N;
    for (i = zero; i < N; i++) {
        scanf("%f", &v[i]);
    }
    char s[N];
    scanf("%s", s);
    i = zero;
    while (i < strlen(s)) {
        if (s[i] == '*') {
            v[i] = v[i] * v[i + one];
            for (j = i + one; j < cpyN - one; j++) {
                v[j] = v[j + one];
            }
            cpyN--;
            sir(s, i);
            i = mone;
        } else if (s[i] == '/') {
            v[i] = v[i] / v[i + one];
            for (j = i + one; j < cpyN - one; j++) {
                v[j] = v[j + one];
            }
            cpyN--;
            sir(s, i);
            i = mone;
        }
        i++;
    }
    i = zero;
    while (i < strlen(s)) {
        if (s[i] == '+') {
            v[i] = v[i] + v[i + one];
            for (j = i + one; j < cpyN - one; j++) {
                v[j] = v[j + one];
            }
            cpyN--;
           sir(s, i);
            i = mone;
        } else if (s[i] == '-') {
            v[i] = v[i] - v[i + one];
            for (j = i + one; j < cpyN - one; j++) {
                v[j] = v[j + one];
            }
            cpyN--;
            sir(s, i);
            i = mone;
        }
        i++;
    }
    result = v[zero];
    printf("%f\n", result);
    return 0;
}
