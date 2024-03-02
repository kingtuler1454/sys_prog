#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}


bool create_folder(const char * path)
{
    int result = mkdir(path, S_IRWXU);

    if (result == 0) {
        printf("Directory  %s created successfully.\n", path);
    } else {
        printf("Directory  %s created Unsuccessful.\n", path);
        return false;
    }
    return true;
}

int main()
{

    create_folder("GTA5")
    // struct dirent **namelist;
    // int n;

    // printf("Current directory:\n");
    
    create_folder("GTA5");




    // n = scandir(".", &namelist, NULL, alphasort);
    // if (n < 0) {
    //     perror("scandir");
    //     return 1;
    // }

    // for (int i = 0; i < n; i++) {
    //     if (is_directory(namelist[i]->d_name)) {
    //         printf("%s\n", namelist[i]->d_name);
    //     }
    // }

    return 0;
}
