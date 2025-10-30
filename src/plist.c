#include "plist.h"
#include "process.h"

#include <stdio.h>
#include <stdlib.h>

/* Initialise la liste dynamique */
void plist_init(PList *pl){
    if (!pl) return;
    pl->data = NULL;
    pl->size = 0;
    pl->capacity = 0;
}

/* Ajoute un Process à la liste */
int plist_push(PList *pl , const Process *p){
    if (!pl || !p) return -1; 

        if (pl->size == pl->capacity){
            size_t new_capacity = (pl->capacity == 0) ? 4 : (pl->capacity * 2);
            
   Process *new_data = (Process *)realloc(pl->data, new_capacity * sizeof *new_data);
        if (!new_data) return -1;
        pl->data = new_data;
        pl->capacity = new_capacity;
    }

    pl->data[pl->size] = *p;
    pl->size += 1;
    return 0;
}

/* Lit l’élément d’indice idx */
int plist_get(const PList *pl, size_t idx, Process *out){
    if (!pl || !out ) return -1;
    if (idx >= pl->size) return -1;

    *out = pl->data[idx];

    return 0;
}

/* Réinitialise la taille à 0 */
void plist_clear(PList *pl) {
    if (!pl) return;
    pl->size = 0;
}

/* Libère la zone mémoire utilisée */
void plist_free(PList *pl){
    if(!pl) return;
    if (pl->data) free(pl->data);
    pl->data = NULL;
    pl->size = 0;
    pl->capacity = 0;
}



