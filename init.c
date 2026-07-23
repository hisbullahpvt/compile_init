
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mount.h>

int main(int argc, char *argv[], char *envp[]) {

    // get process id!
    pid_t pid = getpid();

    if (pid == 1) {

        // try to create /mytmp
        mkdir("/mytmp", 0755);

        /*

        // try to mount tmpfs -> /mytmp
        mount("exboot", "/mytmp", "tmpfs", 0, "mode=0755,size=8M");

        // try to create /mytmpt/source.txt
        FILE *fp = fopen("/mytmp/source.txt", "w");
        if (fp) {
            fprintf(fp, "FIRST STAGE OK\n");
            fclose(fp);
        } */
    }

    // finally execute oringinal init!
    execve("/system/bin/init", argv, envp);

    // if somthing wrong! start infinity loop!
    while (1) {
        sleep(1);
    }

    return 0;
}