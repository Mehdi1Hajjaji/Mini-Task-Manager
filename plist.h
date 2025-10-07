#ifndef PLIST_H
#define PLIST_H

#define PROCESS_NAME_CAP 64
#define PROCESS_STATE_CAP 16

/* Process describes a single tracked process without dynamic allocation.
   pid:        positive identifier (> 0) copied from the system.
   name:       null-terminated program name (<= 63 chars); 64 is enough for
               typical POSIX command names while staying compact.
   state:      null-terminated state string; accept short codes {"R","S","Z","T","I"}
               or documented longer forms like "running" or "sleeping".
   mem_kb:     resident memory usage expressed in kilobytes (kB), must be >= 0.
*/
typedef struct {
    unsigned long pid;
    char name[PROCESS_NAME_CAP];
    char state[PROCESS_STATE_CAP];
    unsigned long mem_kb;
} Process;

#endif /* PLIST_H */