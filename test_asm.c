#include <stdio.h>

int main(){
    int dst= 1;   

    asm ("xor %0, %0\n\t"
        "cpuid\n\t"
        "rdtsc\n\t"
        "add %0, %%eax"
        : "=r" (dst) 
        : "r" (dst)
        : "%eax"
    );

    printf("%d\n", dst);
}