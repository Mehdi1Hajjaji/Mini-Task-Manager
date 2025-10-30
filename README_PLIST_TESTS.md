PList — Plan de tests manuel
================================

Objectif
- Verifier la robustesse et la conformite de l'API `PList` (init, push, get, clear, free).

Conventions
- Codes de retour: 0 = succes, -1 = erreur.
- Fonctions `void`: no-op si `pl == NULL`.

Prérequis build
- Compiler avec: `gcc -Wall -Wextra -std=c11 -Isrc src/main.c src/plist.c -o src/output/main.exe`
- Ou tester module seul: `gcc -Wall -Wextra -std=c11 -Isrc -c src/plist.c -o build/plist.o`

Cas de test
- init
  - `plist_init(NULL)` ne plante pas.
  - `PList pl; plist_init(&pl);` -> `pl.data==NULL`, `pl.size==0`, `pl.capacity==0`.

- push (basique)
  - `plist_push(NULL, &p)` -> -1.
  - `plist_push(&pl, NULL)` -> -1.
  - `plist_push(&pl, &p)` -> 0; `size` passe a 1; l'element est present.
  - Copie: modifier `p` apres `push` ne modifie pas la copie stockee.

- push (croissance)
  - Pousser 1..4 elements -> `capacity` passe de 0 a 4.
  - Pousser un 5e element -> `capacity` passe a 8, les 5 elements sont intacts.
  - Repetition jusqu'a > 100 elements (robustesse croissance).

- get
  - Indices valides 0..size-1 -> 0, donnees correctes.
  - `idx == size` ou `idx > size` -> -1, `out` non modifie.
  - `plist_get(NULL, 0, &out)` -> -1.
  - `plist_get(&pl, 0, NULL)` -> -1.

- clear
  - Remplir la liste, `plist_clear(&pl)` -> `size==0`, `capacity` inchangée, `data` non libérée.
  - `push` apres `clear` reutilise l'espace alloue (pas de reallocation tant que `size < capacity`).

- free
  - Remplir, `plist_free(&pl)` -> `data==NULL`, `size==0`, `capacity==0`.
  - Idempotence: appeler `plist_free(&pl)` a nouveau ne plante pas.
  - `plist_free(NULL)` ne plante pas.

- erreurs d'allocation (simulation)
  - Simuler un echec de `malloc/realloc` (ex: introduire un crochet de test dans le code ou forcer `new_capacity` tres grand).
  - Verifier que `plist_push` retourne -1 et que `data/size/capacity` restent inchanges.

- invariants
  - A chaque etape, verifier: `size <= capacity`, `capacity==0 => data==NULL`, `data==NULL <=> size==0 && capacity==0`.

- stress
  - Pousser 10k elements aleatoires et verifier `size` + quelques echantillons de valeurs.

Qualite memoire (optionnel)
- Linux: `valgrind --leak-check=full src/output/main` -> pas de fuite, pas d'erreurs.
- Alternative: AddressSanitizer (`-fsanitize=address`) si disponible.

Notes
- L'API n'est pas thread-safe; ne pas tester en concurrence.
- `plist_size` (si implémentee) doit retourner 0 si `pl==NULL`.

