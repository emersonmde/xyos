#ifndef __TASK_H__
#define __TASK_H__

#include <stdint.h>

extern void initMultitasking();

typedef struct {
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} Registers;

typedef struct Task {
    Registers regs;
    struct Task *next;
} Task;
 
extern void createTask(Task*, void(*)(), uint32_t, uint32_t*);
extern void yield(); // Switch task frontend
extern void switchTask(Registers *, Registers *);



#endif /* __TASK_H__ */