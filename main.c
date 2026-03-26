#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <cpuid.h>

int rdtsc(){
    int time;
    asm ("xor %0, %0\n\t"
        "cpuid\n\t"
        "rdtsc\n\t"
        "add %0, %%edx"
        : "=r" (time) 
        : "r" (time)
        : "%edx"
    );
    return time;
}


int measure_timing_access(int *a){
    int Clock1 = rdtsc();
    *a = *a +1 ;
    int Clock2 = rdtsc();
    printf("Clock1 : %d\n",Clock1);
    printf("Clock2 : %d\n",Clock2);
    return Clock2-Clock1;
}

int main(){
    int *a = malloc(sizeof(int));
    *a = 1;
    assert(a != NULL);
    // for(int i = 0; i < 100; i++){
    //     *a = *a +1;
    // }
    printf("timing access : %d \n",measure_timing_access(a));
    printf("%d", rdtsc());
    return 0;
}