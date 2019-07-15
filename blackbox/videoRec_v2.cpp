#include "videoRec.h"

CvVideoCapture::CvVideoCapture(int width, int height, double fps) {

	this->width = width;
	this->height = height;
	this->fps = fps;
	this->get_tegra_pipline(width, height, fps);
	this->size = Size(width, height);
	VideoCapture capture(gst);
	this->cap = capture;
}

void CvVideoCapture::get_tegra_pipline(int width, int height, double fps) {
	this->gst = "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + patch::to_string(width) + \
		", height=(int)" + patch::to_string(height) + ",format=(string)NV12, framerate=(fraction)" \
		+ patch::to_string(fps) + "/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";

}


int CvVideoCapture::playVideo() {
	
	while (1)
	{
		cap.read(this->img_color);

		if (this->img_color.empty()) {
			cerr << "image is empty\n";
			break;
		}
		
		imshow("play", this->img_color);

		if (waitKey(35) == 27) 
			break;

	}
	destroyAllWindows();
	return 0;
}

int CvVideoCapture::recordVideo(string path) {
	struct timeval start, end, current;

	gettimeofday(&start, NULL);
	end.tv_sec = start.tv_sec + 59;
	if (start.tv_usec + 500000 > 1000000)
		end.tv_usec = start.tv_usec + 500000;
	this->writer.open("appsrc ! autovideoconvert ! omxh265enc ! matroskamux ! filesink location=" + path, \
		VideoWriter::fourcc('X', 'V', 'I', 'D'), this->fps, this->size, true);

	if (!this->writer.isOpened())
	{
		cerr << "Videowriter error" << endl;
		return -1;
	}

#ifdef DEBUG
	int t_id = pthread_self();
	printf("thread created : %u , start_time : %ld  \n", t_id, time(0));
#endif

	while (1)
	{
		gettimeofday(&current, NULL);

		this->cap.read(this->img_color);

		if (this->img_color.empty()) {
			cerr << "image is empty\n";
			break;
		}

		this->writer.write(this->img_color);
		imshow("play", this->img_color);

		waitKey(20);

		if (current.tv_sec > end.tv_sec && current.tv_usec > end.tv_usec)
			break;
	}
	writer.release();

	return 0;
}

int CvVideoCapture::videoisOpened() {

	if (!cap.isOpened()) {
		cerr << "camera isn't opened\n";
		return -1;
	}

	return 0;
}
//
//CvVideoWriter::CvVideoWriter(int width, int height, double fps) {
//	this->fps = fps;
//	this->size = Size(width, height);
//}
//
//int CvVideoWriter::recordVideo(string path, Mat* img_color) {
//	struct timeval start, end, result;
//	gettimeofday(&start, NULL);
//	end.tv_sec = start.tv_sec + 59;
//	if(start.tv_usec + 500000 > 1000000)
//		end.tv_usec = start.tv_usec + 500000;
//	writer.open("appsrc ! autovideoconvert ! omxh265enc ! matroskamux ! filesink location=" + path, \
//		VideoWriter::fourcc('X', 'V', 'I', 'D'), this->fps, this->size, true);
//
//	if (!writer.isOpened())
//	{
//		cerr << "Videowriter error" << endl;
//		return -1;
//	}
//
//#ifdef DEBUG
//	int t_id = pthread_self();
//	printf("thread created : %u , start_time : %ld  \n", t_id, time(0));
//#endif
//
//	while (1)
//	{
//		result = time_differ(start, end);
//
//		if (img_color->empty()) {
//			cerr << "image is empty\n";
//			break;
//		}
//
//		writer.write(*img_color);
//
//		waitKey(15);
//
//		if (result.tv_sec > end.tv_sec && result.tv_usec > end.tv_usec )
//			break;
//	}
//	writer.release();
//	
//	return 0;
//}
