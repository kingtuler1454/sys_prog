#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

int main()
{
    struct dirent **namelist;
    int n;

    printf("Current directory:\n");

    n = scandir(".", &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (is_directory(namelist[i]->d_name)) {
            printf("%s\n", namelist[i]->d_name);
        }
    }

    return 0;
}
