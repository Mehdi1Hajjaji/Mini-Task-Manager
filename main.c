#include <stdio.h>
#include "plist.h"

int main(void) {
    Process p1 = { .pid = 1234, .name = "bash", .state = "running", .mem_kb = 2048 };
    Process p2 = { .pid = 5678, .name = "very-long-command-name-that-fits-63-chars-total-xxxx", .state = "S", .mem_kb = 512 };
    Process p3 = { .pid = 9999, .name = "firefox", .state = "Z", .mem_kb = 0 };

    printf("p1: pid=%lu name=%s state=%s mem_kb=%lu\n", p1.pid, p1.name, p1.state, p1.mem_kb);
    printf("p2: pid=%lu name=%s state=%s mem_kb=%lu\n", p2.pid, p2.name, p2.state, p2.mem_kb);
    printf("p3: pid=%lu name=%s state=%s mem_kb=%lu\n", p3.pid, p3.name, p3.state, p3.mem_kb);



return 0;

}