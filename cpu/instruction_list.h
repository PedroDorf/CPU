#include <stdint.h>
#include <stdlib.h>
#ifndef INSTRUCTIONLIST_H
#define INSTRUCTIONLIST_H

enum instructionType {
    InstNop,
    InstAdd,
    InstSub,
    InstDiv,
    InstMul,
    InstMova,
    InstLoad,
    InstSwac,
    InstSwab,
    InstInc,
    InstDec,
    InstPush,
    InstPop
};

struct instruction {
    struct instruction* next;
    struct instruction* prev;
    enum instructionType type;
    int arg;
};

struct instructionList {
    struct instruction* end;
    struct instruction* current;
};

unsigned int listNum(struct instructionList* container);

void listInit(struct instructionList* container);

unsigned int listClear(struct instructionList* container);

void listPush(struct instructionList* container, struct instruction* item);

const struct instruction * listStep(struct instructionList* container);

const struct instruction * listBackstep(struct instructionList* container);

int listEmpty(const struct instructionList* container);

#endif
