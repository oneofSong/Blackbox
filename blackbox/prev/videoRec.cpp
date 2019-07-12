#include "videoRec.h"

CvVideoCapture::CvVideoCapture(int width, int height, double fps) {

	this->width = width;
	this->height = height;
	this->fps = fps;
	this->size = Size(width, height);
	this->get_tegra_pipline(width, height, fps);
	VideoCapture capture(gst);
	this->cap = capture;
}

void CvVideoCapture::get_tegra_pipline(int width, int height, double fps) {
	this->gst = "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + patch::to_string(width) + \
		", height=(int)" + patch::to_string(height) + ",format=(string)NV12, framerate=(fraction)" \
		+ patch::to_string(fps) + "/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";

}


int CvVideoCapture::recordVideo(string path, int rec_time) {
	recordFlag = true;

//	int end_time;
	writer.open("appsrc ! autovideoconvert ! omxh265enc ! matroskamux ! filesink location="+path, VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, size, true);

	if (!writer.isOpened())
	{
		cerr << "Videowriter error" << endl;
		return -1;
	}

//	end_time = std::time(0) + rec_time * 60 ;

//	cout << end_time << endl;

	while (recordFlag)
	{
		cap.read(img_color);

		if (img_color.empty()) {
			cerr << "image is empty\n";
			break;
		}
		
		writer.write(img_color);

		imshow(path, img_color);
		waitKey(25);

		if (std::time(0)%60 == 59)
			break;
	}
	destroyAllWindows();
	return 0;
}

int CvVideoCapture::videoisOpened() {

	if (!cap.isOpened()) {
		cerr << "camera isn't opened\n";
		return -1;
	}

	return 0;
}



/*
int main() {
	CvVideoCapture cap(720, 460, 30);

	if(cap.videoisOpened() == 0)
		cout << "camera is opened" << endl;

	cap.recordVideo("./20190710_131524.avi", 1);

	
	while(1){

		cap.cap.read(cap.img_color);
		
		imshow("test",cap.img_color);
		
		waitKey(25);

	}

	
	return 0;

}
*/
