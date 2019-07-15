#include "videoRec.h"

char base_path[] = "/home/nvidia/blackbox/";

int main() {
	float disk_size;
	pthread_t p_thread;
	int thr_id;
	int flag = 0;
	
	
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

	
	// thread : video recording
	printf("thread 2 start ----------------------------\n");
	thr_id = pthread_create(&p_thread, NULL, rec_Video, (void*)&cap);
	if (thr_id < 0) {
		perror("thr_id[0] create error");
		exit(0);
	}
	pthread_detach(p_thread);

	while (1) {

		//disk 용량확인
		if ((disk_size = get_AvailableSpace(base_path)) < 0.4) {
			printf("main size : %f\n", disk_size);
			rm_directory(base_path);
		}
		else printf("main size : %f\n", disk_size);

		sleep(1);
	}


	return 0;
}

