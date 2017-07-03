
#include "input.h"


using namespace std;
using namespace cv;

int ACTIVE_THRESHOLD = 200;
int CAPTURE_REGION = 100;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
float BG_ADAPT = 0.1;
int GLOW_FADE = 15;
int SPRITE_SIZE = 64;
double SQRT_2 = 1.414;

input::~input() {
}

input::input() {
}

input::input(bool debug, Constants _constants) {
	capture = VideoCapture(0);
	//this->constants = Constants();
	if (capture.isOpened()) {
		//pMOG = createBackgroundSubtractorMOG();
		frameSize[0] = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
		frameSize[1] = capture.get(CV_CAP_PROP_FRAME_WIDTH);
		//capture.set(CV_CAP_PROP_FPS, 0.55);
		//capture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
		//capture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	}
	else {
		cout << "No camera found on computer" << endl;
		exit(0);
	}
	SCREEN_HEIGHT = frameSize[0];
	SCREEN_WIDTH = frameSize[1];
	this->history = 100;
	this->nGauss = 20;
	this->bgThresh = 0.2;
	this->noise = 7;
	for (int i = 0; i < 4; i++) {
		// bsmog.push_back();
		//Ptr<BackgroundSubtractorMOG2> pMOG = cv::createBackgroundSubtractorMOG2(history, nGauss, true);

		bsmog.push_back(cv::createBackgroundSubtractorMOG2(history, nGauss, true)); // A VERIFIER
		bgAdapt.push_back(BG_ADAPT);
	}
	this->debug = debug;

	debugWindow0 = "Debug window 0";
	debugWindow1 = "Debug window 1";
	debugWindow2 = "Debug window 2";
	debugWindow3 = "Debug window 3";
	debugWindow4 = "Debug window 4";
	debugWindow5 = "Debug window 5";

	if (this->debug) {
		namedWindow(debugWindow0);
		namedWindow(debugWindow1);
		namedWindow(debugWindow2);
		namedWindow(debugWindow3);
		namedWindow(debugWindow4);
		namedWindow(debugWindow5);
	}
	//C++: VideoCapture& VideoCapture::operator >> (Mat& image)?
	//C++ : bool VideoCapture::read(Mat& image)
	// bool success = cap.read(frame);

	capture >> currentFrame;
	//capture.read(currentFrame);
	// currentFrame = capture.read();
	// currentFrame = capture.get(CV_CAP_PROP_POS_FRAMES);
	// currentFrameNbr = capture.get(CV_CAP_PROP_POS_FRAMES);
	//bool success = capture.read(frame);
	//cv::Mat dst;
	cv::flip(currentFrame, currentFrame, 1);

	//flip(currentFrame, currentFrame, 1);


	for (int i = 0; i < 4; i++) {
		saveBackground(currentFrame, i);
		previousState.push_back(false);
		currentState.push_back(false);
	}
	this->t = false;

}


double* input::getFrameSize() {
	return frameSize;
}

void input::adapt(float* matrix) {
	for (int i = 0; i < 4; i++) {
		if (matrix[i]) {
			bgAdapt[i] = BG_ADAPT;
		}
		else
			bgAdapt[i] = 0;
	}
}

void input::saveBackground(Mat frame, int n) {
	cv::Mat dst1;
	cv::Mat dst2;

	cvtColor(frame, dst1, CV_BGR2HSV);
	GaussianBlur(dst1, dst2, Size(7, 7), 0);
	// TODO
	cv::Rect ROI0(0, 0, CAPTURE_REGION, CAPTURE_REGION);
	cv::Rect ROI1(SCREEN_WIDTH - CAPTURE_REGION, 0, CAPTURE_REGION, CAPTURE_REGION);
	cv::Rect ROI2(0, SCREEN_HEIGHT - CAPTURE_REGION, CAPTURE_REGION, CAPTURE_REGION);
	cv::Rect ROI3(SCREEN_WIDTH - CAPTURE_REGION, SCREEN_HEIGHT - CAPTURE_REGION, CAPTURE_REGION, CAPTURE_REGION);

	if (n == 0) background0 = dst2(ROI0);
	if (n == 1) background1 = dst2(ROI1);
	if (n == 2) background2 = dst2(ROI2);
	if (n == 3) background3 = dst2(ROI3);

	/*if (n == 0) background0 = frame(ROI1);
	if (n == 1) background1 = frame[constants.CAPTURE_REGION, constants.SCREEN_WIDTH - constants.CAPTURE_REGION:constants.SCREEN_WIDTH];
	if (n == 2) background2 = frame[constants.SCREEN_HEIGHT - constants.CAPTURE_REGION:constants.SCREEN_HEIGHT, 0 : constants.CAPTURE_REGION];
	if (n == 3) background3 = frame[constants.SCREEN_HEIGHT - constants.CAPTURE_REGION:constants.SCREEN_HEIGHT, constants.SCREEN_WIDTH - Constants.CAPTURE_REGION : constants.SCREEN_WIDTH];*/

}

bool input::checkDifference(int n, Mat roi) {

	Mat roi2;
	Mat roi3;
	//roi2.copySize(roi);

	cvtColor(roi, roi2, CV_BGR2HSV);
	GaussianBlur(roi2, roi3, Size(7, 7), 0);

	Mat mask;
	bsmog[n]->apply(roi3, mask, bgAdapt[n]);
	//int result = bsmog[n].operator()(roi, fgMaskMog);

	if (debug) {
		if (n == 0) {
			imshow(debugWindow0, roi3);
		}
		if (n == 1) {
			imshow(debugWindow1, roi3);
		}
		if (n == 2) {
			imshow(debugWindow2, roi3);
		}
		if (n == 3) {
			imshow(debugWindow3, roi3);
		}
	}

	number = countNonZero(mask);

	if (number > ACTIVE_THRESHOLD)
		return true;
	return false;
}

bool input::isActive(int n) {
	//Mat frame = cv::Mat(currentFrame.rows, currentFrame.cols, CV_8UC3);
	Mat frame = currentFrame;
	cv::Rect ROI0(0, 0, CAPTURE_REGION, CAPTURE_REGION);
	cv::Rect ROI1(SCREEN_WIDTH - CAPTURE_REGION, 0, CAPTURE_REGION, CAPTURE_REGION);
	cv::Rect ROI2(0, SCREEN_HEIGHT - CAPTURE_REGION, CAPTURE_REGION, CAPTURE_REGION);
	cv::Rect ROI3(SCREEN_WIDTH - CAPTURE_REGION, SCREEN_HEIGHT - CAPTURE_REGION, CAPTURE_REGION, CAPTURE_REGION);

	if (n == 0) return checkDifference(1, frame(ROI1));
	if (n == 1) return checkDifference(0, frame(ROI0));
	if (n == 2) return checkDifference(3, frame(ROI3));
	if (n == 3) return checkDifference(2, frame(ROI2));
}

void input::updateState() {
	for (int i = 0; i < 4; i++) {
		previousState.at(i) = currentState.at(i);
		currentState.at(i) = isActive(i);
	}
}

bool input::toggled(int n) {
	return currentState[n];
}


std::vector<int> input::getCurrentFrame() {
	return currentFrame;
}

sf::Image input::getCurrentFrameAsImage() {
	capture >> currentFrame;
	sf::Image image;
	cv::Mat copy;
	cvtColor(currentFrame, copy, cv::COLOR_BGR2RGBA);
	//imshow(debugWindow0, copy);
	//flip(copy, copy, 1);
	image.create(copy.cols, copy.rows, copy.ptr());
	image.flipHorizontally();
	//pgImg = pygame.image.frombuffer(im.tostring(), getSize(im), "RGB");
	return image;
}

/**void input::run() {
currentFrame = capture.read(frame);
flip(currentFrame, currentFrame, 1);
updateState();
waitKey(1);
}**/


void input::run() {
	capture >> currentFrame;
	flip(currentFrame, currentFrame, 1); // TODO ?
	updateState();
	waitKey(1);
}
