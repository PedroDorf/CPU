#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
//why is here and \n "karel<eof>"

struct human {
    char *id;
    char *name;
    char *date;
    char *friends[256];
    int n_f;
};

int choose(char *id,struct human ppl[]) {
    for (int i = 0; ppl[i].id != NULL; ++i) {
        if (!strcmp(id,ppl[i].id)) {
            return i;
        }
    }
    return -1;
}

void addF(struct human person, char *line) {
    char *FD = malloc(64);
    for (int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == ':') {
            for (int j = 0; line[i + j + 1] != '\0'; ++j) {
                FD[j] = line[i + 1 + j];
                FD[j + 1] = '\0';
            }
            break;
        }
    }
    person.friends[person.n_f] = FD;
    person.n_f += 1;
    return;
}

void chooseNadd(struct human ppl[], char *line) {
    for (int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == '.') {
            if (line[i + 1] == 'b') {
                char *bday = malloc(64);
                char *id = malloc(64);
                for (int x = 0; line[x] != '.'; ++x) {
                    id[x] = line[x];
                    id[x + 1] = '\0';
                }
                int per = choose(id,ppl);
                free(id);
                id = NULL;
                for (int j = 0; line[i + 1 + j] != '\0'; ++j) {
                    bday[j] = line[i + j + 1];
                    bday[j + 1] = '\0';
                }
                ppl[per].date = bday;
            } else {
                char *id = malloc(64);
                for (int x = 0; line[x] != '.'; ++x) {
                    id[x] = line[x];
                    id[x + 1] = '\0';
                }
                int per = choose(id,ppl);
                free(id);
                id = NULL;
                addF(ppl[per],line);
            }
            break;
        }
    }
    return;
}

void freedom(struct human ppl[]) {
    for (int i = 0; ppl[i].id != NULL; ++i) {
        if (!ppl[i].id) {
            free(ppl[i].id);
            ppl[i].id = NULL;
        }
        if (!ppl[i].name) {
            free(ppl[i].name);
            ppl[i].name = NULL;
        }
        if (!ppl[i].date) {
            free(ppl[i].date);
            ppl[i].date = NULL;
        }
    }
}

void print(struct human ppl[]) {
    for (int i = 0; ppl[i].id != NULL; ++i) {
        printf("%s Date = %s Pratele(",ppl[i].name,ppl[i].date);
        for (int j = 0; ppl[i].friends[j] != NULL; ++j) {
            printf("%s",ppl[i].friends[j]);
            if (ppl[i].friends[j + 1] == NULL) {
                printf(")\n");
                break;
            }
            printf(" ,");
        }
    }

}



void readF(FILE *file, char *arr[]) {
    int sizeofline = 1024;
    char c;
    for (int i = 0; c != EOF; ++i) {
        char *str = malloc(sizeofline + 1);
        *(str) = '\0';
        for (int j = 0; c != EOF; ++j) {
            c = fgetc(file);
            if (c == EOF || c == '\n') {
                break;
            }
            *(str + j) = c;
            *(str + j + 1) = '\0';
        }
        if (*(str) == '\0') {
            continue;
        }
        if (c == EOF) {
            break;
        }
        arr[i] = str;
    }
    return;
}

int addN(char *line, struct human ppl[],int pers) {
    char *id = malloc(64);
    char *call = malloc(64);
    for (int i = 0; line[i] != '.'; i++) {
        id[i] = line[i];
        id[i + 1] = '\0';
    }
    ppl[pers].id = id;
    for (int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == '.') {
            for (int j = 0; line[i+j+1] != '\0'; ++j) {
                call[j] = line[i+j+1];
                call[j + 1] = '\0';
            }
            ppl[pers].name = call;
            break;
        }

    }
    pers++;
    return pers;
}

void proc(char *arr[], struct human ppl[]) {
    int pers = 0;
    for (int i = 0; arr[i] != NULL; ++i) {
        bool dot = false;
        for (int j = 0; arr[i][j] != '\0'; ++j) {
            if (arr[i][j] == '.') {
                dot = true;
            }
            if (arr[i][j] == ':' && !dot) {
                pers = addN(arr[i],ppl,pers);
            }
            if (dot) {
                chooseNadd(ppl,arr[i]);
            }
        }
    }


    /*
    int person = 0;
    int pk = 0;
    int pv = 0;
    char *str = malloc(1025);
    for (int i = 0; arr[i] != NULL; ++i) {
        pk = 0;
        pv = 0;
        bool ak = false;
        for (int j = 0; arr[i][j] != '\0'; ++j) {
            if (arr[i][j] == ':' && !ak) {
                ppl[person].id = str;
                char *nam = malloc(64);
                strcpy(nam,&arr[i][j + 1]);
                ppl[person].name = nam;
                break;
            }
            if (arr[i][j] == ':' && ak) {
                pv = j + 1;
                arr[i][j] = '\0';
                continue;
            }
            if (arr[i][j] == '.' && !ak) {
                arr[i][j] = '\0';
                pk = j + 1;
                ak = true;
                continue;
            }
            str[j] = arr[i][j];
            str[j + 1] = '\0';
        }
        if (ak) {
            int x = 0;
            switch (str[pk]) {
            case 'f':
                for (x = 0; ppl[x].id != NULL; ++x) {
                    if (!strcmp(&str[pv],ppl[x].id)) {
                        break;
                    }
                }
                addF(ppl[person],ppl[x].name);
                break;


            case 'b':
                ppl[person].date = malloc(64);
                strcpy(ppl[person].date,&str[pv]);
                break;
            default:
                break;
            }
        }
        person++;
    }*/
}

int main(int argc, char *argv[])
{

    int lines = 64;
    char *arr[lines];
    struct human ppl[256];
    if (argc > 2) {
        printf("Too many parameters.\n");
        return 0;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("File cannot be open.\n");
        return 0;
    }




    readF(file,arr);
    fclose(file);


    for (int i = 0; arr[i] != NULL; ++i) {
        printf("%s0\n",arr[i]);
    }


    proc(arr,ppl);
    for (int i = 0; ppl[i].id != NULL; ++i) {
        printf("%s0 %s0 %s0\n",ppl[i].id,ppl[i].date,ppl[i].name);
    }
    for (int i = 0; arr[i] != NULL; ++i) {
        free(arr[i]);
        arr[i] = NULL;
    }
    print(ppl);
    freedom(ppl);




    //precitat subor ak sa nepodari spravne to ukoncit
    //precita subor...
    //spracuje ho do struktury
    //vypise kazdy kluc
    //: je vzdy prva
    //ak je zadanny priatel tak uz pred tym bol definovany

    return 0;
}
