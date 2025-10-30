#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

int process_read_all(PList *list) {
    if (!list) return -1; // Erreur si la liste est invalide

    DIR *proc_dir = opendir("/proc");
    if (!proc_dir) return -1;

    struct dirent *entry;

    while ((entry = readdir(proc_dir)) != NULL) {
        // Vérifie si le nom du dossier est un nombre (PID)
        size_t len = strlen(entry->d_name);
        int is_pid = (len > 0);
        for (size_t i = 0; i < len; i++) {
            if (!isdigit((unsigned char)entry->d_name[i])) {
                is_pid = 0;
                break;
            }
        }
        if (!is_pid) continue;

        // Ouvre /proc/<pid>/status
        char status_path[256];
        snprintf(status_path, sizeof(status_path), "/proc/%s/status", entry->d_name);

        FILE *fp = fopen(status_path, "r");
        if (!fp) continue; // Impossible d'ouvrir ce process

        // Variables temporaires pour chaque Process
        unsigned long pid = strtoul(entry->d_name, NULL, 10);
        char name[PROCESS_NAME_LEN] = "";
        char state[PROCESS_STATE_LEN] = "";
        unsigned long mem_kb = 0;

        char line[256];
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "Name:", 5) == 0) {
                sscanf(line + 5, "%63s", name);
            }
            if (strncmp(line, "State:", 6) == 0) {
                sscanf(line + 6, "%15s", state);
            }
            if (strncmp(line, "VmRSS:", 6) == 0) {
                sscanf(line + 6, "%lu", &mem_kb);
            }
        }
        fclose(fp);

        // Si la mémoire n'est pas trouvée, garde à 0.
        // Crée Process et ajoute à la liste
        Process proc = process_make(pid, name, state, mem_kb);
        plist_push(list, &proc); // Ignore si erreur de push
    }

    closedir(proc_dir);
    return 0;
}
