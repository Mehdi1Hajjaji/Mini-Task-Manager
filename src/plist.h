#ifndef PLIST_H
#define PLIST_H

#include <stddef.h> /* size_t */

/*
   PList — API de liste dynamique de Process (interface uniquement).

   Conventions du module
   - Codes de retour: 0 = succes, -1 = erreur (uniforme sur tout le module).
   - Pointeurs NULL: voir chaque prototype; les fonctions void sont des no-op
     si pl == NULL (ne plantent pas).
   - Responsabilite memoire: l'appelant doit appeler plist_init() avant usage
     et plist_free() en fin de vie. Les allocations internes sont liberees par
     plist_free().
   - Thread-safety: non thread-safe par defaut (pas de synchronisation interne).

   Debug/Assertions (optionnel)
   - Il est recommande d'activer des assertions en debug pour verifier les
     invariants (via <assert.h>). Aucune assertion n'est imposee par l'API.
*/

/*
   API de liste dynamique de Process (interface uniquement).

   Contrats généraux:
   - Toutes les fonctions retournent 0 en cas de succès et une valeur négative
     (-1) en cas d'erreur lorsqu'un code de retour existe.
   - Toute fonction recevant un pointeur documente le comportement si celui-ci
     vaut NULL (voir chaque prototype).
   - Aucune implémentation ici: seules les signatures sont déclarées.
   - Responsabilité mémoire: l'appelant initialise et libère la liste via
     plist_init() et plist_free(). Les éventuelles allocations internes au
     conteneur sont libérées par plist_free().
*/


/* Invariants PList (doivent toujours etre vrais):
   - data == NULL <=> size == 0 && capacity == 0
   - size <= capacity
   - capacity == 0 => data == NULL
*/
typedef struct Process Process;

typedef struct {
    Process *data;  /* zone de stockage des éléments (peut être NULL si vide) */
    size_t   size;  /* nombre d'éléments actuellement stockés */
    size_t   capacity; /* capacité allouée (en éléments) */
} PList;

/*
   plist_init
   Paramètres:
   - pl: pointeur valide sur une structure PList à initialiser.
     Si pl == NULL: aucun effet (contrat: la fonction ne plante pas).
   Retour:
   - Aucun (void).
   Effets de bord:
   - Met la liste dans un état vide utilisable: data=NULL, size=0, capacity=0.
   Complexité:
   - O(1).
*/
void plist_init(PList *pl);
/* Details:
   - Preconditions: pl peut etre NULL.
   - Postconditions (si pl != NULL): data=NULL, size=0, capacity=0.
   - Retour: void; no-op si pl == NULL.
   - Erreurs: aucune.
*/

/*
   plist_clear
   Paramètres:
   - pl: pointeur valide sur une PList.
     Si pl == NULL: aucun effet.
   Retour:
   - Aucun (void).
   Effets de bord:
   - Remet la taille à 0 mais ne libère pas la zone (capacity inchangée).
   Complexité:
   - O(1).
*/
void plist_clear(PList *pl);
/* Details:
   - Preconditions: pl peut etre NULL.
   - Postconditions (si pl != NULL): size=0; data/capacity inchanges.
   - Retour: void; no-op si pl == NULL.
   - Erreurs: aucune.
*/

/*
   plist_free
   Paramètres:
   - pl: pointeur valide sur une PList.
     Si pl == NULL: aucun effet.
   Retour:
   - Aucun (void).
   Effets de bord:
   - Libère la zone interne si nécessaire et remet la liste à l'état initial
     (équivalent à { data=NULL, size=0, capacity=0 }).
   Complexité:
   - O(1) pour l'opération elle-même (hors coût de libération mémoire).
*/
void plist_free(PList *pl);
/* Details:
   - Preconditions: pl peut etre NULL.
   - Postconditions (si pl != NULL): data liberee si non NULL; data=NULL,
     size=0, capacity=0 (etat initial). Idempotente.
   - Retour: void; no-op si pl == NULL.
   - Erreurs: aucune (free(NULL) sans effet).
*/

/*
   plist_push
   Paramètres:
   - pl: pointeur valide vers la PList de destination.
   - p: pointeur valide vers le Process à copier.
     Si pl == NULL ou p == NULL: échec.
   Retour:
   - 0 en cas de succès, -1 en cas d'argument invalide ou d'échec d'allocation.
   Effets de bord:
   - Ajoute une copie de *p à la fin de la liste; peut réallouer la zone.
   Complexité:
   - Amortie O(1) après réallocation (stratégie de croissance non exposée ici).
*/
int plist_push(PList *pl, const Process *p);
/* Details:
   - Preconditions: pl != NULL, p != NULL.
   - Postconditions (si succes): *p est copie a la fin; peut reallouer.
     En cas d'echec d'allocation: -1 est retourne et la liste reste inchangee.
   - Retour: 0 si succes; -1 si argument invalide ou echec d'allocation.
   - Erreurs typiques: pl==NULL, p==NULL, malloc/realloc a echoue.
*/

/*
   plist_get
   Paramètres:
   - pl: pointeur valide vers la PList source.
   - idx: indice de l'élément à lire (0 <= idx < size).
   - out: pointeur valide où écrire la copie de l'élément.
     Si pl == NULL, out == NULL, ou idx hors bornes: échec.
   Retour:
   - 0 si OK, -1 si hors bornes ou pointeur invalide.
   Effets de bord:
   - Aucun (ne modifie pas la liste).
   Complexité:
   - O(1).
*/
int plist_get(const PList *pl, size_t idx, Process *out);
/* Details:
   - Preconditions: pl != NULL, out != NULL, 0 <= idx < pl->size.
   - Postconditions (si succes): *out recoit une copie de l'element idx.
     En cas d'erreur, *out n'est pas modifiee.
   - Retour: 0 si succes; -1 si pointeur invalide ou idx hors bornes.
*/

/*
   plist_size (optionnel)
   Paramètres:
   - pl: pointeur vers la PList.
     Si pl == NULL: retourne 0.
   Retour:
   - Taille courante de la liste (nombre d'éléments).
   Effets de bord:
   - Aucun.
   Complexité:
   - O(1).
*/
size_t plist_size(const PList *pl);
/* Details:
   - Preconditions: pl peut etre NULL.
   - Retour: taille courante (0 si pl == NULL).
*/

#endif /* PLIST_H */
