#include "videoRec.h"

//#define DEBUG

char base_path[] = "/home/nvidia/blackbox/";


void *rec_Video(void *data);

int main() {
	float disk_size;
	pthread_t p_thread[2];
	int thr_id[2];
	int flag = 0;
	time_t start_time, end_time = 0;
	
	
	// device check 
	if (make_directory(base_path) == -1) {
		/*perror("make_directory error");*/
		printf("directory already existed.\n");
	}
	else {
		printf("%s directory create~!", base_path);
	}


	CvVideoCapture cap = CvVideoCapture(720,480,30);
       	if(cap.videoisOpened() == 0)
		cout << "camera is opened" << endl;
	else cout << "video isn't opened" << endl;

	while (1) {
		//disk 용량확인
		start_time = time(0);
		if ((disk_size = get_AvailableSpace(base_path)) < 0.5) {
			rm_directory(base_path);
		       	printf("cur_time : %s main size : %f \n",ctime(&start_time), disk_size);
		}else{
		       	printf("cur_time : %s main size : %f \n",ctime(&start_time), disk_size);
			ctime(&start_time);
		}

		// video 녹화
		if (time(0) % 60 == 0) {

			if (flag == 0) {
				start_time = time(0);
				printf("thread 1 start ----------------------------\n");
				thr_id[0] = pthread_create(&p_thread[0], NULL, rec_Video, (void*)&cap);
				if (thr_id[0] < 0) {
					perror("thr_id[0] create error");
					exit(0);
				}
				pthread_detach(p_thread[0]);
				end_time = start_time + 60;
				flag = 1;
			}
			else if (flag == 1) {
				start_time = time(0);
				printf("thread 2 start ----------------------------\n");
				thr_id[1] = pthread_create(&p_thread[1], NULL, rec_Video, (void*)&cap);
				if (thr_id[1] < 0) {
					perror("thr_id[0] create error");
					exit(0);
				}
				pthread_detach(p_thread[1]);
				end_time = start_time + 60;
				flag = 0;
			}

		}

		sleep(1);
	}


	return 0;
}

void *rec_Video(void *data) {
	// 비디오 녹화 thread
	CvVideoCapture* cap = (CvVideoCapture *)data;
	char file_name[16], dir_name[12], path[60];
	get_time(dir_name, 'd');

	strcpy(path, base_path);
	strcat(path, dir_name);
	strcat(path, "/");

#ifdef DEBUG
	int t_id = pthread_self();
	printf("thread: %u create, start_time : %ld \n", t_id, time(0));
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

	cap->recordVideo(path, 1);

#ifdef DEBUG
	printf("thread: %u finished \n", t_id);
#endif
}

