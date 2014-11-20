// Tool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tool.h"

// Class Tool : Public
Tool::Tool() {
	readFile("default");
	//newData();
}

Tool::Tool(std::string profile){
	readFile(profile);	
}

void Tool::calibrateOri(cv::Mat image){
	active = ORI;
	std::cout << "\n= Calibrate Tray Orientation =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";
	std::cout << "arrows:Move Rect\n";	

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&oriLowHue, &oriHighHue, 
		&oriLowSat, &oriHighSat, 
		&oriLowVal, &oriHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			oriLowHue, oriHighHue, 
			oriLowSat, oriHighSat, 
			oriLowVal, oriHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);
		cv::rectangle(imgLines, oriRect, cv::Scalar(0, 255, 0), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y) + 
			" Inside: " + std::to_string(oriRect.contains(point)),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateTray(cv::Mat image){
	active = TRAY;
	std::cout << "\n= Calibrate Tray Detection =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;
	cv::vector<cv::vector<cv::Point>> contours;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&trayLowHue, &trayHighHue, 
		&trayLowSat, &trayHighSat, 
		&trayLowVal, &trayHighVal);

	while (keyPress(cvWaitKey(33))){		
		imgThresholded = thresholdImage(
			imgHSV, 
			trayLowHue, trayHighHue, 
			trayLowSat, trayHighSat, 
			trayLowVal, trayHighVal);

		// Find all contours in the image
		cv::findContours(imgThresholded, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));		

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);
		cv::vector<cv::RotatedRect> rotatedRects(contours.size());

		cv::line(imgLines, trayPoint, trayPoint, cv::Scalar(0, 255, 0), 6);

		cv::Point center;
		for(int i = 0; i < contours.size(); i++){
			cv::approxPolyDP(cv::Mat(contours[i]), contours[i], 3, true);
			rotatedRects[i] = cv::minAreaRect(cv::Mat(contours[i]));

			cv::drawContours(imgLines, contours, i, cv::Scalar(0,0,255), 1);
		}

		if (rotatedRects.size() > 0){
			cv::RotatedRect tray = detectTray(rotatedRects, TRAYC);

			cv::Point2f points[4];
			tray.points(points);
			center = tray.center;
			// Draw
			cv::line(imgLines, tray.center, tray.center, cv::Scalar(255, 0, 0), 3);			
			for (int j = 0; j < 4; j++)
				cv::line(imgLines, points[j], points[(j + 1) % 4], cv::Scalar(255, 255, 0), 2);			


			int x, y, d;
			offset(center, trayPoint, &x, &y, &d);


			cv::putText(imgLines, 
				"Width: " + std::to_string(length(tray.size.width, TRAYC)) + 
				"mm Height: " + std::to_string(length(tray.size.height, TRAYC)) + 
				"mm Angle: " + std::to_string(tray.angle) +
				" offset: (" + std::to_string(length(x, TRAYC)) + 
				", " + std::to_string(length(y, TRAYC)) + 
				") - " + std::to_string(length(d, TRAYC)) + "mm", 
				cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		}
		updateDisplay(image + imgLines, imgThresholded);
	}
	cv::destroyAllWindows();
}

void Tool::calibrateProductTray(cv::Mat image){
	active = PRODUCTTRAY;
	std::cout << "\n= Calibrate Product Tray Detection =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;
	cv::vector<cv::vector<cv::Point>> contours;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&productLowHue, &productHighHue, 
		&productLowSat, &productHighSat, 
		&productLowVal, &productHighVal);

	while (keyPress(cvWaitKey(33))){		
		imgThresholded = thresholdImage(
			imgHSV, 
			productLowHue, productHighHue, 
			productLowSat, productHighSat, 
			productLowVal, productHighVal);

		// Find all contours in the image
		cv::findContours(imgThresholded, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));		

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);
		cv::vector<cv::RotatedRect> rotatedRects(contours.size());

		cv::line(imgLines, productPoint, productPoint, cv::Scalar(0, 255, 0), 6);

		cv::Point center;
		for(int i = 0; i < contours.size(); i++){
			cv::approxPolyDP(cv::Mat(contours[i]), contours[i], 3, true);
			rotatedRects[i] = cv::minAreaRect(cv::Mat(contours[i]));

			cv::drawContours(imgLines, contours, i, cv::Scalar(0,0,255), 1);
		}

		if (rotatedRects.size() > 0){
			cv::RotatedRect tray = detectTray(rotatedRects, PRODUCTC);

			cv::Point2f points[4];
			tray.points(points);
			center = tray.center;
			// Draw
			cv::line(imgLines, tray.center, tray.center, cv::Scalar(255, 0, 0), 3);			
			for (int j = 0; j < 4; j++)
				cv::line(imgLines, points[j], points[(j + 1) % 4], cv::Scalar(255, 255, 0), 2);			


			int x, y, d;
			offset(center, productPoint, &x, &y, &d);


			cv::putText(imgLines, 
				"Width: " + std::to_string(length(tray.size.width, PRODUCTC)) + 
				"mm Height: " + std::to_string(length(tray.size.height, PRODUCTC)) + 
				"mm Angle: " + std::to_string(tray.angle) +
				" offset: (" + std::to_string(length(x, PRODUCTC)) + 
				", " + std::to_string(length(y, PRODUCTC)) + 
				") - " + std::to_string(length(d, PRODUCTC)) + "mm", 
				cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		}
		updateDisplay(image + imgLines, imgThresholded);
	}
	cv::destroyAllWindows();
}

void Tool::calibrateProduct(cv::Mat image){
	active = PRODUCT;
	std::cout << "\n= Calibrate Stock Detection =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgText,
		imgHSV,
		imgGray,
		imgThresholded;
	cv::vector<cv::vector<cv::Point>> contours;
	cv::vector<Tablet> tabletsOld;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);
	imgGray = initImage(image, cv::COLOR_BGR2GRAY);

	imgThresholded = thresholdImage(
		imgHSV, 
		trayLowHue, trayHighHue, 
		trayLowSat, trayHighSat, 
		trayLowVal, trayHighVal);

	buildGUI(&trayCanny, &trayAccumulator);

	while (keyPress(cvWaitKey(33))){	
		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		// Detect Tray
		cv::findContours(imgThresholded, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
		cv::vector<cv::RotatedRect> rotatedRects(contours.size());
		for(int i = 0; i < contours.size(); i++){
			cv::approxPolyDP(cv::Mat(contours[i]), contours[i], 3, true);
			rotatedRects[i] = cv::minAreaRect(cv::Mat(contours[i]));
		}
		if (rotatedRects.size() == 0)
			return;
		cv::RotatedRect tray = detectTray(rotatedRects, TRAYC);
		cv::Point2f points[4];
		tray.points(points);		
		for (int j = 0; j < 4; j++)
			cv::line(imgLines, points[j], points[(j + 1) % 4], cv::Scalar(255, 255, 0), 2);		

		// Detect Tablets Positions
		cv::rectangle(imgLines, tray.boundingRect(), cv::Scalar(255, 0, 0), 2);
		cv::vector<Tablet> tablets = detectCircles(imgGray, imgLines, tray.boundingRect(), TRAYC);

		if (!displayOriginal && tabletsChange(tablets, tabletsOld)){
			imgText = cv::Mat::zeros(image.size(), CV_8UC3);
			detectTablets(&tablets, image, TRAYC);

			for (int i = 0; i < tablets.size() && i < 8; i++){
				cv::Size text = cv::getTextSize(tabletToString(tablets[i], TRAYC), CV_FONT_HERSHEY_PLAIN, 1, 1, 0);
				cv::putText(imgText, 
					tabletToString(tablets[i], TRAYC),
					cv::Point(tablets[i].center.x - text.width / 2, tablets[i].center.y),
					CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
			}
			tabletsOld = tablets;
		}

		// Is valid Product
		std::string validString = isValidProduct(tray, tablets);
		cv::putText(imgLines, 
			validString, 
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));

		updateDisplay(image + imgLines, image + imgText);
	}

	cv::destroyAllWindows();
}

void Tool::calibrateProductBlue(cv::Mat image){
	active = PRODUCTCOLOUR;
	std::cout << "\n= Calibrate Product Blue =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&productBlueLowHue, &productBlueHighHue, 
		&productBlueLowSat, &productBlueHighSat, 
		&productBlueLowVal, &productBlueHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			productBlueLowHue, productBlueHighHue, 
			productBlueLowSat, productBlueHighSat, 
			productBlueLowVal, productBlueHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateProductGreen(cv::Mat image){
	active = PRODUCTCOLOUR;
	std::cout << "\n= Calibrate Product Green =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&productGreenLowHue, &productGreenHighHue, 
		&productGreenLowSat, &productGreenHighSat, 
		&productGreenLowVal, &productGreenHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			productGreenLowHue, productGreenHighHue, 
			productGreenLowSat, productGreenHighSat, 
			productGreenLowVal, productGreenHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateProductRed(cv::Mat image){
	active = PRODUCTCOLOUR;
	std::cout << "\n= Calibrate Product Red =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&productRedLowHue, &productRedHighHue, 
		&productRedLowSat, &productRedHighSat, 
		&productRedLowVal, &productRedHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			productRedLowHue, productRedHighHue, 
			productRedLowSat, productRedHighSat, 
			productRedLowVal, productRedHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateProductBlack(cv::Mat image){
	active = PRODUCTCOLOUR;
	std::cout << "\n= Calibrate Product Black =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&productBlackLowHue, &productBlackHighHue, 
		&productBlackLowSat, &productBlackHighSat, 
		&productBlackLowVal, &productBlackHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			productBlackLowHue, productBlackHighHue, 
			productBlackLowSat, productBlackHighSat, 
			productBlackLowVal, productBlackHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateProductWhite(cv::Mat image){
	active = PRODUCTCOLOUR;
	std::cout << "\n= Calibrate Product White =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&productWhiteLowHue, &productWhiteHighHue, 
		&productWhiteLowSat, &productWhiteHighSat, 
		&productWhiteLowVal, &productWhiteHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			productWhiteLowHue, productWhiteHighHue, 
			productWhiteLowSat, productWhiteHighSat, 
			productWhiteLowVal, productWhiteHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateStockArea(cv::Mat image){
	active = STOCKAREA;
	std::cout << "\n= Calibrate Stock Area =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines;

	buildGUI();

	while (keyPress(cvWaitKey(33))){		
		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);
		cv::rectangle(imgLines, stockValidArea, cv::Scalar(255, 0, 0), 2);
		updateDisplay(image + imgLines, image + imgLines);
	}
	cv::destroyAllWindows();
}

void Tool::calibrateStock(cv::Mat image){
	active = STOCK;
	std::cout << "\n= Calibrate Stock Detection =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgText,
		imgThresholded;
	cv::vector<Tablet> tabletsOld;
	cv::vector<cv::vector<cv::Point>> contours;

	buildGUI(&stockCanny, &stockAccumulator);

	imgThresholded = initImage(image, cv::COLOR_BGR2GRAY);

	while (keyPress(cvWaitKey(33))){			
		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);				

		cv::vector<Tablet> tablets = detectCircles(imgThresholded, imgLines, stockValidArea, STOCKC);		

		if (!displayOriginal && tabletsChange(tablets, tabletsOld)){
			imgText = cv::Mat::zeros(image.size(), CV_8UC3);
			detectTablets(&tablets, image, STOCKC);

			for (int i = 0; i < tablets.size() && i < 8; i++){
				cv::Size text = cv::getTextSize(tabletToString(tablets[i], STOCKC), CV_FONT_HERSHEY_PLAIN, 1, 1, 0);
				cv::putText(imgText, 
					tabletToString(tablets[i], STOCKC),
					cv::Point(tablets[i].center.x - text.width / 2, tablets[i].center.y),
					CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
			}
			tabletsOld = tablets;
		}

		cv::line(imgLines, stockPoint, stockPoint, cv::Scalar(0, 255, 0), 6);

		updateDisplay(image + imgLines, image + imgText);
	}
	cv::destroyAllWindows();
}

void Tool::calibrateStockBlue(cv::Mat image){
	active = STOCKCOLOUR;
	std::cout << "\n= Calibrate Stock Blue =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&stockBlueLowHue, &stockBlueHighHue, 
		&stockBlueLowSat, &stockBlueHighSat, 
		&stockBlueLowVal, &stockBlueHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			stockBlueLowHue, stockBlueHighHue, 
			stockBlueLowSat, stockBlueHighSat, 
			stockBlueLowVal, stockBlueHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateStockGreen(cv::Mat image){
	active = STOCKCOLOUR;
	std::cout << "\n= Calibrate Stock Green =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&stockGreenLowHue, &stockGreenHighHue, 
		&stockGreenLowSat, &stockGreenHighSat, 
		&stockGreenLowVal, &stockGreenHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			stockGreenLowHue, stockGreenHighHue, 
			stockGreenLowSat, stockGreenHighSat, 
			stockGreenLowVal, stockGreenHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateStockRed(cv::Mat image){
	active = STOCKCOLOUR;
	std::cout << "\n= Calibrate Stock Red =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&stockRedLowHue, &stockRedHighHue, 
		&stockRedLowSat, &stockRedHighSat, 
		&stockRedLowVal, &stockRedHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			stockRedLowHue, stockRedHighHue, 
			stockRedLowSat, stockRedHighSat, 
			stockRedLowVal, stockRedHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateStockBlack(cv::Mat image){
	active = STOCKCOLOUR;
	std::cout << "\n= Calibrate Stock Black =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&stockBlackLowHue, &stockBlackHighHue, 
		&stockBlackLowSat, &stockBlackHighSat, 
		&stockBlackLowVal, &stockBlackHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			stockBlackLowHue, stockBlackHighHue, 
			stockBlackLowSat, stockBlackHighSat, 
			stockBlackLowVal, stockBlackHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}

void Tool::calibrateStockWhite(cv::Mat image){
	active = STOCKCOLOUR;
	std::cout << "\n= Calibrate Stock White =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";

	cv::Mat imgLines,
		imgHSV,
		imgThresholded;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	buildGUI(
		&stockWhiteLowHue, &stockWhiteHighHue, 
		&stockWhiteLowSat, &stockWhiteHighSat, 
		&stockWhiteLowVal, &stockWhiteHighVal);

	while (keyPress(cvWaitKey(33))){
		imgThresholded = thresholdImage(
			imgHSV, 
			stockWhiteLowHue, stockWhiteHighHue, 
			stockWhiteLowSat, stockWhiteHighSat, 
			stockWhiteLowVal, stockWhiteHighVal);

		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::Point point = getPointofObject(imgThresholded);
		cv::line(imgLines, point, cv::Point(0, 0), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(point.x) + 
			" Y: " + std::to_string(point.y),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, imgThresholded);
	}	
	cv::destroyAllWindows();
}


void Tool::calibrateMeasurement(cv::Mat image, CameraType type){
	active = MEASURE;
	std::cout << "\n= Calibrate Measurement =\n";
	std::cout << "esc:Exit | s:Save Test | r:Load Test | p:Stats\n";
	std::cout << "arrows(Left & Right):Change Length\n";

	cv::Mat imgLines;
	int* measureLength;
	switch (type){
	case TRAYC:
		measureLength = &measureTrayLength;
		break;
	case STOCKC:
		measureLength = &measureStockLength;
		break;
	case PRODUCTC:
		measureLength = &measureProductLength;
		break;
	default:
		measureLength = &measureTrayLength;
	}

	buildGUI();

	while (keyPress(cvWaitKey(33), measureLength)){
		imgLines = cv::Mat::zeros(image.size(), CV_8UC3);

		cv::line(imgLines, measurePoint, cv::Point(measurePoint.x + *measureLength, measurePoint.y), cv::Scalar(0, 0, 255), 2);
		cv::line(imgLines, cv::Point(measurePoint.x, measurePoint.y - 10), cv::Point(measurePoint.x, measurePoint.y + 10), cv::Scalar(0, 0, 255), 2);
		cv::line(imgLines, cv::Point(measurePoint.x + *measureLength, measurePoint.y - 10), cv::Point(measurePoint.x + *measureLength, measurePoint.y + 10), cv::Scalar(0, 0, 255), 2);

		cv::putText(imgLines, 
			"X: " + std::to_string(measurePoint.x) + 
			" Y: " + std::to_string(measurePoint.y) + 
			" Length: " + std::to_string(*measureLength),
			cv::Point(30, 30), CV_FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
		updateDisplay(image + imgLines, image + imgLines);
	}	
	cv::destroyAllWindows();
}

void Tool::changeDisplay(){
	displayOriginal = !displayOriginal;
}

void Tool::writeFile(std::string profile){
	std::ofstream outputFile("/DetectionSystem/save/" + profile + ".sav", std::ios::binary);
	outputFile.write((char*)this, sizeof(Tool));
	outputFile.close();
	std::cout << ">> Tool Saved: " << profile.c_str() << "\n";
}

void Tool::readFile(std::string profile){
	std::ifstream  inputFile("/DetectionSystem/save/" + profile + ".sav", std::ios::binary);
	inputFile.read((char*)this, sizeof(Tool));
	inputFile.close();
	std::cout << ">> Tool Loaded: " << profile.c_str() << "\n";

	//GetPrivateProfileString();
}

void Tool::leftClickEvent(int x, int y, int flags){
	if (flags&cv::EVENT_FLAG_CTRLKEY ){
		switch (active){
		case ORI:
			oriRect.x = x;
			oriRect.y = y;
			std::cout << " - Ori rect moved";
			break;
		case TRAY:
			trayPoint.x = x;
			trayPoint.y = y;
			std::cout << " - Tray point moved";
			break;
		case STOCK:
			stockPoint.x = x;
			stockPoint.y = y;
			std::cout << " - Stock point moved";
			break;
		case MEASURE:
			measurePoint.x = x;
			measurePoint.y = y;
			std::cout << " - Measure point moved";
			break;
		case STOCKAREA:
			stockValidArea.x = x;
			stockValidArea.y = y;
			std::cout << " - Stock rect moved";
			break;
		case PRODUCTTRAY:
			productPoint.x = x;
			productPoint.y = y;
			std::cout << " - Product point moved";
			break;
		}		
	}
}

void Tool::changeAddress(CameraType type, std::string address){
	if (address.length() > 15)
		return;
	if (type == TRAYC)
		strcpy_s(trayAddress, address.c_str());
	else if (type == STOCKC)
		strcpy_s(stockAddress, address.c_str());
	else
		strcpy_s(productAddress, address.c_str());
}

// Class Tool : Private
void Tool::buildGUI(int* canny, int* accumulator){
	buildGUI();

	//Create trackbars in "Control" window
	cv::createTrackbar("Canny", "Control", canny, 255);
	cv::createTrackbar("Accum", "Control", accumulator, 200);
}

void Tool::buildGUI(
	int* lowHue, int* highHue,
	int* lowSat, int* highSat,
	int* lowVal, int* highVal){
		buildGUI();

		//Create trackbars in "Control" window
		cv::createTrackbar("LowH", "Control", lowHue, 179); //Hue (0 - 179)
		cv::createTrackbar("HighH", "Control", highHue, 179);

		cv::createTrackbar("LowS", "Control", lowSat, 255); //Saturation (0 - 255)
		cv::createTrackbar("HighS", "Control", highSat, 255);

		cv::createTrackbar("LowV", "Control", lowVal, 255); //Value (0 - 255)
		cv::createTrackbar("HighV", "Control", highVal, 255);		
}

void Tool::buildGUI(){
	cv::namedWindow("Control", cv::WINDOW_NORMAL);
	cv::namedWindow("Display", cv::WINDOW_AUTOSIZE);
	cv::setMouseCallback("Display", callBackFunc, this);
}

bool Tool::keyPress(int key, int* measureLength){
	switch (key) {
	case 112:		// p
		displayStats();
		break;
	case 114:		// r
		readFile("test");
		break;
	case 115:		// s
		writeFile("test");
		break;	
	case 2424832:	// Left Arrow
		if (active == ORI)
			std::cout << "> Rect width: " << --oriRect.width << "\n";
		else if (active == STOCKAREA)
			std::cout << "> Rect width: " << --stockValidArea.width << "\n";
		else if (active == MEASURE)
			std::cout << "> Measure length: " << --(*measureLength) << "\n";
		break;
	case 2555904:	// Right Arrow
		if (active == ORI)
			std::cout << "> Rect width: " << ++oriRect.width << "\n";
		else if (active == STOCKAREA)
			std::cout << "> Rect width: " << ++stockValidArea.width << "\n";
		else if (active == MEASURE)
			std::cout << "> Measure length: " << ++(*measureLength) << "\n";
		break;
	case 2490368:	// Up Arrow
		if (active == ORI)
			std::cout << "> Rect height: " << --oriRect.height << "\n";
		else if (active == STOCKAREA)
			std::cout << "> Rect width: " << --stockValidArea.height << "\n";
		break;
	case 2621440:	// Down Arrow
		if (active == ORI)
			std::cout << "> Rect height: " << ++oriRect.height << "\n";
		else if (active == STOCKAREA)
			std::cout << "> Rect width: " << ++stockValidArea.height << "\n";
		break;
	}
	return key != 27; //ESC
}

cv::Point Tool::getPointofObject(cv::Mat image){
	cv::Moments oMoments;

	//Calculate the moments of the thresholded image
	oMoments = cv::moments(image);

	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	double dArea = oMoments.m00;

	//calculate the position of the ball
	int posX = dM10 / dArea;
	int posY = dM01 / dArea;   

	return cv::Point(posX, posY);
}

cv::Mat Tool::initImage(cv::Mat image, int type){
	cv::Mat imgRet;	

	//Convert the captured frame from BGR to HSV
	cv::cvtColor(image, imgRet, type); 

	//smooth the original image using Gaussian kernel to remove noise
	cv::GaussianBlur(imgRet, imgRet, cv::Size(3, 3), cv::BORDER_REFLECT);

	return imgRet;
}

cv::Mat Tool::thresholdImage(
	cv::Mat image,
	int lowHue, int highHue,
	int lowSat, int highSat,
	int lowVal, int highVal){
		cv::Mat imgThresholded;

		//Threshold the image
		inRange(image, cv::Scalar(lowHue, lowSat, lowVal), cv::Scalar(highHue, highSat, highVal), imgThresholded); 

		//morphological opening (remove small objects from the foreground)
		cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));
		cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10))); 

		//morphological closing (fill small holes in the foreground)
		cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10))); 
		cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(10, 10)));

		return imgThresholded;
}

void Tool::updateDisplay(cv::Mat original, cv::Mat thresholded){
	if (displayOriginal)
		cv::imshow("Display", original);
	else
		cv::imshow("Display", thresholded);
}


void Tool::displayStats(){
	std::cout << "trayAddress: " << trayAddress  << "\n";
	std::cout << "stockAddress: " << stockAddress << "\n";
	switch (active){
	case ORI:
		std::cout << "oriLowHue: " << oriLowHue << "\n";
		std::cout << "oriHighHue: " << oriHighHue << "\n";
		std::cout << "oriLowSat: " << oriLowSat << "\n";
		std::cout << "oriHighSat: " << oriHighSat << "\n";
		std::cout << "oriLowVal: " << oriLowVal << "\n";
		std::cout << "oriHighVal: " << oriHighVal << "\n";
		std::cout << "oriRect: x(" << oriRect.x << "), y(" << oriRect.y << "), width(" << oriRect.width << "height(" << oriRect.height << ")\n";
		break;
	case TRAY:
		std::cout << "trayLowHue: " << trayLowHue << "\n";
		std::cout << "trayHighHue: " << trayHighHue << "\n";
		std::cout << "trayLowSat: " << trayLowSat << "\n";
		std::cout << "trayHighSat: " << trayHighSat << "\n";
		std::cout << "trayLowVal: " << trayLowVal << "\n";
		std::cout << "trayHighVal: " << trayHighVal << "\n";
		std::cout << "trayPoint: x(" << trayPoint.x << "), y(" << trayPoint.y << ")\n";
		break;
	case STOCK:
		break;
	}
}

cv::RotatedRect Tool::detectTray(cv::vector<cv::RotatedRect> rotatedRects, CameraType type){
	for (int i = 0; i < rotatedRects.size(); i++)
		if (validTray(rotatedRects[i], type))
			return rotatedRects[i];
	return rotatedRects[0];
}

bool Tool::validTray(cv::RotatedRect tray, CameraType type){
	return length(tray.size.width, type) <= TRAYWIDTH + TRAYWIDTHRANGE &&
		length(tray.size.width, type) >= TRAYWIDTH - TRAYWIDTHRANGE &&
		length(tray.size.height, type) <= TRAYHEIGHT + TRAYHEIGHTRANGE &&
		length(tray.size.height, type) >= TRAYHEIGHT - TRAYHEIGHTRANGE;
}

cv::vector<Tablet> Tool::detectCircles(cv::Mat image, cv::Mat imgLines, cv::Rect validArea, CameraType type){
	cv::vector<cv::Vec3f> circles;
	cv::vector<Tablet> tablets;
	int canny = type == STOCKC ? stockCanny : trayCanny,
		accumulator = type == STOCKC ? stockAccumulator : trayAccumulator,
		measure = type == STOCKC ? measureStockLength : measureTrayLength;
	cv::Point point = type == STOCKC? stockPoint : productPoint;

	canny == 0 ? canny = 1 : canny;
	accumulator == 0 ? accumulator = 1 : accumulator;

	/// Apply the Hough Transform to find the circles
	cv::HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1, image.rows/8, canny, accumulator, 
		cvRound(((TABLETRADIUS - 4)/10) * measure), cvRound(((TABLETRADIUS + 8)/10) * measure));

	/// Draw the circles detected
	for(int i = 0; i < circles.size() && tablets.size() < 8; i++ )
	{		
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		if (validArea.contains(center)) {
			tablets.push_back(Tablet(circles[i], point, measure));

			int radius = cvRound(circles[i][2]);
			// circle center
			cv::circle(imgLines, center, 3, cv::Scalar(0, 255, 0), -1);
			// circle outline
			cv::circle(imgLines, center, radius, cv::Scalar(0, 0, 255), 2);
		}
	}
	return tablets;
}

cv::vector<Tablet> Tool::detectCircles(cv::Mat image, cv::Rect validArea, CameraType type){
	cv::vector<cv::Vec3f> circles;
	cv::vector<Tablet> tablets;
	int canny = type == STOCKC ? stockCanny : trayCanny,
		accumulator = type == STOCKC ? stockAccumulator : trayAccumulator,
		measure = type == STOCKC ? measureStockLength : measureTrayLength;
	cv::Point point = type == STOCKC? stockPoint : productPoint;

	canny == 0 ? canny = 1 : canny;
	accumulator == 0 ? accumulator = 1 : accumulator;

	/// Apply the Hough Transform to find the circles
	cv::HoughCircles(image, circles, CV_HOUGH_GRADIENT, 1, image.rows/8, canny, accumulator, 
		cvRound(((TABLETRADIUS - 4)/10) * measure), cvRound(((TABLETRADIUS + 8)/10) * measure));

	/// Draw the circles detected
	for(int i = 0; i < circles.size(); i++ )
	{		
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		if (validArea.contains(center)) {
			tablets.push_back(Tablet(circles[i], point, measure));			
		}
	}
	//detectTablets(&tablets, image, type);

	return tablets;
}

void Tool::detectTablets(cv::vector<Tablet>* tablets, cv::Mat image, CameraType type){
	for(int i = 0; i < tablets->size(); i++ )
	{
		cv::Mat tabletImage = cv::Mat::zeros(image.size(), CV_8UC3),
			mask = cv::Mat::zeros(image.size(), CV_8UC3);

		// Mask tablet i
		cv::circle(mask, (*tablets)[i].center, (*tablets)[i].radius, cv::Scalar(255, 255, 255), -1);

		// Crop out tablet i
		image.copyTo(tabletImage, mask);

		detectTablet(&((*tablets)[i]), tabletImage, type);
	}
}

void Tool::detectTablet(Tablet* tablet, cv::Mat image, CameraType type){
	cv::Mat imgHSV,
		imgThresholded,
		imgLines;	
	cv::Point point;

	imgHSV = initImage(image, cv::COLOR_BGR2HSV);

	if (length(tablet->radius, type) > TABLETRADIUS + TABLETRADUISRANGE  ||
		length(tablet->radius, type) < TABLETRADIUS - TABLETRADUISRANGE){ // 18.5mm
			tablet->valid = false;
			return;
	}

	imgThresholded = type == STOCKC? thresholdImage(imgHSV, stockGreenLowHue, stockGreenHighHue, stockGreenLowSat, stockGreenHighSat, stockGreenLowVal, stockGreenHighVal) :
		thresholdImage(imgHSV, productGreenLowHue, productGreenHighHue, productGreenLowSat, productGreenHighSat, productGreenLowVal, productGreenHighVal);
	point = getPointofObject(imgThresholded);
	if (isDetectedTablet(tablet, point, GREEN))
		return;

	imgThresholded = type == STOCKC? thresholdImage(imgHSV, stockRedLowHue, stockRedHighHue, stockRedLowSat, stockRedHighSat, stockRedLowVal, stockRedHighVal) :
		thresholdImage(imgHSV, productRedLowHue, productRedHighHue, productRedLowSat, productRedHighSat, productRedLowVal, productRedHighVal);
	point = getPointofObject(imgThresholded);
	if (isDetectedTablet(tablet, point, RED))
		return;

	imgThresholded = type == STOCKC? thresholdImage(imgHSV, stockBlackLowHue, stockBlackHighHue, stockBlackLowSat, stockBlackHighSat, stockBlackLowVal, stockBlackHighVal) :
		thresholdImage(imgHSV, productBlackLowHue, productBlackHighHue, productBlackLowSat, productBlackHighSat, productBlackLowVal, productBlackHighVal);
	point = getPointofObject(imgThresholded);
	if (isDetectedTablet(tablet, point, BLACK))
		return;

	imgThresholded = type == STOCKC? thresholdImage(imgHSV, stockWhiteLowHue, stockWhiteHighHue, stockWhiteLowSat, stockWhiteHighSat, stockWhiteLowVal, stockWhiteHighVal) :
		thresholdImage(imgHSV, productWhiteLowHue, productWhiteHighHue, productWhiteLowSat, productWhiteHighSat, productWhiteLowVal, productWhiteHighVal);
	point = getPointofObject(imgThresholded);
	if (isDetectedTablet(tablet, point, WHITE))
		return;

	imgThresholded = type == STOCKC? thresholdImage(imgHSV, stockBlueLowHue, stockBlueHighHue, stockBlueLowSat, stockBlueHighSat, stockBlueLowVal, stockBlueHighVal) :
		thresholdImage(imgHSV, productBlueLowHue, productBlueHighHue, productBlueLowSat, productBlueHighSat, productBlueLowVal, productBlueHighVal);
	point = getPointofObject(imgThresholded);
	if (isDetectedTablet(tablet, point, BLUE))
		return;
}

bool Tool::isDetectedTablet(Tablet* tablet, cv::Point mask, Colour colour){
	int x, y, d;

	offset(tablet->center, mask, &x, &y, &d);
	if (length(d, STOCKC) > 4 ||
		length(d, STOCKC) < -4) // Allowed distance from masked point
		return false;

	tablet->colour = colour;
	return true;
}

float Tool::length(float pixels, CameraType type){
	float length;

	if (type == TRAYC)
		length = pixels / measureTrayLength; // cm
	else if (type == STOCKC)
		length = pixels / measureStockLength; // cm
	else
		length = pixels / measureProductLength; // cm

	return std::floor(length * 100) / 10; // mm
}

std::string Tool::tabletToString(Tablet tablet, CameraType type){
	int x, y, d;
	char toString[100];

	offset(tablet.center, stockPoint, &x, &y, &d);	
	tablet.valid ?
		sprintf_s(toString, 100, "%s R%.1f C(%d, %d) O(%.1f, %.1f) D%.1f", 
		tablet.colourToString().c_str(), length(tablet.radius, type), 
		tablet.center.x, tablet.center.y, tablet.getX(length(x, type)), 
		tablet.getY(length(y, type)), length(tablet.radius, type)) :
		sprintf_s(toString, 100, "Invalid R%.1f", length(tablet.radius, type));

	return (std::string)toString;
}

void Tool::offset(cv::Point src, cv::Point ref, int* x, int* y, int* d){
	*x = src.x - ref.x;
	*y = src.y - ref.y;
	*d = std::sqrt(std::pow(*x, 2) + std::pow(*y, 2));
}

bool Tool::tabletsChange(cv::vector<Tablet> a, cv::vector<Tablet> b){
	if (a.size() != b.size())
		return true;

	for (int i = 0; i < a.size(); i++)
		if (a[i].center.x != b[i].center.x ||
			a[i].center.y != b[i].center.y)
			return true;

	return false;
}

std::string Tool::isValidProduct(cv::RotatedRect tray, cv::vector<Tablet> tablets){	
	int blue = 0, green = 0, red = 0, white = 0, black = 0, noColour = 0;

	for (int i = 0; i < tablets.size(); i++)
		switch (tablets[i].colour){
		case BLUE:
			blue++;
			break;
		case GREEN:
			green++;
			break;
		case RED:
			red++;
			break;
		case WHITE:
			white++;
			break;
		case BLACK:
			black++;
			break;
		default:
			noColour++;
	}

	std::string string = 
		"Nb Tablets:" + std::to_string(tablets.size()) + 
		" Blue:" + std::to_string(blue) + 
		" Green:" + std::to_string(green) + 
		" Red:" + std::to_string(red) + 
		" White:" + std::to_string(white) + 
		" Black:" + std::to_string(black) + 
		"noColour:" + std::to_string(noColour);
	return "";
}

void Tool::newData(){
	displayOriginal = true;

	oriLowHue = 55;
	oriHighHue = 64;
	oriLowSat = 65;
	oriHighSat = 255;
	oriLowVal = 0;
	oriHighVal = 255;
	oriRect = cv::Rect(728, 166, 110, 130);

	strcpy_s(trayAddress, "192.168.1.112");
	strcpy_s(stockAddress, "192.168.1.112");

	trayLowHue = 10;
	trayHighHue = 31;
	trayLowSat = 80;
	trayHighSat = 230;
	trayLowVal = 115;
	trayHighVal = 227;
	trayPoint = cv::Point(615, 28);

	measurePoint = cv::Point(486, 28);
	measureTrayLength = 27;
	measureStockLength = 25;

	stockCanny = 74;
	stockAccumulator = 40;

	stockBlueLowHue = 110;
	stockBlueHighHue = 115;
	stockBlueLowSat = 69;
	stockBlueHighSat = 228;
	stockBlueLowVal = 67;
	stockBlueHighVal = 255;

	stockGreenLowHue = 100;
	stockGreenHighHue = 108;
	stockGreenLowSat = 55;
	stockGreenHighSat = 232;
	stockGreenLowVal = 50;
	stockGreenHighVal = 241;

	stockRedLowHue = 129;
	stockRedHighHue = 177;
	stockRedLowSat = 37;
	stockRedHighSat = 239;
	stockRedLowVal = 23;
	stockRedHighVal = 255;

	stockBlackLowHue = 105;
	stockBlackHighHue = 121;
	stockBlackLowSat = 88;
	stockBlackHighSat = 98;
	stockBlackLowVal = 0;
	stockBlackHighVal = 98;

	stockWhiteLowHue = 109;
	stockWhiteHighHue = 119;
	stockWhiteLowSat = 48;
	stockWhiteHighSat = 195;
	stockWhiteLowVal = 112;
	stockWhiteHighVal = 237;

	stockPoint = cv::Point(350, 734);

	trayCanny = 44;
	trayAccumulator = 23;

	stockLowHue = 0;
	stockHighHue = 179;
	stockLowSat = 0;
	stockHighSat = 255;
	stockLowVal = 0;
	stockHighVal = 255;
}

void callBackFunc(int event, int x, int y, int flags, void* userdata)
{
	Tool* tool = (Tool*)userdata;
	if  (event == cv::EVENT_LBUTTONDOWN)
	{		
		std::cout << "> Point (" << x << "," << y << ")";		
		tool->leftClickEvent(x, y, flags);
		std::cout << "\n";
	}
	else if  (event == cv::EVENT_RBUTTONDOWN)
	{
		tool->changeDisplay();
		std::cout << "> Display Changed\n";
	}
	else if  (event == cv::EVENT_MBUTTONDOWN)
	{

	}
	else if (event == cv::EVENT_MOUSEMOVE)
	{

	}
}

// Tablet Class : Public
Tablet::Tablet(){
	valid = false;
}

Tablet::Tablet(cv::Vec3f circle, cv::Point point, int measure){
	center.x = cvRound(circle[0]);
	center.y = cvRound(circle[1]);
	radius = cvRound(circle[2]);
	colour = NOCOLOUR;
	valid = true;

	int x, y, d;
	offset(center, point, &x, &y, &d);

	offsetX = getX(length(x, measure));
	offsetY = getY(length(y, measure));
}

std::string Tablet::colourToString(){
	switch (colour){
	case BLUE:
		return"Blue";
	case GREEN:
		return "Green";
	case RED:
		return "Red";
	case BLACK:
		return "Black";
	case WHITE:
		return "White";
	}
	return "";
}

float Tablet::getX(float nb){
	return (0.0468 * nb - 0.134) + nb;
}

float Tablet::getY(float nb){
	return (0.0716 * nb - 0.2519) + nb;
}

void Tablet::offset(cv::Point src, cv::Point ref, int* x, int* y, int* d){
	*x = src.x - ref.x;
	*y = src.y - ref.y;
	*d = std::sqrt(std::pow(*x, 2) + std::pow(*y, 2));
}

float Tablet::length(float pixels, int measure){
	float length;

	length = pixels / measure; // cm

	return std::floor(length * 100) / 10; // mm
}

std::string Tablet::toString(){
	char toString[30];
	sprintf_s(toString, 30, "%s,%.0f,%.0f,%s",
		valid?"valid":"invalid",
		offsetX, offsetY,
		colourToString().c_str());	
	

	return toString;
}

// Tray Class : Public
Tray::Tray(){
	width = 0;
	height = 0;
	angle = 0;
	offsetX = 0;
	offsetY = 0;
	valid = false;
}

Tray::Tray(cv::RotatedRect tray, cv::Point point, CameraType type, Tool tool){
	int x, y, d;
	tool.offset(tray.center, point, &x, &y, &d);

	width = tool.length(tray.size.width, type);
	height = tool.length(tray.size.height, type);
	angle = tray.angle;;
	offsetX = tool.length(x, type);
	offsetY = tool.length(y, type);
	boundingRect = tray.boundingRect();

	valid = true;	
}

std::string Tray::toString(){
	char toString[20];
	sprintf_s(toString, 20, "%s,%.0f,%.0f,%.0f",
		valid?"valid":"invalid", offsetX, offsetY, angle);
	return toString;
}