#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "instruction_list.h"
#include <stdint.h>
#include <assert.h>

void stackInit(struct stack* stack) {
    if (!stack) {
        printf("ERROR Stack pointer is NULL.\n");
        return;
    }
    stack->top = NULL;
    if (!(stack->values = malloc(2048))){
        printf("ERROR could not alloc wanted memory.\nPlease restart program.\n");
    }
    return;
}

void stackClear(struct stack* stack) {
    if (stack == NULL) {
        printf("ERROR Stack pointer is NULL.\n");
        return;
    }
    
    free(stack->values);
    stack->top = NULL;
    stack->values = NULL;
    return;
}

void stackPush(struct stack* stack, int32_t cpu_register) {
    if (stack == NULL) {
        printf("ERROR Stack pointer is NULL.\n");
        return;
    }

    if (stack->top == stack->values + 2047) {
        printf("ERROR Stack is full.\n");
        return;
    }

    if (stack->top == NULL) {
        stack->top = stack->values;
        *(stack->top) = cpu_register;
        return;
    }
    stack->top++;
    *(stack->top) = cpu_register;
    return;
}

//Normal stack pop except it doesn't return popped value
void stackPop(struct stack* stack) {
    if (stack == NULL) {
        printf("ERROR Stack pointer is NULL.\n");
        return;
    }
    if (stack->top == NULL) {
        //printf("WARNING Stack is empty.\n");
        return;
    }
    if (stack->top == stack->values) {
        stack->top = NULL;
        return;
    }

    stack->top--;
    return;
}

void cpuInit (struct cpu* cpu) {
    if (cpu == NULL) {
        return;
    }
    
    listInit(&cpu->programList);
    stackInit(&cpu->memory);
    cpu->registers[0] = 0;
    cpu->registers[1] = 0;
    cpu->registers[2] = 0;
    return;
}

void cpuClear (struct cpu* cpu) {
    if (cpu == NULL) {
        printf("ERROR CPU pointer is NULL.\n");
        return;
    }

    stackClear(&cpu->memory);
    listClear(&cpu->programList);
    cpu->registers[0] = 0;
    cpu->registers[1] = 0;
    cpu->registers[2] = 0;
    return;
}

int cpuStep(struct cpu* cpu) {
    if (!cpu) {
        printf("ERROR CPU pointer is NULL.\n");
        return 0;
    }
    int32_t tmp;
    const struct instruction *step = listStep(&cpu->programList);
    if (step == NULL) {
        return 0;
    }
    switch (step->type) {
    case InstNop:
        break;
    case InstAdd:
        cpu->registers[0] = cpu->registers[0] + cpu->registers[2];
        break;
    case InstSub:
        cpu->registers[0] = cpu->registers[0] - cpu->registers[2];
        break;
    case InstDiv:
        if (cpu->registers[2] == 0){
            return 0;
        }
        cpu->registers[0] = cpu->registers[0] / cpu->registers[2];
        break;
    case InstMul:
        cpu->registers[0] = cpu->registers[0] * cpu->registers[2];
        break;
    case InstMova:
        cpu->registers[0] = step->arg;
        break;
    case InstLoad:
        assert(cpu->memory.top != NULL);
        assert(cpu->memory.top - cpu->registers[1] >= cpu->memory.values);
        cpu->registers[0] = *(cpu->memory.top - cpu->registers[1]);
        break;
    case InstSwac:
        tmp = cpu->registers[0];
        cpu->registers[0] = cpu->registers[2];
        cpu->registers[2] = tmp;
        break;
    case InstSwab:
        tmp = cpu->registers[0];
        cpu->registers[0] = cpu->registers[1];
        cpu->registers[1] = tmp;
        break;
    case InstInc:
        cpu->registers[0] = cpu->registers[0] + 1;
        break;
    case InstDec:
        cpu->registers[0] = cpu->registers[0] - 1;
        break;
    case InstPush:
        stackPush(&cpu->memory,cpu->registers[0]);
        break;
    case InstPop:
        stackPop(&cpu->memory);
        break;
    default:
        return 0;
        break; //Not sure if this has to be here
    }
    return 1;
}

//Prints out state of Registers and Stack
void cpuDebug(const struct cpu* cpu) {
    if (cpu == NULL) {
        printf("ERROR CPU pointer is NULL.\n");
        return;
    }
    printf("# Registers %d %d %d | Stack", cpu->registers[0], cpu->registers[1], cpu->registers[2]);
    if (cpu->memory.top == NULL){
            printf("\n");
            return;
        }
    for (int i = 0; cpu->memory.values + i <= cpu->memory.top ; i++) {
        printf(" %d", *(cpu->memory.values + i));
    }
    printf("\n");
    return;

}
