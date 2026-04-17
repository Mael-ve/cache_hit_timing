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

void clflush(void * ptr){
    // flush the value of ptr
    asm("clflush 0(%0)"
        :: "r"(ptr)
        : "rax"
        );
}