// Camera.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Camera.h"

static bool factoryLoaded = false;

// Class Camera : Public
Camera::Camera(){}

Camera::Camera(std::string name, std::string address){
	this->name = name;
	this->address = address;
	std::cout << ">> " << name << ": " << address << "\n";
}

cv::Mat Camera::getImage(){
	/*if (strcmp(name.c_str(), "Tray Camera") == 0)
		image = cv::imread("images/tray1.jpg", CV_LOAD_IMAGE_UNCHANGED);
	else
		image = cv::imread("images/AllTabs - Box - No Ruler.jpg", CV_LOAD_IMAGE_UNCHANGED);*/
	image = stringtoMat("http://" + address + ":8080/photoaf.jpg");
	return image;
}

void Camera::displayImage(){
	cv::namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	cv::imshow("MyWindow", image);
	cv::waitKey(0);
	cv::destroyWindow("MyWindow");
}

std::string Camera::changeAddress(){
	std::cout << "> " << name << " Adress: ";
	std::cin >> address;
	std::cout << "> " + name + ": " << address << "\n";
	return address;
}

// Class Camera : Private
cv::Mat Camera::stringtoMat(std::string url)
{
	cv::Mat newImage;

	newImage = loadFromURL(url);
	if(!newImage.data)
		std::cout << "> " + name + " has invalid address: " + address + "\n";

	return newImage;
}

cv::Mat Camera::loadFromURL(std::string url)
{
	//Don't register the factory more than once
	if(!factoryLoaded){
		Poco::Net::HTTPStreamFactory::registerFactory();
		factoryLoaded = true;
	}

	//Specify URL and open input stream
	Poco::URI uri(url);
	std::auto_ptr<std::istream> pStr;
	//Poco::TimeoutException
	try {
		pStr = std::auto_ptr<std::istream>(Poco::URIStreamOpener::defaultOpener().open(uri));
	} catch (Poco::TimeoutException e) {
		return cv::Mat::zeros(cv::Size(0,0), CV_8UC3);
	}

	//Copy image to our string and convert to cv::Mat
	std::string str;
	Poco::StreamCopier::copyToString(*pStr.get(), str);
	std::vector<char> data( str.begin(), str.end() );
	cv::Mat data_mat(data);
	cv::Mat newImage(cv::imdecode(data_mat,1));
	return newImage;
}

void Camera::dectectColourHSV(){
	cv::Mat imgLines = cv::Mat::zeros(image.size(), CV_8UC3 );;
	cv::Mat imgHSV;
	cv::Mat imgThresholded;
	cv::Moments oMoments;

	int iLowH = 55;		// Max 179 - 55
	int iHighH = 64;	// Max 179 - 64

	int iLowS = 65;		// Max 255 - 65
	int iHighS = 255;	// Max 255 - 255

	int iLowV = 0;		// Max 255 - 0
	int iHighV = 255;	// Max 255 - 255

	//Convert the captured frame from BGR to HSV
	cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV); 

	//Threshold the image
	inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded); 

	//morphological opening (remove small objects from the foreground)
	cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5))); 

	//morphological closing (fill small holes in the foreground)
	cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5))); 
	cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	//Calculate the moments of the thresholded image
	oMoments = cv::moments(imgThresholded);

	double dM01 = oMoments.m01;
	double dM10 = oMoments.m10;
	double dArea = oMoments.m00;

	// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
	if (dArea > 10000)
	{
		//calculate the position of the ball
		int posX = dM10 / dArea;
		int posY = dM01 / dArea;   
		cv::line(imgLines, cv::Point(posX, posY), cv::Point(0, 0), cv::Scalar(0,0,255), 2);
	}	

	if (!imgLines.empty())
		image += imgLines;

	cv::imshow("Thresholded Image - HSV", imgThresholded); //show the thresholded image
	cv::imshow("Original", image); //show the original image			
}