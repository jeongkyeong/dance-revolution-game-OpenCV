#ifndef INPUT_H
#define INPUT_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <SFML/Graphics/Image.hpp>
//#include <opencv2/bgsegm.hpp>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <sstream>
#include "Constants.h"


using namespace cv;
using namespace std;

class input {
public:
	input();
	input(bool debug, Constants _constants);
	~input();

	Constants constants;
	int device;
	int rc;
	int history;
	int nGauss;
	double bgThresh;
	int noise;
	double frameSize[2];


	Mat src;
	Mat currentFrame;
	double currentFrameNbr;
	sf::Image pgImg;
	VideoCapture capture;
	//int* bsmog;

	std::vector<Ptr<BackgroundSubtractorMOG2>> bsmog;
	Ptr<BackgroundSubtractor> pMOG;
	std::vector<float> bgAdapt;
	bool debug;
	int number = 0;
	bool t;

	String debugWindow0;
	String debugWindow1;
	String debugWindow2;
	String debugWindow3;
	String debugWindow4;
	String debugWindow5;

	Mat	background0;
	Mat	background1;
	Mat	background2;
	Mat	background3;
	Mat	background4;
	Mat	background5;

	std::vector<bool> previousState;
	std::vector<bool> currentState;


	/******** METHOD ********/

	double* getFrameSize();
	void adapt(float*);
	void saveBackground(Mat, int);
	bool checkDifference(int, Mat);
	bool isActive(int);
	void updateState();
	bool toggled(int);
	std::vector<int> getCurrentFrame();
	sf::Image getCurrentFrameAsImage();
	void run();

};

#endif