#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

void get_process_info(char* pid) {
    char path[256];
    char line[256];
    FILE* f;

    // 1. Build the string "/proc/[PID]/status"
    snprintf(path, sizeof(path), "/proc/%s/status", pid);

    // 2. Open that specific process's status file
    f = fopen(path, "r");
    if (f == NULL) return; // If process ended quickly, just skip it

    // 3. Read the file line-by-line
    while (fgets(line, sizeof(line), f)) {
        // 4. Look for the line starting with "VmRSS" (Physical RAM)
        if (strncmp(line, "VmRSS:", 6) == 0) {
            printf("PID: %s | Memory: %s", pid, line + 7);
            break; 
        }
    }

    fclose(f);
}

int main() {
    DIR* d;
    struct dirent* dir_entry;

    // 5. Open the virtual /proc directory
    d = opendir("/proc");
    if (d == NULL) {
        perror("Could not open /proc");
        return 1;
    }

    // 6. Loop through every folder in /proc
    while ((dir_entry = readdir(d)) != NULL) {
        // 7. If the folder name starts with a digit, it's a process!
        if (isdigit(dir_entry->d_name[0])) {
            get_process_info(dir_entry->d_name);
        }
    }

    closedir(d);
    return 0;
}