#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/mount.h>
#include<malloc.h>

bool create_folder(const char * path)
{
    int result = mkdir(path, S_IRWXU);
    printf("Creating folder %s ...\n", path);
    if (result == 0) {
        printf("Directory  %s created successfully.\n", path);
    } else {
        perror("mkdir");
        return false;
    }
    return true;
}


bool delete_folder(const char *path)
{

    int result = rmdir(path);
    printf("Deleting folder %s ...\n", path);
    if (result == 0) {
        printf("Directory  %s deleted successfully.\n", path);
    } else {
        perror("rmdir");
        return false;
    }
    return true;
}


bool write_to_file(const char *path, const char *text) {
    printf("Creating file %s ...\n", path);
    int result = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (result < 0) {
        perror("Open file");
        return false;
    }
    
    printf("Opened file '%s'.\n", path);
    printf("Writing in file %s ...\n", path);
    
    ssize_t bytes_written = write(result, text, strlen(text));
    if (bytes_written == -1) {
        perror("Failed to write to file");
        close(result);
        return false;
    }

    close(result);
    printf("Wrote in file %s ...\n", path);
    return true;
}

int filter(const struct dirent *entry) {
    return 1; 
}



bool write_random_or_null(const char *path, int count_bytes,int chose)
{
    int result;
    printf("Opening /dev/urandom...\n");
    if(chose==1) result = open("/dev/urandom", O_RDONLY);
    else result = open("/dev/zero", O_RDONLY);
    if (result < 0) {
        perror("Open file");
        return false;
    }
    
    printf("Opened /dev/urandom\n");
    printf("Reading bytes of urandom...\n");
    char *text = (char *)malloc(count_bytes);
    ssize_t bytes_read = read(result, text, count_bytes);
    if (bytes_read == -1) {
        perror("Failed to read file");
        close(result);
        return false;
    }
    
    printf("Writing in file %s ...\n", path);
    
    int output_file = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (output_file < 0) {
        perror("Open output file");
        close(result);
        free(text);
        return false;
    }
    
    ssize_t bytes_written = write(output_file, text, bytes_read);
    if (bytes_written == -1) {
        perror("Failed to write to file");
        close(result);
        close(output_file);
        free(text);
        return false;
    }

    close(result);
    close(output_file);
    free(text);
    printf("Wrote random in file %s ...\n", path);
    return true;
}

bool symbol_link(const char *target, const char *linkpath){

    printf("Creating symlink on path  %s ...\n", linkpath);
    int result=symlink(target, linkpath);
    if (result < 0) {
        perror("symlink");
        return false;
    }
    printf("Created link  on  path %s ...\n", linkpath);
    return true;
}

bool hard_link(const char *target, const char *linkpath)
{
    printf("Creating symlink on path  %s ...\n", linkpath);
    int result=link(target, linkpath);
    if (result < 0) {
        perror("link");
        return false;
    }
    printf("Created link  on  path %s ...\n", linkpath);
    return true;
}

int removeDirectory(const char* path)
{
     int result= rmdir(path);
     if (result < 0) {
        perror("rmdir");
        return false;
    }
    printf("Remove Directory  on  path %s succsesful\n", path);
    return true;
}

int removeFile(const char* path)
{
    int result= unlink(path);
    if (result < 0) {
        perror("unlink");
        return false;
    }
    printf("Unlink  file on  path %s ... succsesful\n", path);
    return true;
}

bool remove_files(const char *dir_path) {
    struct dirent **namelist;
    int n = scandir(dir_path, &namelist, NULL, alphasort);
    if (n < 0) {
        perror("scandir");
        return false;
    }
    char file_path[PATH_MAX];
    for (int i = 0; i < n; i++) {
        if (strcmp(namelist[i]->d_name, ".") == 0 || strcmp(namelist[i]->d_name, "..") == 0) {
            free(namelist[i]);
            continue;
        }
        snprintf(file_path, PATH_MAX, "%s/%s", dir_path, namelist[i]->d_name);
        if (namelist[i]->d_type == DT_DIR) {
            remove_files(file_path);
 
        } else {
            removeFile(file_path);
        }
        
        free(namelist[i]);
    }
    
    free(namelist);

    removeDirectory(dir_path);
    
    return true;
}




void creating(){

    create_folder("Harry_Potter");
    create_folder("Harry_Potter/Orden_Fenix");
    create_folder("Harry_Potter/Death_Eaters");

    write_random_or_null("Harry_Potter/Orden_Fenix/Dambldor.txt",10,1);
    write_to_file("Harry_Potter/Orden_Fenix/Grum.txt","");
    write_to_file("Harry_Potter/Orden_Fenix/Snape.txt","Иногда мы должны сделать то, что кажется нам невозможным.");
    symbol_link("Harry_Potter/Death_Eaters","Harry_Potter/Orden_Fenix/Lupin");
    
    write_random_or_null("Harry_Potter/Death_Eaters/Vlan_De_Mort.txt",2,0);
    write_to_file("Harry_Potter/Death_Eaters/Malfoy.txt","Некоторые люди просто рождаются счастливыми. Мы, Малфои, например.");
    hard_link("Harry_Potter/Orden_Fenix/Snape.txt","Harry_Potter/Death_Eaters/Snape");

}


int main()
{
    creating();
    getchar();
    remove_files("Harry_Potter");


}