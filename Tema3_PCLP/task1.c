#define zero 0
#define one 1
#define hdr 100
#include <stdio.h>
#include <string.h>
int main() {
    unsigned int N, i;
    char s[hdr];
    float v[hdr], result = zero;
    scanf("%u",&N);
    for(i = zero; i < N; i++) {
        scanf("%f",&v[i]);
    }
    result = v[zero];
    scanf("%s",s);
    for (i = zero; i < strlen(s); i++) {
        if(s[i] == '+') {
            result = result + v[i + one];
        } else if(s[i] == '*') {
                result = result * v[i + one];
            } else if(s[i] == '/') {
                    result = result / v[i + one];
                } else if(s[i] == '-') {
                    result = result - v[i + one];
                }
    }
    printf("%f\n",result);
    return 0;
}
