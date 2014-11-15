// DetectionSystem.h : Defines the entry point for the console application.
//

#ifndef DetectionSystem_H
#define DetectionSystem_H

#include "Camera.h"
#include "Tool.h"

class DetectionSystem {
	Camera trayCamera;
	Camera stockCamera;
	Tool tool;	
	
	bool checkOrientation(cv::Mat image);
	cv::Mat detectColourHSV(cv::Mat image, int lowHue, int highHue, int lowSat, int highSat, int lowVal, int highVal);
	cv::Point detectSinglePoint(cv::Mat image);
	Tray checkTray(cv::Mat image);
	Tray detectTray(cv::Mat image);
	cv::RotatedRect findTray(cv::vector<cv::RotatedRect> rotatedRects, bool* error);

	
	void selectMode();
	void run();
	void calibrate();
	void test();
	bool testAction(std::string action);
	bool calibrateAction(std::string action);
	void calibrateStock();

public:
	DetectionSystem();
	void checkSystem();
	void checkTray();
	void checkTablet();
	void checkProdut();	
};

#endif