#include "instruction_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//Returns how many VALID instructins there are in container
unsigned int listNum(struct instructionList* container) {
    if (container == NULL) {
        return 0;
    }
    unsigned int i;
    container->current = container->end;
    for (i = 0; container->current->prev != NULL; i++){
        container->current = container->current->prev;
    }
    return i;
}

//Creates hold and initialise the container
void listInit(struct instructionList* container) {
    if (!container) {
        printf("ERROR Container pointer is NULL.\n");
        return;
    }

    struct instruction *hold = malloc(sizeof(struct instruction));
    container->end = hold;
    container->current = hold;
    container->end->prev = NULL;
    container->end->next = NULL;
    container->end->type = InstNop;
    container->end->arg = 0;

}

//Clears list
unsigned int listClear(struct instructionList* container) {
    if (container == NULL) {
        printf("ERROR Container pointer is NULL.\n");
        return 0;
    }
    int i = listEmpty(container);
    if (i == 1) {
        free(container->end);
        container->end = NULL;
        container->current = NULL;
        return 0;
    }
    unsigned int num = listNum(container);
    // call func for how many nodes is in list
    // while it puts current at the start
    for (; num != 0; num--) {
        container->current = container->current->next;
        free (container->current->prev);
    }
    //now container is empty except for hold
    free(container->end);
    container->end = NULL;
    container->current = NULL;
    return num;
}

//Pushes instruction into line/container
void listPush(struct instructionList* container, struct instruction* item) {
    if (!container) {
        printf("ERROR Container pointer is NULL.\n");
        return;
    }
    if (!item) {
        printf("ERROR Item pointer is NULL.\n");
        return;
    }
    item->next = container->end;
    if (container->end->prev == NULL) {
        container->end->prev = item;
        item->prev = NULL;
        container->current = item;
        return;
    }
    item->prev = container->end->prev;
    item->prev->next = item;
    container->end->prev = item;

    if (container->current == container->end) {
        container->current = container->end->prev;
    }
    return;
}

//"Steps fuurther" in cointainer
const struct instruction * listStep(struct instructionList* container) {
    if (!container) {
        printf("ERROR Container pointer is NULL.\n");
        return NULL;
    }

    if (container->end == container->current) {
        return NULL;
    }
    // if containner is empty returns NULL
    container->current = container->current->next;

    return container->current->prev;
}

//UNUSED
const struct instruction * listBackstep(struct instructionList* container) {
    if (container == NULL) {
        return NULL;
    }

    if (container->current->prev == NULL) {
        return NULL;
    }
    // if current is first instruction returns NULL

    struct instruction *step = container->current;
    container->current = container->current->prev;
    //remembers current but puts current onto prev node

    return step;
}

//SAYS if list is EMPTY
int listEmpty(const struct instructionList* container) {
    if (container == NULL) {
        return -1;
    }
    
    if (container->end->prev == NULL) {
        return 1;
    }
    
    return 0;
}
