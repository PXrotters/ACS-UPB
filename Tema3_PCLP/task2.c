#define zero 0
#define mone -1
#define one 1
#define hdr 100
#include <stdio.h>
#include <string.h>
int main() {
    unsigned int N, i, j, cpyN;
    char s[hdr];
    float v[hdr], result = zero;
    scanf("%u",&N);
    cpyN = N;
    for(i = zero; i < N; i++) {
        scanf("%f",&v[i]);
    }
    scanf("%s",s);
    i = zero;
    while(i < strlen(s)) {
        if(s[i] == '*') {
            v[i] = v[i] * v[i + one];
            printf("v[i]=%f\t",v[i]);
            for (j = i + one; j < cpyN - one; j++) {
                v[j] = v[j + one];
            }
            cpyN--;
            strcpy(s + i, s + i + one);
            i = mone;
        } else if(s[i] == '/') {
            v[i] = v[i] / v[i + one];
             printf("v[i]=%f\t",v[i]);
            for (j = i + one; j < cpyN - one; j++) {
                v[j] = v[j + one];
            }
            cpyN--;
            strcpy(s + i, s + i + one);
            i = mone;
        }
        i++;
    }
    i = zero;
    while(i < strlen(s)) {
        if(s[i] == '+') {
            v[i] = v[i] + v[i + one];
            printf("v[i]=%f\t",v[i]);
            for (j = i + one; j < cpyN - one; j++) {
                v[j] = v[j + one];
            }
            cpyN--;
            strcpy(s + i, s + i + one);
            i = mone;
        } else  if(s[i] == '-') {
            v[i] = v[i] - v[i + one];
            printf("v[i]=%f\t",v[i]);
            for (j = i + one; j < cpyN - one; j++) {
                v[j] = v[j + one];
            }
            cpyN--;
            strcpy(s + i, s + i + one);
            i = mone;
        }
        i++;
    }
    result = v[zero];
    printf("%f\n",result);
    return 0;
}
