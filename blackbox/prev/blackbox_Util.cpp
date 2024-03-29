#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <sys/time.h>

#include <time.h>


// 현재 시간을 buf에 저장
struct tm get_time(char* buf, char type){
    time_t cur_time;
    struct tm *tm_ptr;
    
    cur_time = time(NULL);
    tm_ptr = localtime(&cur_time);

	if (type == 'D' || type == 'd')
		// sprintf(buf, "%d%02d%02d_%02d",tm_ptr->tm_year+1900,tm_ptr->tm_mon+1,tm_ptr->tm_mday,tm_ptr->tm_hour);
		strftime(buf, 12, "%4Y%2m%2d_%H", tm_ptr);
	else if (type == 'F' || type == 'f')
		strftime(buf, 16, "%4Y%2m%2d_%H%M%S", tm_ptr);


	return *tm_ptr;
}

// time1, time2의 시간의 차이를 반환
// time 1이 클때 양수, time 2가 클 때 음수 , 같을 때는 0
/*
double cmp_time(char* time1, char* time2){
    struct tm* tmp[2];
    time_t t_fst, t_snd;
    int i;
    double dif_time;

#ifdef DEBUG
    printf("%s\n", time1);
    printf("%s\n", time2);
#endif

    for(int i=0; i<2; i++){
        tmp[i] = malloc(sizeof(struct tm));
        tmp[i]->tm_sec =0;
        tmp[i]->tm_min = 0;
        tmp[i]->tm_isdst = 0;
    }

    // string -> struct tm으로 변환
    if(strptime(time1, "%Y%02m%02d_%0l",tmp[0])==NULL) perror("strptime error");
    if(strptime(time2, "%Y%02m%02d_%0l",tmp[1])==NULL) perror("strptime error");

#ifdef DEBUG
    printf("%4d%2d%2d_%2d\n",1900+tmp[0]->tm_year, 1+tmp[0]->tm_mon, tmp[0]->tm_mday,tmp[0]->tm_hour);
    printf("sec : %d, min : %d, tm_isdst : %d\n", tmp[0]->tm_sec, tmp[0]->tm_min, tmp[0]->tm_isdst);
    printf("%4d%2d%2d_%2d\n",1900+tmp[1]->tm_year, 1+tmp[1]->tm_mon, tmp[1]->tm_mday,tmp[1]->tm_hour);
    printf("sec : %d, min : %d, tm_isdst : %d\n", tmp[1]->tm_sec, tmp[1]->tm_min, tmp[1]->tm_isdst);
#endif

    // struct tm -> time_t로 변환
    t_fst = mktime(tmp[0]);
    t_snd = mktime(tmp[1]);

    // time_t type의 변수를 비교
    dif_time = difftime(t_fst,t_snd);

#ifdef DEBUG
    printf("%f\n", dif_time);
#endif

    free(tmp[0]);
    free(tmp[1]);

    return dif_time;
}
*/

// /home/user_name/black 하위에 디렉토리 생성
int make_directory(const char *dir_name){
    char path[50] = "";
    int ret;
    struct passwd *user_pw;
    
	user_pw = getpwuid(getuid());
	strcat(path, user_pw->pw_dir);
    strcat(path, "/blackbox/");   


    if ( 0 != access(path, R_OK)){

#ifdef DEBUG
        printf("blackbox 디렉토리 생성\n");
        printf("%s\n", path);
#endif
        if((ret=mkdir(path, 0755) == -1)){
            perror("mkdir");
			return -1;
        }
    }

	// 디렉토리 경로 저장
    strcat(path, dir_name);

    if ( 0 != access(path, R_OK)){
#ifdef DEBUG
        printf("시간  디렉토리 생성\n");
        printf("%s\n", path);
#endif 
        if((ret=mkdir(path, 0755) == -1)){
            perror("mkdir");
			return -1;
        }
    } else{
        printf("directory alreay exists!\n");
		return 0;
    }

}

// 디렉토리 내 파일 리스트 반환
int get_DiretoryLIst(const char* base_path, struct  dirent ***namelist) {
	int     count;
	int     idx;
		
	if ((count = scandir(base_path, namelist, NULL, alphasort)) == -1) {
		fprintf(stderr, "%s Directory Scan Error: %s\n", base_path, strerror(errno));
		printf("%s\n", base_path);
		return -1;
	}

	//for (idx = 0; idx < count; idx++) {
	//	printf("%s\n", (*namelist)[idx]->d_name);
	//}

	////건별 데이터 메모리 해제
	//for (idx = 0; idx < count; idx++) {
	//	free(namelist[idx]);
	//}

	//// namelist에 대한 메모리 해제
	//free(namelist);

	return count;
}

// directory 및 하위 file 삭제
int rmdirs(const char *path, int is_error_stop) {
	DIR * dir_ptr = NULL;
	struct dirent *file = NULL;
	struct stat buf;
	char filename[1024];
	
	// directory를 oepndir로 읽음
	if ((dir_ptr = opendir(path)) == NULL) {
		return unlink(path);
	}
	
	while ((file = readdir(dir_ptr)) != NULL) {
		
		if (file->d_name[0] == '.') {
			continue;
		}
		sprintf(filename, "%s/%s", path, file->d_name);
		

		if (lstat(filename, &buf) == -1) {
			continue;
		}

		//검색된 파일 이름이 directory 일 때 rmdirs를 재귀로 부름
		if (S_ISDIR(buf.st_mode)) {
			if (rmdirs(filename, is_error_stop) == -1 && is_error_stop) {
				return -1;
			}
		}
		else if(S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode)){
			if (unlink(filename) == -1 && is_error_stop)
				return -1;
			
		}
	}

#ifdef DEBUG
	printf("디렉토리 하위 파일 삭제 완료\n");
#endif // DEBUG
	
	closedir(dir_ptr);

	return rmdir(path);
}

// 디렉토리, 하위 파일 삭제
int rm_directory(char *base_path) {
	int cnt;
	struct dirent **dir_list;
	char dir_name[64];
	strcpy(dir_name, base_path);
	if ((cnt = get_DiretoryLIst(dir_name, &dir_list)) == -1) {
		perror("get_Directory error");
		return -1;
	}

	// 오래된 디렉토리 찾기
	for (int i = 0; i < cnt; i++) {
		if (dir_list[i]->d_name[0] != '.') {
			strcat(dir_name, dir_list[i]->d_name);
			break;
		}
	}

	// 디렉토리 삭제
	if (rmdirs(dir_name, 1) == -1) {
		//dir_list 데이터 메모리 해제
		for (int i = 0; i < cnt; i++) {
			free(dir_list[i]);
		}
		free(dir_list);

		perror("rmdirs error");
		return -1;
	}

	//dir_list 데이터 메모리 해제
	for (int i = 0; i < cnt; i++) {
		free(dir_list[i]);
	}
	free(dir_list);

	return 0;
}

// 현재 사용 가능 용량 확인
float get_AvailableSpace(const char* path)
{
	struct statvfs stat;

	// error happens, just quits here
	if (statvfs(path, &stat) != 0) {
		perror("statvfs error");
		return -1;
	}

	return (float)stat.f_bavail / (float) stat.f_blocks;
}

//// blackbox 녹화
//void rec_Video() {}

//// 디바이스 연결 상태 확인
//void chk_devide() {}
//

