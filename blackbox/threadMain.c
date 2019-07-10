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
#include <pthread.h>

//#define __USE_XOPEN  // strptime을 사용하기 위해 추가
#include <time.h>

//#include "videoRec_c.h"

#define DEBUG

char base_path[] = "/home/song/blackbox/";

extern struct tm get_time(char*, char type);
extern int make_directory(const char*);
extern int get_DirectoryList(const char*, struct dirent ***);
extern int rmdirs(const char *, int);
extern int rm_directory(char *base_path);
extern float get_AvailableSpace(const char*);
void *rec_Video(void *data);

int main() {
	float disk_size;
	pthread_t p_thread[2];
	int thr_id[2];
	int flag = 0;
	int start_time, end_time = 0;
	
	
	// device 확인
	if (make_directory(base_path) == -1) {
		/*perror("make_directory error");*/
		printf("directory already existed.\n");
	}
	else {
		printf("%s directory create~!", base_path);
	}


	while (1) {
		//disk 용량확인
		if ((disk_size = get_AvailableSpace(base_path)) < 0.7) {
			printf("main size : %f\n", disk_size);
			rm_directory(base_path);
		}else printf("main size : %f\n", disk_size);

		// video 녹화
		if (end_time < time(0)) {

			if (flag == 0) {
				start_time = time(0);
				thr_id[0] = pthread_create(&p_thread[0], NULL, rec_Video, (void*)&start_time);
				if (thr_id[0] < 0) {
					perror("thr_id[0] create error");
					exit(0);
				}
				pthread_detach(p_thread[0]);
				end_time = start_time + 10;
				flag = 1;
			}
			else if (flag == 1) {
				start_time = time(0);
				thr_id[1] = pthread_create(&p_thread[1], NULL, rec_Video, (void*)&start_time);
				if (thr_id[1] < 0) {
					perror("thr_id[0] create error");
					exit(0);
				}
				pthread_detach(p_thread[1]);
				end_time = start_time + 10;
				flag = 0;
			}
		}

		sleep(1);
	}


	return 0;
}

void *rec_Video(void *data) {
	// 비디오 녹화 thread
	int * time = (int *)data;
	char file_name[16], dir_name[12], path[60];
	get_time(dir_name, 'd');

	strcpy(path, base_path);
	strcat(path, dir_name);
	strcat(path, "/");

#ifdef DEBUG
	int t_id = pthread_self();
	printf("thread: %u create, start_time : %u \n", t_id, *time);
#endif


	// 디렉토리 확인 후 생성
	if (make_directory(dir_name) == -1) {
		perror("make_directory error");
		printf("directory already existed.\n");
	}
	else {
		printf("%s directory create~!\n", path);
	}

	// 비디오 녹화
	// function
	get_time(file_name, 'f');
	strcat(path, file_name);
	strcat(path, ".avi");

#ifdef DEBUG
	printf("file name: %s\n", path);
	for (int i = 0; i < 10; i++) {
		sleep(1);
		printf("thread %u, %d\n", t_id, i);
	}

	printf("thread: %u finished \n", t_id);
#endif
}

