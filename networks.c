#include <stdio.h>
#include <string.h>

void monitor_network() {
    FILE *f = fopen("/proc/net/dev", "r");
    char line[256];

    if (!f) return;

    printf("--- Network Stats ---\n");

    while(fgets(line, sizeof(line), f)) {
        if (strstr(line,"eth0:")) {
            long long rx_bytes, tx_bytes;
            // recieved and transmitted
            sscanf(strstr(line,"eth0:") + 5, "%lld", &rx_bytes);

            printf("Bytes Received: %lld\n", rx_bytes);
        }
    }
    fclose(f);
}

int main() {
    monitor_network();
    return 0;
}