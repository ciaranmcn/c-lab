# c-lab

Small C programs for learning sockets and Linux `/proc`. No Makefile—compile what you need.

**Files**

- `server.c` — TCP server on port 8080, minimal HTTP-style reply (`fork` per connection).
- `sockets.c` — TCP client: connect to Google, send a raw HTTP request, print the response.
- `networks.c` — Read `/proc/net/dev` (expects `eth0`; change the name if yours differs).
- `ps_mini.c` — List PIDs and `VmRSS` from `/proc/*/status`.
- `monitor.c` — Print load average from `/proc/loadavg` every few seconds.

**Linux:** `networks.c`, `ps_mini.c`, and `monitor.c` need `/proc` (use Linux, not macOS).

**Build**

```bash
cc -Wall -Wextra -o server server.c
cc -Wall -Wextra -o sockets sockets.c
cc -Wall -Wextra -o networks networks.c
cc -Wall -Wextra -o ps_mini ps_mini.c
cc -Wall -Wextra -o monitor monitor.c
```

With `./server` running: `curl http://127.0.0.1:8080/`

Educational only—not hardened for real networks or production.
