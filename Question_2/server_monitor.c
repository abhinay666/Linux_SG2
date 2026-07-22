#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork operation failed");
        return EXIT_FAILURE;
    } 
    
    if (child_pid == 0) {
        // Child execution path
        printf("[CHILD  | PID: %d] Process running intensive job...\n", getpid());
        sleep(10); // Simulate extended execution time exceeding threshold
        printf("[CHILD  | PID: %d] Task finished normally.\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        // Parent execution path
        int status;
        printf("[PARENT | PID: %d] Monitoring child PID %d. Timeout window: 3s\n", getpid(), child_pid);
        sleep(3); 

        // Non-blocking status query
        pid_t check_result = waitpid(child_pid, &status, WNOHANG);

        if (check_result == 0) {
            printf("[PARENT | PID: %d] Child process unresponsive. Initiating termination...\n", getpid());
            
            kill(child_pid, SIGKILL); 
            waitpid(child_pid, &status, 0); // Reap child resources
            
            printf("[PARENT | PID: %d] Child process reaped successfully. Zombie state prevented.\n", getpid());
        } else {
            printf("[PARENT | PID: %d] Child completed within the designated time limits.\n", getpid());
        }
    }

    return EXIT_SUCCESS;
}