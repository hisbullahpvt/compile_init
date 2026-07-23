#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mount.h>

int copy_file(const char *src, const char *dst) {
    FILE *in = fopen(src, "rb");
    if (in == NULL)
        return -1;

    FILE *out = fopen(dst, "wb");
    if (out == NULL) {
        fclose(in);
        return -1;
    }

    char buffer[4096];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        if (fwrite(buffer, 1, bytes, out) != bytes) {
            fclose(in);
            fclose(out);
            return -1;
        }
    }

    fclose(in);
    fclose(out);

    return 0;
}

int main(int argc, char *argv[], char *envp[]) {

    // try to create /mytmp!
    mkdir("/mytmp", 0755);

    // try to create /source.txt
    FILE *fp = fopen("/source.txt", "w");
    fprintf(fp, "FIRST STAGE OK\n");
    fclose(fp);

    // try to mount tmpfs -> /mytmp!
    mount("tmpfs", "/mytmp", "tmpfs", 0, "");

    // try to copy source.txt to /mytmp/source.txt!
    copy_file("/source.txt", "/mytmp/source.txt");

    // finally execute oringinal init!
    execve("/system/bin/init", argv, envp);

    // if somthing wrong! start infinity loop!
    while (1) {
        sleep(1);
    }

    return 0;
}
