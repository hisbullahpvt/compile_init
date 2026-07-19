#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    sleep(20);
    execve("/system/bin/init", argv, envp);

    // execve fail aana mattum inga varum
    while (1) {
        sleep(1);
    }

    return 0;
}
