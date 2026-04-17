#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../utils.h"


int measure_timing_access(int *a){
    // measure the number of cpu cycle to access and increment the value of a 
    int Clock1 = rdtsc();
    *a = *a +1 ;
    int Clock2 = rdtsc();

    return Clock2-Clock1;
}

int measure_cache_hit(){
    // measure the time if a pointer a is in the cache 
    int *a = malloc(sizeof(int));
    *a = 1;
    assert(a != NULL);

    clflush(a);
    for(int i = 0; i < 100; i++){
        *a = *a +1; // for loop to put the pointer a in the cache 
    }

    int time = measure_timing_access(a);
    free(a);
    return time; 
}

int main(int argc, char*argv[]){
    if(argc > 1){

        if (strcmp(argv[1], "cache") == 0){
            FILE* f = fopen("./access_cache_hit.csv", "w");
            fprintf(f, "time\n");

            for(int i = 0; i < 10000; i++){
                fprintf(f, "%d\n",measure_cache_hit());
            }

            fclose(f);
        }
        else{
            if(strcmp(argv[1], "single")== 0){
                FILE* f = fopen("./access_single.csv", "w");
                fprintf(f, "time\n");
            
                for(int i = 0; i < 10000; i++){
                    int *a = malloc(sizeof(int));
                    assert(a != NULL);
                    *a = 1;

                    clflush(a);
                    fprintf(f, "%d\n",measure_timing_access(a));

                    free(a);
                }

                fclose(f);
            }
            else{
                printf("Please enter a measure time access mode.\n");
                printf("Please enter \"cache\" to get a time access for a pointer in the cache.\n");
                printf("Please enter \"single\" to get a time access for a pointer access only one time.\n");
            }
        }
    }
    else{
        printf("Please enter a measure time access mode.\n");
        printf("Please enter \"cache\" to get a time access for a pointer in the cache.\n");
        printf("Please enter \"single\" to get a time access for a pointer access only one time.\n");
    }

    return 0;
}