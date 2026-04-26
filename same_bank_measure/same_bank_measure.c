#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define LENGTH_TAB 500000

int rdtsc(){
    // Call rdtsc assembly command with a barrier assure by the command cpuid
    // Return the actual number of cpu cycle of the machine code
    int time;
    asm("xor %0, %0\n\t"
        // "cpuid\n\t"
        "mfence\n\t"
        "rdtsc\n\t"
        "add %0, %%edx"
        : "=r" (time) 
        : "r" (time)
        : "%edx"
    );
    return time;
}

int measure_access_two_values(int * tab, int i, int j){
    // measure the time to access the value of tab[i] and the value of tab[j]
    // one after another, and flush the two value after
    
    void* value1 = &tab[i];
    void* value2 = &tab[j];
    asm("clflush 0(%0)\n\t"
        "clflush 0(%1)"
        ::"r" (value1), "r" (value2)
        : "rax"
    );

    
    int clock1, clock2;

    clock1 = rdtsc();

    tab[i] = tab[i] +1;

    tab[j] = tab[j] +1;

    clock2 = rdtsc();


    return clock2-clock1;
}

int main(){
    // We want to measure the difference of time to access two addresses 
    // if these addresses are in the same memory bank or not
    // We take two addresses that are not in the same page 
    // so 4096 addresses after 

    int *tab = malloc(LENGTH_TAB*4096*sizeof(int));
    assert(tab != NULL);

    FILE * f = fopen("./access_two_value.csv", "w");

    for(int j = 0; j < LENGTH_TAB; j++){
        
        for(int r = 0; r < 100; r ++){
            fprintf(f, "%d, ", measure_access_two_values(tab, 0, j*4096+1));
        }
        fprintf(f, "%d\n", measure_access_two_values(tab, 0, j*4096+1));
    }

    free(tab);

    return 0;
}