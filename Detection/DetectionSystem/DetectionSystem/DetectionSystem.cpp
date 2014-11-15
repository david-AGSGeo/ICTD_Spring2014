// DetectionSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DetectionSystem.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DetectionSystem test;
	return 0;
}

// Class DetectionSystem : Public
DetectionSystem::DetectionSystem(){
	std::cout << "\n==== Detection System ====\n";
	trayCamera = Camera("Tray Camera", (std::string)tool.trayAddress);
	stockCamera = Camera("Stock Camera", (std::string)tool.stockAddress);

	selectMode();
}

void DetectionSystem::selectMode(){
	std::string input;

	std::cout << ">> Select Mode - a:Main | s:test | d:Calibrate\n";
	std::cout << ">> Input: ";
	std::cin >> input;

	switch (input[0]){
	case 'a':
		run();
		break;
	case 's':
		test();
		break;
	case 'd':
		calibrate();
		break;
	}
}

void DetectionSystem::run(){
	bool end = false;

	std::cout << "\n== Detection System ==\n";
	while (!end){
		// Wait for SCADA input
		std::string input;
		std::cin >> input;
	}
}

void DetectionSystem::test(){
	bool end = false;
	std::string input;

	std::cout << "\n== Detection System Test ==\n";
	std::cout << "e:Exit | h:Help\n";
	std::cout << "a:checkSystem | s:checkTray | d:checkTablet | f:checkProduct\n";
	while (!end){
		// Wait for SCADA input
		std::cout << ">> Input: ";
		std::cin >> input;
		end = testAction(input);
	}
}

bool DetectionSystem::testAction(std::string action){
	switch (action[0]){
	case 'e':
		return true;
	case 'h':
		std::cout << "e:Exit | h:Help\n";
		std::cout << "a:checkSystem | s:checkTray | d:checkTablet | f:checkProduct\n";
		break;
	case 'a':
		checkSystem();
		break;
	case 's':
		checkTray();
		break;
	case 'd':
		checkTablet();
		break;
	case 'f':
		checkProdut();
		break;
	}
	return false;
}

void DetectionSystem::checkSystem(){	
	cv::Mat image = trayCamera.getImage();
	if (image.data)
		image = stockCamera.getImage();
	if (image.data)
		; // Working
	return; // Not Working
}

void DetectionSystem::checkTray(){
	cv::Mat image = trayCamera.getImage();

	// Check Orientation
	if (!checkOrientation(image))
		return;	// Invalid

	// Get Tray
	Tray tray = checkTray(image);  // Detected Tray
}

void DetectionSystem::checkTablet(){
	cv::Mat image = stockCamera.getImage();
	cv::Mat imgGray = tool.initImage(image, cv::COLOR_BGR2GRAY);

	// Get Stock Area
	cv::Rect stockArea(0, 0, 1280, 960);

	// Get Tablets
	cv::vector<Tablet> tablets = tool.detectCircles(imgGray, stockArea, STOCKC);
	tool.detectTablets(&tablets, image, STOCKC);

	// Return Required Tablet
}

void DetectionSystem::checkProdut(){
	cv::Mat image = trayCamera.getImage();
	cv::Mat imgGray = tool.initImage(image, cv::COLOR_BGR2GRAY);

	// Get Tray
	Tray tray = checkTray(image);

	// Get Tabelts
	cv::vector<Tablet> tablets = tool.detectCircles(imgGray, tray.boundingRect, TRAYC);
	tool.detectTablets(&tablets, image, TRAYC);

	// Compare tablets to Order

}

bool DetectionSystem::checkOrientation(cv::Mat image){
	cv::Mat detectImage = detectColourHSV(image, 
		tool.oriLowHue, tool.oriHighHue, 
		tool.oriLowSat, tool.oriHighSat, 
		tool.oriLowVal, tool.oriHighVal);

	return tool.oriRect.contains(detectSinglePoint(detectImage));
}

Tray DetectionSystem::checkTray(cv::Mat image){
	cv::Mat detectImage = detectColourHSV(image, 
		tool.trayLowHue, tool.trayHighHue, 
		tool.trayLowSat, tool.trayHighSat, 
		tool.trayLowVal, tool.trayHighVal);

	return detectTray(detectImage);
}

Tray DetectionSystem::detectTray(cv::Mat image){
	cv::vector<cv::vector<cv::Point>> contours;

	// Detect Tray
	cv::findContours(image, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	cv::vector<cv::RotatedRect> rotatedRects(contours.size());

	for(int i = 0; i < contours.size(); i++){
		cv::approxPolyDP(cv::Mat(contours[i]), contours[i], 3, true);
		rotatedRects[i] = cv::minAreaRect(cv::Mat(contours[i]));
	}

	bool error = false;
	cv::RotatedRect tray = findTray(rotatedRects, &error);

	if (error)
		return Tray();

	return Tray(tray, tool);
}

cv::RotatedRect DetectionSystem::findTray(cv::vector<cv::RotatedRect> rotatedRects, bool* error){
	for (int i = 0; i < rotatedRects.size(); i++)
		if (tool.validTray(rotatedRects[i]))
			return rotatedRects[i];

	*error = true;
	return cv::RotatedRect();
}

cv::Mat DetectionSystem::detectColourHSV(
	cv::Mat image,
	int lowHue, int highHue,
	int lowSat, int highSat,
	int lowVal, int highVal){
		cv::Mat imageHSV;
		cv::Mat imageOut;

		//Convert the captured frame from BGR to HSV
		imageHSV = tool.initImage(image, cv::COLOR_BGR2HSV);

		//Threshold the image
		inRange(imageHSV, cv::Scalar(lowHue, lowSat, lowVal), cv::Scalar(highHue, highSat, highVal), imageOut); 

		//morphological opening (remove small objects from the foreground)
		cv::erode(imageOut, imageOut, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
		cv::dilate(imageOut, imageOut, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5))); 

		//morphological closing (fill small holes in the foreground)
		cv::dilate(imageOut, imageOut, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5))); 
		cv::erode(imageOut, imageOut, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));	

		return imageOut;
}

cv::Point DetectionSystem::detectSinglePoint(cv::Mat image){
	cv::Moments oMoments;

	//Calculate the moments of the image
	oMoments = cv::moments(image);

	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	double dArea = oMoments.m00;

	//calculate the position
	return cv::Point(dM10 / dArea, dM01 / dArea);
}

// Calibration

void DetectionSystem::calibrate(){
	bool end = false;
	std::string input;
	std::cout << "\n== Calibrate Detection System ==\n";
	std::cout << "e:Exit | s:Save | l:Load | h:Help\n";
	std::cout << "o:Orientation | t:Tray | p:Product | c:Stock\n";
	std::cout << "Address> v:Tray | b:Stock\n";
	std::cout << "Measure> m:Tray | n:Stock\n";
	while (!end){
		std::cout << ">> Input: ";
		std::cin >> input;
		end = calibrateAction(input);
	}
	std::cout << "\n== End Calibrate ==\n";
}

// Class DetectionSystem : Private
bool DetectionSystem::calibrateAction(std::string action){
	cv::Mat image;
	switch (action[0]){
	case 'e':
		std::cout << "> Exit calibration mode\n";
		return true;
	case 's':
		tool.writeFile("default");
		break;
	case 'l':
		tool.readFile("default");
		break;
	case 'o':
		image = trayCamera.getImage();
		if (image.data)
			tool.calibrateOri(image);
		break;
	case 't':
		image = trayCamera.getImage();
		if (image.data)
			tool.calibrateTray(image);
		break;
	case 'p':
		tool.calibrateProduct(trayCamera.getImage());
		break;
	case 'c':
		calibrateStock();
		break;
	case 'm':
		image = trayCamera.getImage();
		if (image.data)
			tool.calibrateMeasurement(image, TRAYC);
		break;
	case 'n':
		image = stockCamera.getImage();
		if (image.data)
			tool.calibrateMeasurement(image, STOCKC);
		break;
	case 'v':		
		tool.changeAddress(TRAYC, trayCamera.changeAddress());
		break;
	case 'b':
		tool.changeAddress(STOCKC, stockCamera.changeAddress());
		break;
	case 'h':
		std::cout << "e:Exit | s:Save | l:Load | h:Help\n";
		std::cout << "o:Orientation | t:Tray | c:Stock\n";
		std::cout << "Address> v:Tray | b:Stock\n";
		std::cout << "Measure> m:Tray | n:Stock\n";
		break;
	}
	return false;
}

void DetectionSystem::calibrateStock(){
	std::string input = "";
	cv::Mat image;
	std::cout << "e:Exit | s:Save | l:Load | h:Help\n";
	std::cout << "z:Tablets | a:Area\n";
	std::cout << "x:Blue | c:Green | v:Red | b:Black | n:White\n";

	while (input[0] != 'e'){
		std::cout << ">> Input: ";
		std::cin >> input;
		switch (input[0]){
		case 's':
			tool.writeFile("default");
			break;		
		case 'l':
			tool.readFile("default");
			break;
		case 'z':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStock(image);
			break;
		case 'a':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockArea(image);
			break;
		case 'x':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockBlue(image);
			break;
		case 'c':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockGreen(image);
			break;
		case 'v':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockRed(image);
			break;
		case 'b':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockBlack(image);
			break;
		case 'n':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockWhite(image);
			break;
		case 'h':
			std::cout << "b:Exit | s:Save | l:Load | h:Help\n";
			std::cout << "z:Tablets | a:Area\n";
			std::cout << "x:Blue | c:Green | v:Red | b:Black | n:White\n";
			break;
		}
	}
	std::cout << "> Exit Stock calibration mode\n";
}