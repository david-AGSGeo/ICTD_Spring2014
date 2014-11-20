// DetectionSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DetectionSystem.h"
#include "Pipe.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DetectionSystem system;	
	if (argc <= 1)
		system.calibrate();
	else
		system.run();
	return 0;
}

// Class DetectionSystem : Public
DetectionSystem::DetectionSystem(){
	std::cout << "\n==== Detection System ====\n";
	trayCamera = Camera("Tray Camera", (std::string)tool.trayAddress);
	stockCamera = Camera("Stock Camera", (std::string)tool.stockAddress);
	productCamera = Camera("Product Camera", (std::string)tool.productAddress);
}

void DetectionSystem::run(){
	bool end = false;
	std::cout << "\n== Detection System Main==\n";
	if (!pipe.initPipe()){
		pipe.endPipe();
		return;
	}

	while (!end){
		std::vector<std::string> commands = pipe.listenForCommand();
		std::string message = "";
		if (commands.size() == 0)
			return;
		else if (compareString(commands[0], "checkSystem")){
			message = checkSystem();
			pipe.returnMessage(message, "checkSystem");
		} else if (compareString(commands[0], "checkTray")){
			message = checkTray();
			pipe.returnMessage(message, "checkTray");
		} else if (compareString(commands[0], "checkTablet")){
			message = checkTablet(commands);
			pipe.returnMessage(message, "checkTablet");
		} else if (compareString(commands[0], "checkProduct")){
			message = checkProduct(commands);
			pipe.returnMessage(message, "checkProduct");
		} else if (compareString(commands[0], "checkPTray")){
			message = checkProductTray();
			pipe.returnMessage(message, "checkProductTray");
		} else if (compareString(commands[0], "shutdown"))
			end = true;
		else{
			std::cout << "Invalid Command Size:" << std::to_string(commands.size());
			commands.size() > 0? std::cout << " Message:" << commands[0] << "\n" : std::cout << "\n";
		}
	}

	pipe.endPipe();
	std::cout << "Detection System Shutdown\n";
}

std::string DetectionSystem::checkSystem(){	
	std::cout << "Checking tray camera\n";
	cv::Mat image = trayCamera.getImage();
	if (image.data){
		std::cout << "Checking stock camera\n";
		image = stockCamera.getImage();
		if (image.data){
			std::cout << "Checking product camera\n";
			image = productCamera.getImage();
			if (image.data)
				return "ready"; // Working
		}
	}
	return "invalidIp"; // Not Working
}

std::string DetectionSystem::checkTray(){
	std::cout << "Getting image\n";
	cv::Mat image = trayCamera.getImage();
	if (!image.data) {
		std::cout << "Image failed";
		return "noTray,0,0,0";
	}

	// Get Tray
	std::cout << "Getting tray\n";
	Tray tray = checkTray(image);  // Detected Tray
	std::cout << "Recieved tray\n";
	return tray.toString();
}

std::string DetectionSystem::checkTablet(std::vector<std::string> parameters){
	std::cout << "Getting image\n";
	cv::Mat image = stockCamera.getImage();
	if (!image.data){
		std::cout << "Image failed\n";
		return "noTablet";
	}
	cv::Mat imgGray = tool.initImage(image, cv::COLOR_BGR2GRAY);

	std::cout << "Getting tablets\n";
	// Get Tablets
	cv::vector<Tablet> tablets = tool.detectCircles(imgGray, tool.stockValidArea, STOCKC);
	tool.detectTablets(&tablets, image, STOCKC);
	std::cout << "Recieved tablets\n";

	// Return Tablet
	if (tablets.size() == 0)
		return "noTablet";
	
	if (parameters.size() == 1){
		std::cout << "Returning first tablet\n";
		return tablets[0].toString(); // Return first tablet
	}

	if (compareString(parameters[1], "priority") &&
		hasTablets(tablets, -1, getColour(parameters[2]))){
			std::cout << "Check for priority\n";
			Tablet tablet = findTablet(tablets, getColour(parameters[2])); // Return pirority tablet
			if (tablet.valid){
				std::cout << "Returning Priority tablet\n";
				return tablet.toString();				
			}
	}

	if (compareString(parameters[1], "reject") ||
		parameters.size() > 3 && compareString(parameters[3], "reject")){
			Tablet tablet = findTablet(tablets, parameters); // Return first non rejected tablet
			if (tablet.valid){
				std::cout << "Returning first non-reject tablet\n";
				return tablet.toString();
			}else{
				std::cout << "Only reject tablets\n";
				return "noTablet";
			}
	}

	std::cout << "Post Parameter\n";
	return tablets[0].toString();
}

std::string DetectionSystem::checkProduct(std::vector<std::string> parameters){
	std::cout << "Getting image\n";
	cv::Mat image = trayCamera.getImage();
	if (!image.data){
		std::cout << "Image failed\n";
		return "noProduct";
	}
	cv::Mat imgGray = tool.initImage(image, cv::COLOR_BGR2GRAY);

	std::cout << "Getting tray\n";
	// Get Tray
	Tray tray = checkTray(image);
	std::cout << "Recieved tray\n";

	std::cout << "Getting tablets\n";
	// Get Tabelts
	cv::vector<Tablet> tablets = tool.detectCircles(imgGray, tray.boundingRect, TRAYC);
	tool.detectTablets(&tablets, image, TRAYC);
	std::cout << "Recieved tablets\n";

	std::cout << "Comparing order\n";
	// Compare tablets to Order
	if (compareProductToOrder(tablets, parameters)){
		std::cout << "Order valid\n";
		return "valid";
	}
	std::cout << "Order invalid\n";
	return "invalid";
}

std::string DetectionSystem::checkProductTray(){
	std::cout << "Getting image\n";
	cv::Mat image = productCamera.getImage();
	if (!image.data){
		std::cout << "Image failed\n";
		return "noProductTray,0,0,0";
	}
	std::cout << "Getting tray\n";
	// Get Tray
	Tray tray = checkProductTray(image);  // Detected Tray
	std::cout << "Tray recieved\n";
	return tray.toString();
}

Tablet DetectionSystem::findTablet(cv::vector<Tablet> tablets, Colour colour){
	for (int i = 0; i < tablets.size(); i++)
		if (tablets[i].colour == colour)
			return tablets[i];
	return Tablet();
}

Tablet DetectionSystem::findTablet(cv::vector<Tablet> tablets, std::vector<std::string> parameters){
	std::vector<Colour> colours;
	for (int i = 0; i < parameters.size(); i++)
		colours.push_back(getColour(parameters[i]));

	for (int i = 0; i < tablets.size(); i++)
		if (std::find(colours.begin(), colours.end(), tablets[i].colour) == colours.end())
			return tablets[i];
	return Tablet();
}

bool DetectionSystem::compareProductToOrder(cv::vector<Tablet> product, std::vector<std::string> order){	
	int total = 0;
	for (int i = 1; i < order.size(); i+=2){
		int number = std::stoi(order[i]);
		total += number;
		Colour colour = getColour(order[i+1]);
		if (!hasTablets(product, number, colour))
			return false;
	}

	return total == product.size();
}

Colour DetectionSystem::getColour(std::string colour){
	if (compareString(colour, "Blue"))
		return BLUE;
	if (compareString(colour, "Green"))
		return GREEN;
	if (compareString(colour, "Red"))
		return RED;
	if (compareString(colour, "Black"))
		return BLACK;
	if (compareString(colour, "White"))
		return WHITE;
	return NOCOLOUR;
}

bool DetectionSystem::hasTablets(cv::vector<Tablet> tablets, int number, Colour colour){
	int nbTablets = 0;
	for (int i = 0; i < tablets.size(); i++)
		if (tablets[i].colour == colour)
			nbTablets++;
	return number == -1? nbTablets > 0 : nbTablets == number;
}

bool DetectionSystem::compareString(std::string str1, std::string str2){
	int length = str1.length() <= str2.length()? str1.length() : str2.length();
	for (int i = 0; i < length; i++)
		if (str1[i] != str2[i])
			return false;
	return true;
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

	return detectTray(detectImage, TRAYC);
}

Tray DetectionSystem::checkProductTray(cv::Mat image){
	cv::Mat detectImage = detectColourHSV(image, 
		tool.productLowHue, tool.productHighHue, 
		tool.productLowSat, tool.productHighSat, 
		tool.productLowVal, tool.productHighVal);

	return detectTray(detectImage, PRODUCTC);
}

Tray DetectionSystem::detectTray(cv::Mat image, CameraType type){
	cv::vector<cv::vector<cv::Point>> contours;

	// Detect Tray
	cv::findContours(image, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	cv::vector<cv::RotatedRect> rotatedRects(contours.size());

	for(int i = 0; i < contours.size(); i++){
		cv::approxPolyDP(cv::Mat(contours[i]), contours[i], 3, true);
		rotatedRects[i] = cv::minAreaRect(cv::Mat(contours[i]));
	}

	bool error = false;
	cv::RotatedRect tray = findTray(rotatedRects, type, &error);

	if (error)
		return Tray();

	cv::Point point = type == TRAYC? tool.trayPoint : tool.productPoint;
	return Tray(tray, point, type, tool);
}

cv::RotatedRect DetectionSystem::findTray(cv::vector<cv::RotatedRect> rotatedRects, CameraType type, bool* error){
	for (int i = 0; i < rotatedRects.size(); i++)
		if (tool.validTray(rotatedRects[i], type))
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
	std::cout << "q:Exit | w:Save | e:Load | r:Help\n";
	std::cout << "a:Orientation | s:Tray | d:Product | f:Stock | g:ProductColours | h:ProductTray\n";
	std::cout << "Address> z:Tray | x:Stock | c:Product\n";
	std::cout << "Measure> v:Tray | b:Stock | n:Product\n";
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
	case 'q':
		std::cout << "> Exit calibration mode\n";
		return true;
	case 'w':
		tool.writeFile("default");
		break;
	case 'e':
		tool.readFile("default");
		break;
	case 'a':
		image = trayCamera.getImage();
		if (image.data)
			tool.calibrateOri(image);
		break;
	case 's':
		image = trayCamera.getImage();
		if (image.data)
			tool.calibrateTray(image);
		break;
	case 'd':
		image = trayCamera.getImage();
		if (image.data)
			tool.calibrateProduct(image);
		break;
	case 'g':
		calibrateProduct();
		break;
	case 'h':
		image = productCamera.getImage();
		if (image.data)
			tool.calibrateProductTray(image);
		break;
	case 'f':
		calibrateStock();
		break;
	case 'v':
		image = trayCamera.getImage();
		if (image.data)
			tool.calibrateMeasurement(image, TRAYC);
		break;
	case 'b':
		image = stockCamera.getImage();
		if (image.data)
			tool.calibrateMeasurement(image, STOCKC);
		break;
	case 'n':
		image = productCamera.getImage();
		if (image.data)
			tool.calibrateMeasurement(image, PRODUCTC);
		break;
	case 'z':		
		tool.changeAddress(TRAYC, trayCamera.changeAddress());
		break;
	case 'x':
		tool.changeAddress(STOCKC, stockCamera.changeAddress());
		break;
	case 'c':
		tool.changeAddress(PRODUCTC, productCamera.changeAddress());
		break;
	case 'r':
		std::cout << "q:Exit | w:Save | e:Load | r:Help\n";
		std::cout << "a:Orientation | s:Tray | d:Product | f:Stock | g:ProductColours | h:ProductTray\n";
		std::cout << "Address> z:Tray | x:Stock | c:Product\n";
		std::cout << "Measure> v:Tray | b:Stock | n:Product\n";
		break;
	}
	return false;
}

void DetectionSystem::calibrateStock(){
	std::string input = "";
	cv::Mat image;
	std::cout << "\n== Stock calibration mode ==\n";
	std::cout << "q:Exit | w:Save | e:Load | r:Help\n";
	std::cout << "a:Tablets | s:Area\n";
	std::cout << "z:Blue | x:Green | c:Red | v:Black | b:White\n";

	while (input[0] != 'q'){
		std::cout << ">> Input: ";
		std::cin >> input;
		switch (input[0]){
		case 'w':
			tool.writeFile("default");
			break;		
		case 'e':
			tool.readFile("default");
			break;
		case 'a':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStock(image);
			break;
		case 's':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockArea(image);
			break;
		case 'z':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockBlue(image);
			break;
		case 'x':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockGreen(image);
			break;
		case 'c':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockRed(image);
			break;
		case 'v':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockBlack(image);
			break;
		case 'b':
			image = stockCamera.getImage();
			if (image.data)
				tool.calibrateStockWhite(image);
			break;
		case 'r':
			std::cout << "q:Exit | w:Save | e:Load | r:Help\n";
			std::cout << "a:Tablets | s:Area\n";
			std::cout << "z:Blue | x:Green | c:Red | v:Black | b:White\n";
			break;
		}
	}
	std::cout << "> Exit Stock calibration mode\n";
}

void DetectionSystem::calibrateProduct(){
	std::string input = "";
	cv::Mat image;
	std::cout << "\n== Product calibration mode ==\n";
	std::cout << "q:Exit | w:Save | e:Load | r:Help\n";
	std::cout << "z:Blue | x:Green | c:Red | v:Black | b:White\n";

	while (input[0] != 'q'){
		std::cout << ">> Input: ";
		std::cin >> input;
		switch (input[0]){
		case 'w':
			tool.writeFile("default");
			break;		
		case 'e':
			tool.readFile("default");
			break;
		case 'z':
			image = trayCamera.getImage();
			if (image.data)
				tool.calibrateProductBlue(image);
			break;
		case 'x':
			image = trayCamera.getImage();
			if (image.data)
				tool.calibrateProductGreen(image);
			break;
		case 'c':
			image = trayCamera.getImage();
			if (image.data)
				tool.calibrateProductRed(image);
			break;
		case 'v':
			image = trayCamera.getImage();
			if (image.data)
				tool.calibrateProductBlack(image);
			break;
		case 'b':
			image = trayCamera.getImage();
			if (image.data)
				tool.calibrateProductWhite(image);
			break;
		case 'r':
			std::cout << "q:Exit | w:Save | e:Load | r:Help\n";
			std::cout << "z:Blue | x:Green | c:Red | v:Black | b:White\n";
			break;
		}
	}
	std::cout << "> Exit Product calibration mode\n";
}