#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

void get_time(char* buf);
void make_directory(char *dir_name, int name_len);

int main(int argc, char *argv[]){
    char dir_name[12];
    
    get_time(dir_name);
    make_directory(dir_name, strlen(dir_name));

    return 0;    
}

void get_time(char* buf){
    time_t cur_time;
    struct tm *tm_ptr;
    
    cur_time = time(NULL);
    tm_ptr = localtime(&cur_time);
    
    sprintf(buf, "%d%02d%02d_%02d",tm_ptr->tm_year+1900,tm_ptr->tm_mon+1,tm_ptr->tm_mday,tm_ptr->tm_hour);
}

void make_directory(char *dir_name, int name_len){
    char base_path[] = "/home/song/blackbox/";
    int path_len = strlen(base_path) + name_len;
    char path[path_len+1];
    strcat(path, base_path);
    strcat(path, dir_name);
    
    // printf("%s\n", path);

    if ( 0 != access(base_path, R_OK)){
        mkdir(base_path, 0775);
    }

    if ( 0 != access(path, R_OK)){
        mkdir(path, 0775);
    } else{
        printf("directory alreay exists!\n");
    }
}
