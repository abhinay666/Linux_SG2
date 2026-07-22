### Commands Executed:
1. `gcc -Wall server_monitor.c -o server_monitor`
2. `./server_monitor`

### Explanations:
* **Process Spawning via `fork()`:** Clones the calling process to split execution into concurrent execution streams (parent monitor vs. child worker).
* **Non-blocking Status Queries (`waitpid` with `WNOHANG`):** Uses `waitpid(..., WNOHANG)` to inspect state changes in child processes without stalling the main execution thread. Following force-termination with `SIGKILL`, a blocking `waitpid()` releases the process control block (PCB) entry to prevent resource leaks (zombies).
* **Inter-Process Signals (`SIGKILL` via `kill()`):** Sends an uncatchable termination signal (`SIGKILL`) to force-exit processes that violate maximum execution thresholds.