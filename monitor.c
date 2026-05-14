#include <stdio.h>
#include <unistd.h> // For sleep()
int main() {
    FILE *fp;
    char buffer[255];
    float load1, load5, load15;

    while (1){

        
        fp = fopen("/proc/loadavg", "r");
        if (fp == NULL) {
            printf("Error: Could not open /proc/loadavg. Are we on Linux?\n");
            return 1; // Exit with an error code
        }

        fgets(buffer, 255, fp);

        sscanf(buffer, "%f %f %f", &load1, &load5, &load15 );

        printf("The 1-minute load average is: %.2f\n", load1);
        // Try to read
        if (load1 > 2.0) {
            printf("⚠️ Warning: CPU is getting a bit busy!\n");
        } else {
            printf("✅ System is chilling.\n");
        }

        fclose(fp);
        sleep(2);
    }
    return 0;
}
