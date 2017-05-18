#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
//why is there a '\n' "karel<eof>"



//Mozes mi prosim ta povedat preco mi valgrind vypisuje
//ze niektore values su neinicializovane? aj ked teda su/mali by byt inicializovane?
//napr.
//char *arr[lines];
//pise mi ze je to neinicializovane... aj ked, ked zapnem debuger vsetko je nastavene na 0x0
//pise mi tam chybu az pokial nenapisem toto:
//for (int i = 0; i < lines; ++i) {
//    arr[i] = NULL;
//}




struct human {
    char *id;
    char *name;
    char *date;
    char *friends[256];
    int n_f;
};

//Whoose id it is
int choose(char *id,struct human ppl[]) {
    for (int i = 0; ppl[i].id != NULL; ++i) {
        if (!strcmp(id,ppl[i].id)) {
            return i;
        }
    }
    return -1;
}

//Adds friend
void addF(struct human *person, char *line) {
    char *FD = malloc(64);
    for (int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == ':') {
            for (int j = 0; line[i + j + 1] != '\0'; ++j) {
                FD[j] = line[i + 1 + j];
                FD[j + 1] = '\0';
            }

        }

    }
    person->friends[person->n_f] = FD;
    person->n_f += 1;
    return;
}

//Chooses whether it is a Bday key or friend key
void chooseNadd(struct human ppl[], char *line) {
    for (int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == '.') {
            if (line[i + 1] == 'b') {
                char *bday;
                bday = malloc(sizeof(char)*64);
                char *id = malloc(64);
                for (int x = 0; line[x] != '.'; ++x) {
                    id[x] = line[x];
                    id[x + 1] = '\0';
                }
                int per = choose(id,ppl);
                free(id);
                id = NULL;
                for (int j = 0; line[i + 11 + j] != '\0'; ++j) {
                    bday[j] = line[i + j + 11];
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
                addF(&ppl[per],line);
            }
            break;
        }
    }
    return;
}

//frees all people
void freedom(struct human ppl[]) {
    for (int i = 0; ppl[i].id != NULL; ++i) {

        if (ppl[i].id) {
            free(ppl[i].id);
            ppl[i].id = NULL;
        }
        if (ppl[i].name) {
            free(ppl[i].name);
            ppl[i].name = NULL;
        }
        if (ppl[i].date) {
            free(ppl[i].date);
            ppl[i].date = NULL;
        }
        if (ppl[i].friends[0]) {
            for (int j = ppl[i].n_f; j != 0; --j) {
                free(ppl[i].friends[j - 1]);
                ppl[i].friends[j - 1] = NULL;
            }
        }

    }
}

//prints the wanted output
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

//Reads the file and stores it in ARR
void readF(FILE *file, char *arr[]) {
    int sizeofline = 1024;
    char c = 'a';
    for (int i = 0; c != EOF; ++i) {
        char *str = malloc(sizeofline + 1); //toto je zevraj neinicializovane... ako to mam inicializovat
        *(str) = '\0';
        for (int j = 0; c != EOF; ++j) {
            c = fgetc(file);
            if (c == EOF || c == '\n') {
                break;
            }
            *(str + j) = c;
            *(str + j + 1) = '\0';
        }
        if (c == EOF) {
            free(str);
            str = NULL;
            break;
        }
        if (*(str) == '\0') {
            continue;
        }   
        arr[i] = str;

    }

    return;
}

//Adds name and ID to the human
int addN(char *line, struct human ppl[],int pers) {
    char *id = malloc(64);
    char *call = malloc(64);
    for (int i = 0; line[i] != ':'; i++) {
        id[i] = line[i];
        id[i + 1] = '\0';
    }

    ppl[pers].id = id;
    for (int i = 0; line[i] != '\0'; ++i) {
        if (line[i] == ':') {
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

//Procesess the text
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
                break;

            }
        }
    }
}

int main(int argc, char *argv[])
{
    int lines = 64;
    char *arr[lines];
    for (int i = 0; i < lines; ++i) {
        arr[i] = NULL;
    }
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
    proc(arr,ppl);
    //frees the text
    for (int i = 0; arr[i] != NULL; ++i) {
        free(arr[i]);
        arr[i] = NULL;
    }
    print(ppl);
    freedom(ppl);
    return 0;
}
