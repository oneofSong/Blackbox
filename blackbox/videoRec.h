#ifndef VIDEOREC_H
#define VIDEOREC_H


#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>


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

	CvVideoCapture();
	CvVideoCapture(int width, int height, double fps);
	string get_tegra_pipline(int width, int height, double fps);
	int recordVideo(string path,int rec_time);
	int videoisOpened();
};



#endif
