// DetectionSystem.h : Defines the entry point for the console application.
//

#ifndef DetectionSystem_H
#define DetectionSystem_H

#include "Camera.h"
#include "Tool.h"
#include "Pipe.h"

class DetectionSystem {
	Camera trayCamera;
	Camera stockCamera;
	Camera productCamera;
	Tool tool;	
	Pipe pipe;
	
	bool checkOrientation(cv::Mat image);
	cv::Mat detectColourHSV(cv::Mat image, int lowHue, int highHue, int lowSat, int highSat, int lowVal, int highVal);
	cv::Point detectSinglePoint(cv::Mat image);
	Tray checkTray(cv::Mat image);
	Tray checkProductTray(cv::Mat image);
	Tray detectTray(cv::Mat image, CameraType type);
	cv::RotatedRect findTray(cv::vector<cv::RotatedRect> rotatedRects, CameraType type, bool* error);

	
	bool calibrateAction(std::string action);
	void calibrateStock();
	void calibrateProduct();

	std::string checkSystem();
	std::string checkTray();
	std::string checkTablet(std::vector<std::string> parameters);
	std::string checkProduct(std::vector<std::string> parameters);	
	std::string DetectionSystem::checkProductTray();

	Tablet findTablet(cv::vector<Tablet> tablets, Colour colour);
	Tablet findTablet(cv::vector<Tablet> tablets, std::vector<std::string> parameters);
	bool compareProductToOrder(cv::vector<Tablet> product, std::vector<std::string> order);
	Colour getColour(std::string colour);
	bool hasTablets(cv::vector<Tablet> tablets, int number, Colour colour);
	bool compareString(std::string str1, std::string str2);
public:
	DetectionSystem();	
	void run();
	void calibrate();
};

#endif