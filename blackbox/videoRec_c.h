#ifndef VIDEOREC_C_H
#define VIDEOREC_C_H

#ifdef __cplusplus
extern "C" {
#endif
	   

void* creat_CvVideoCapture(int width, int height, double fps);

void destroy_CvVideoCapture(void* instance);

int check_Camera(void* instance);

int record_Video(void* instance, char* path, int rec_time);

#ifdef __cplusplus
}
#endif

#endif
