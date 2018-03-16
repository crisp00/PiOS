section .text

global task_start
task_start: ; takes one parameter: a task structure
    mov eax, [esp + 4] ;task addr
    mov ebx, [eax + 36]
    mov [eflags_], ebx
    mov ebx, [eax + 24]
    mov [esp_], ebx
    mov ebx, [eax + 32]
    mov [eip_], ebx
    mov esp, [esp_]
    push dword [eflags_]
    push dword 8
    push dword [eip_]
    push 0
    push 0
    push 0
    push 0
    push 0
    push 0
    push 0
    push 16
    push 16
    push 16
    push 16
    push esp
    call task_switch

global task_switch
task_switch:    ;expexts esp of task as only parameter
    mov eax, [esp + 4]
    mov esp, eax
    pop gs
    pop fs
    pop es
    pop ds
    pop ebp
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    iret

task_esp dd 0,0

task_tmp:
    eax_ dd 0
    ebx_ dd 0
    ecx_ dd 0
    edx_ dd 0
    esi_ dd 0
    edi_ dd 0
    esp_ dd 0
    ebp_ dd 0
    eip_ dd 0
    eflags_ dd 0x202
    cr3_ dd 0
