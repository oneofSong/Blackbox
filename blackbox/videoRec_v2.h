#ifndef VIDEOREC_H
#define VIDEOREC_H


#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

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
#include <time.h>
#include <sys/time.h>



#define DEBUG



extern struct tm get_time(char*, char type);
extern int make_directory(const char*);
extern int get_DiretoryLIst(const char*, struct dirent ***);
extern int rm_directory(char *base_path);
extern float get_AvailableSpace(const char*);
extern struct timeval time_differ(struct timeval start_time, struct timeval end_time);

extern void *rec_Video(void *data);
extern void *play_Video(void *data);

using namespace cv;
using namespace std;

namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

class CvVideoCapture {
public:
	VideoCapture cap;
	VideoWriter writer;
	
	Mat img_color;
	string gst;
	int width, height;
	double fps;
	Size size;


	CvVideoCapture(int width, int height, double fps);
	void get_tegra_pipline(int width, int height, double fps);
	int playVideo();
	int recordVideo(string path);
	int videoisOpened();
};


//class CvVideoWriter {
//public:
//	VideoWriter writer;
//
//	bool recordFlag;
//	Size size;
//	double fps;
//	
//	CvVideoWriter(int width, int height, double fps);
//	int recordVideo(string path, Mat* img_corlor);
//};

extern char base_path[];

#endif
