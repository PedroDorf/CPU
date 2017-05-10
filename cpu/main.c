#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "instruction_list.h"
#include <stdint.h>
#include <string.h>

/*TODO:
 * Implement reading files
 * Implement something with POSIX
 *
 */

int main(int argc, char *argv[]) {
    if (argc == 1 || argc > 3) {
        return 0;
    }
    char cmd[16];
    int arg = 0;
    struct cpu cpu;
    cpuInit(&cpu);
    int goal = 1;
    if (argc == 2) {
        if (strcmp(argv[1], "h") == 0) {
            printf("-h             Prints manual.\n");
            printf("-r <number>    After use of \"run\" command program will run only number of commands or until the end.\n");
            printf("-R             After use of \"run\" command program will run every valid command written.\n");
            cpuClear(&cpu);
            return 0;
        }
        while (1) {
            printf("> ");
            scanf("%s",cmd);
            struct instruction *inst = malloc(sizeof(struct instruction));
            inst->next = NULL;
            inst->prev = NULL;
            inst->arg = 0;
            //Could have been done easily w/ Switch but I was too far into it
            if (strcmp(cmd,"nop") == 0) {
                inst->type = InstNop;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"mova") == 0) {
                inst->type = InstMova;
                scanf("%d",&arg);
                inst->arg = arg;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"add") == 0) {
                inst->type = InstAdd;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"sub") == 0) {
                inst->type = InstSub;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"div") == 0) {
                inst->type = InstDiv;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"mul") == 0) {
                inst->type = InstMul;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"load") == 0) {
                inst->type = InstLoad;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"swac") == 0) {
                inst->type = InstSwac;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"swab") == 0) {
                inst->type = InstSwab;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"inc") == 0) {
                inst->type = InstInc;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"dec") == 0) {
                inst->type = InstDec;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"push") == 0) {
                inst->type = InstPush;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"pop") == 0) {
                inst->type = InstPop;
                listPush(&cpu.programList,inst);
            } else if (strcmp(cmd,"run") == 0) {
                while (goal != 0) {
                    goal = cpuStep(&cpu);
                }
                cpuDebug(&cpu);
                goal = 1;
            } else if (strcmp(cmd,"halt") == 0) {
                break;
            }
        }
        cpuClear(&cpu);
    }
    if (strcmp(argv[1], "r") == 0) {
        goal = 1;
        while (1) {
        int inst_num = atoi(argv[2]);
        printf("> ");
        scanf("%s",cmd);
        struct instruction *inst = malloc(sizeof(struct instruction));
        inst->next = NULL;
        inst->prev = NULL;
        inst->arg = 0;
        //Could have been done easily w/ Switch but I was too far into it
        if (strcmp(cmd,"nop") == 0) {
            inst->type = InstNop;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"mova") == 0) {
            inst->type = InstMova;
            scanf("%d",&arg);
            inst->arg = arg;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"add") == 0) {
            inst->type = InstAdd;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"sub") == 0) {
            inst->type = InstSub;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"div") == 0) {
            inst->type = InstDiv;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"mul") == 0) {
            inst->type = InstMul;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"load") == 0) {
            inst->type = InstLoad;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"swac") == 0) {
            inst->type = InstSwac;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"swab") == 0) {
            inst->type = InstSwab;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"inc") == 0) {
            inst->type = InstInc;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"dec") == 0) {
            inst->type = InstDec;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"push") == 0) {
            inst->type = InstPush;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"pop") == 0) {
            inst->type = InstPop;
            listPush(&cpu.programList,inst);
        } else if (strcmp(cmd,"run") == 0) {
            while (inst_num != 0) {
                goal = cpuStep(&cpu);
                if (goal == 0){
                    inst_num = 1;
                }
                inst_num--;
            }
            cpuDebug(&cpu);
            goal = 1;

        } else if (strcmp(cmd,"halt") == 0) {
            break;
        }
        }
        cpuClear(&cpu);
    }
    return 0;
}
