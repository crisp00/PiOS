#include "headers/task.hh"
#include "headers/heap.hh"
#include "headers/serial.hh"
#include "headers/pit.hh"
#include "../libh/stdlib.hh"

namespace task{
    static int n_tasks = 0;
    static int task_index = -1;
    bool enabled = 0;

    static task_t *tasks[100];

    task_t *create(function_ptr_t function_ptr){
        task_t *task = (task_t *)heap::mem_alloc(sizeof(task_t));
        task->eax = 0;
        task->ebx = 0;
        task->ecx = 0;
        task->edx = 0;
        task->esi = 0;
        task->edi = 0;
        task->ebp = 0;
        task->eflags = 0x202;
        task->ended = false;
        task->initialized = false;
        task->eip = (uint32_t)function_ptr;

        task->esp = (uint32_t)heap::mem_get_first_free_block() + 4092;
        *((int*)task->esp) = 0;

        return task;
    }

    uint32_t add(task_t *task){
        tasks[n_tasks] = task;
        n_tasks++;
        return n_tasks - 1;
    }

    void update_current(task_t *current){
        if(enabled && n_tasks > 0){
            task_t *cur = tasks[task_index];
            cur->esp = current->esp;
        }
    }

    static char tmp[100];
    uint64_t slice_time = 10;
    void schedule(){
        uint64_t millis = pit::millis();
        uint64_t slice_time_elapsed = millis - tasks[task_index]->slice_started;
        uint64_t sleep_end = tasks[task_index]->sleep_end;
        if(enabled && n_tasks > 0 && (slice_time_elapsed > slice_time || sleep_end >= millis)){
            int prev = task_index;
            do{
                task_index++;
            }while(tasks[task_index]->sleep_end >= millis && task_index < n_tasks);
            int i = 0;
            while(tasks[task_index]->sleep_end >= millis && task_index < prev){
                task_index = 0;
                i++;
            }
            if(task_index < 0 || task_index >= n_tasks){
                task_index = 0;
            }
            task_t *cur = tasks[task_index];
            serial::putstring("Switching task from ");
            serial::putstring(itoa(prev, tmp, 10));
            serial::putstring(" to ");
            serial::putstring(itoa(task_index, tmp, 10));
            serial::putstring("\n");
            serial::putstring("New EFLAGS: 0x");
            serial::putstring(itoa(cur->eflags, tmp, 16));
            serial::putstring("\n");
            cur->sleep_end = 0;
            if(!cur->initialized){
                serial::putstring("starting task\n");
                cur->initialized = true;
                cur->slice_started = pit::millis();
                task_start(cur);
            }else{
                serial::putstring("switching task\n");
                cur->slice_started = pit::millis();
                task_switch((uint32_t)cur->esp);
            }
        }
    }

    void enable(){
        enabled = true;
    }

    void sleep(uint64_t milliseconds){
        uint64_t sleep_end = pit::millis() + milliseconds;
        tasks[task_index]->sleep_end = sleep_end;
        asm("int $32");
        while(sleep_end > pit::millis()){
            asm("NOP");
        }
    }

}