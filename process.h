#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

#define PROCESS_Name_Len_64  /* Nom max = 64 caractères (inspiré de /proc/<pid>/comm, largement suffisant pour un affichage).
#define PROCESS_STATE_Len_16 /*États possibles documentés comme chaîne courte ("R","S","Z","T","I") ou longue ("running"...).

typedef struct{
    pid_t pid;
    char name[PROCESS_NAME_LEN];
    char state[PROCESS_STATE_LEN];
    unsigned long memory_kb;
} process_info_t;

#endif // PROCESS H 