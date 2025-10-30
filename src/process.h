/* Minimal definition of Process used by PList */
#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>

#define PROCESS_NAME_LEN 64
#define PROCESS_STATE_LEN 16

typedef struct Process {
    unsigned long pid;
    char name[PROCESS_NAME_LEN];
    char state[PROCESS_STATE_LEN];
    unsigned long mem_kb;
} Process;


int process_read_all(PList *list);

// Créer un Process à partir de ses infos
Process process_make(unsigned long pid, const char *name, const char *state, unsigned long mem_kb);

// Vérifier si un Process est valide
int process_is_valid(const Process *proc);

//  Format court pour affichage/test
int process_format_brief(const Process *proc, char *buffer, size_t buflen);

// Remplir une PList avec des Process fictifs pour les tests
int process_fill_mock(PList *pl);




#endif /* PROCESS_H */

