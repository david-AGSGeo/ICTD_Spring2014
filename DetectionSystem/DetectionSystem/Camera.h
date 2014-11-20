// Camera.h : Defines the entry point for the console application.
//

#ifndef Camera_H
#define Camera_H

class Camera {
	std::string name,
				address;
	cv::Mat image;

	cv::Mat stringtoMat(std::string file);
	cv::Mat loadFromURL(std::string url);

public: 	
	Camera();
	Camera(std::string name, std::string address);
	cv::Mat getImage();
	void displayImage();
	void dectectColourHSV();
	std::string changeAddress();
};

#endif