#include "videoRec.h"


CvVideoCapture::CvVideoCapture(int input_width, int input_height, double input_fps) {

	width = input_width;
	height = input_height;
	fps = input_fps;
	size = Size(width, height);
	get_tegra_pipline(width, height, fps);
	VideoCapture capture(gst);
	cap = capture;

}

string CvVideoCapture::get_tegra_pipline(int width, int height, double fps) {
	gst = "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + patch::to_string(width) + \
		", height=(int)" + patch::to_string(height) + ",format=(string)NV12, framerate=(fraction)" \
		+ patch::to_string(fps) + "/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";

	/*gst = "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + \
		", height=(int)" + std::to_string(height) + ",format=(string)NV12, framerate=(fraction)" \
		+ std::to_string(fps) + "/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";*/
}

int CvVideoCapture::recordVideo(string path, int rec_time) {
	recordFlag = true;

	int end_time;

	writer.open(path, VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, size, true);

	if (!writer.isOpened())
	{
		cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
		return -1;
	}

	end_time = std::time(0) + rec_time * 60;

	while (recordFlag)
	{
		cap.read(img_color);

		if (img_color.empty()) {
			cerr << "빈 영상입니다.\n";
			break;
		}

		writer.write(img_color);

		waitKey(25);

		if (end_time < std::time(0))
			break;
	}
	return 0;
}

int CvVideoCapture::videoisOpened() {

	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
		return -1;
	}

	return 0;
}


//void* creat_CvVideoCapture(int width, int height, double fps) {
//        CvVideoCapture* cap = new CvVideoCapture(width,height,fps);
//    	return (void *)cap;
//	};
//
//void destroy_CvVideoCapture(void *instance) {
//        CvVideoCapture* cap = (CvVideoCapture*) instance;
//		delete cap;
//	};
//
//int check_Camera(void* instance) {
//        CvVideoCapture *cap = (CvVideoCapture *) instance;
//		return cap->videoisOpened();
//	};
//
//int record_Video(void* instance, char* path,int rec_time) {
//		int res;
//        CvVideoCapture* cap = (CvVideoCapture *) instance;
//		res = cap->recordVideo(path, rec_time);
//
//		return res;
//	};


int main() {


}