#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <cpuid.h>

int rdtsc(){
    // Call rdtsc assembly command with a barrier assure by the command cpuid
    // Return the actual number cpu cycle of the machine code
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
    // measure the number of cpu cycle to access and increment the value of a 
    int Clock1 = rdtsc();
    *a = *a +1 ;
    int Clock2 = rdtsc();
    return Clock2-Clock1;
}

void measure_cache_hit(int *a){
    // measure the time if the pointer a is in the cache 
    for(int i = 0; i < 100; i++){
        *a = *a +1; // for loop to put the pointer a in the cache 
    }
    printf("timing access : %d \n",measure_timing_access(a));
}

int main(){
    int *a = malloc(sizeof(int));
    *a = 1;
    assert(a != NULL);

    measure_cache_hit(a);
    return 0;
}