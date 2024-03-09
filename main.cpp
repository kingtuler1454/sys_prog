#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int is_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}
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
bool open_directory(const char *path)
{
    printf("Opening directory %s ...\n", path);
    if (chdir(path) == 0) {
        printf("Changed directory to '%s'.\n", path);
        return true;
    } else {
        perror("chdir");
        return false;
    }
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


bool symbol_link(const char *target, const char *linkpath){

    /*создать символьную ссылку*/
    printf("Creating symlink on path  %s ...\n", linkpath);
    int result=symlink(target, linkpath);
    if (result < 0) {
        perror("symlink");
        return false;
    }
    printf("Created link  on  path %s ...\n", linkpath);
    return true;
}

int main()
{

    
    // struct dirent **namelist;
    // int n;

    // printf("Current directory:\n");
    
    create_folder("GTA5");
    open_directory("GTA5");// изменить рабочий каталог
     create_folder("Venichles");
     create_folder("Heroes");
    
     open_directory("Heroes");
      create_folder("Trevor");
      create_folder("Micle");
      create_folder("Franklin");
    
    write_to_file("Trevor/quote.txt","Listen: nobody likes you!");
    write_to_file("Trevor/zero.txt", "00");
    write_to_file("Trevor/random.txt","asd");
    
    write_to_file("Micle/quote.txt","Каждый день ты забываешь тысячу мелочей. Пусть это будет одна из них.");
    write_to_file("Micle/zero.txt", "00");
    write_to_file("Micle/random.txt","asd");
    
    write_to_file("Franklin/quote.txt","My car is dear, moron!");
    write_to_file("Franklin/zero.txt", "00");
    write_to_file("Franklin/random.txt","My car is dear, moron!");
    open_directory("..");
    create_folder("Venichles/Franklin");
    create_folder("Venichles/Trevor");
    create_folder("Venichles/Micle");
    
    write_to_file("Venichles/Franklin/car.txt","Bravado Buffalo S");
    symbol_link("../../Heroes/Franklin","Venichles/Franklin/link_on_heroes");

    write_to_file("Venichles/Trevor/car.txt","Canis Bodhi");
    symbol_link("../../Heroes/Trevor","Venichles/Trevor/link_on_heroes");

    symbol_link("../../Heroes/Micle","Venichles/Micle/link_on_heroes");
    write_to_file("Venichles/Micle/car.txt","Dewbauchee Exemplar");




    //delete_folder("Franklin");
   


    
    



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
