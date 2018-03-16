#include "headers/task.hh"
#include "headers/heap.hh"
#include "headers/serial.hh"
#include "../libh/stdlib.hh"

namespace task{
    static int n_tasks = 0;
    static int task_index = 0;

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

        task->esp = (uint32_t)heap::mem_get_first_free_block() + 4095;

        return task;
    }

    uint32_t add(task_t *task){
        tasks[n_tasks] = task;
        n_tasks++;
        return n_tasks - 1;
    }

    void update_current(task_t *current){
        if(n_tasks > 0){
            task_t *cur = tasks[task_index];
            cur->esp = current->esp;
        }
    }

    static char tmp[100];
    void schedule(){
        if(n_tasks > 0){
            int prev = task_index;
            task_index++;
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
            if(!cur->initialized){
                serial::putstring("starting task\n");
                cur->initialized = true;
                task_start(cur);
            }else{
                serial::putstring("switching task\n");
                task_switch((uint32_t)cur->esp);
            }
        }
    }

}