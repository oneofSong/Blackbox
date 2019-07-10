#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <pwd.h>

void get_time(char* buf);
void make_directory(char *dir_name);

int main(int argc, char *argv[]){
    char dir_name[12];
    
    get_time(dir_name);
    make_directory(dir_name);
    
    return 0;    
}

void get_time(char* buf){
    time_t cur_time;
    struct tm *tm_ptr;
    
    cur_time = time(NULL);
    tm_ptr = localtime(&cur_time);

    // sprintf(buf, "%d%02d%02d_%02d",tm_ptr->tm_year+1900,tm_ptr->tm_mon+1,tm_ptr->tm_mday,tm_ptr->tm_hour);
    strftime(buf, 12, "%Y%02m%02d_%0l", tm_ptr);
}


// /home/user_name/black 하위에 디렉토리 생성
void make_directory(char *dir_name){
    char path[50] = "/";
    int ret;
    
    struct passwd *user_pw;
    user_pw = getpwuid(getuid());

    strcat(path, user_pw->pw_dir);
    strcat(path, "/blackbox/");   


    if ( 0 != access(path, R_OK)){
        printf("blackbox 디렉토리 생성\n");
        printf("%s\n", path);

        if((ret=mkdir(path, 0755) == -1)){
            perror("mkdir");
        }

    }

    strcat(path, dir_name);
    if ( 0 != access(path, R_OK)){
        printf("시간  디렉토리 생성\n");
        printf("%s\n", path);

        if((ret=mkdir(path, 0755) == -1)){
            perror("mkdir");
        }
    } else{
        printf("directory alreay exists!\n");
    }
}
