#include <stdint.h>

namespace task{
    typedef void (*function_ptr_t)();


    __attribute__((packed)) struct task{
        uint32_t    eax, //offset
                    ebx, //4
                    ecx, //8
                    edx, //12
                    esi, //16
                    edi, //20
                    esp, //24
                    ebp, //28
                    eip, //32
                    eflags, //36
                    cr3; //40
        bool initialized = false;
        bool ended = false;
        uint64_t slice_started = 0;
        uint64_t sleep_end = 0;
    }typedef task_t;

    task_t *create(function_ptr_t function_ptr);
    uint32_t add(task_t *task);
    void update_current(task_t *current);
    void schedule();
    void enable();
    void sleep(int time); //For now time is not indicative of real time
}

extern "C" void task_switch(uint32_t esp);
extern "C" void task_start(task::task_t * state);
extern "C" task::task_t *get_cpu_state();
extern "C" void set_cpu_state(task::task_t *state);
