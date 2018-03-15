#include <stdint.h>

namespace task{
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
    }typedef task_t;

    task_t *get_task(int index);
    void add_task();
}

extern "C" void task_switch(int32_t state);
extern "C" task::task_t *get_cpu_state();