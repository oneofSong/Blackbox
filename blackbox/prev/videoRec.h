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
	Size size;
	string gst;
	bool recordFlag;
	int width, height;
	double fps;
	int time;

	CvVideoCapture(int width, int height, double fps);
	void get_tegra_pipline(int width, int height, double fps);
	int recordVideo(string path,int rec_time);
	int videoisOpened();
};

extern struct tm get_time(char*, char type);
extern int make_directory(const char*);
extern int get_DirectoryList(const char*, struct dirent ***);
extern int rm_directory(char *base_path);
extern float get_AvailableSpace(const char*);


#endif
