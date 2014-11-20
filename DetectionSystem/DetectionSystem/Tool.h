// Tool.h : Defines the entry point for the console application.
//

#ifndef Tool_H
#define Tool_H

#define TRAYWIDTH 225//mm
#define TRAYWIDTHRANGE 10//mm
#define TRAYHEIGHT 225//mm
#define TRAYHEIGHTRANGE 10//mm
#define TABLETRADIUS 18.5//mm
#define TABLETRADUISRANGE 2//mm

enum Active{
	ORI,
	TRAY,
	PRODUCT,
	STOCK,
	STOCKCOLOUR,
	STOCKAREA,
	MEASURE,
	PRODUCTTRAY,
	PRODUCTCOLOUR
};

enum CameraType{
	TRAYC,
	STOCKC,
	PRODUCTC
};

enum Colour{
	BLUE,
	GREEN,
	RED,
	BLACK,
	WHITE,
	NOCOLOUR
};

class Tablet{
public:
	cv::Point center;
	float radius,
		offsetX,
		offsetY;
	Colour colour;
	bool valid;

	Tablet();
	Tablet(cv::Vec3f circle, cv::Point point, int measure);
	std::string colourToString();
	float getX(float nb);
	float getY(float nb);
	void offset(cv::Point src, cv::Point ref, int* x, int* y, int* d);
	float length(float pixels, int measure);
	std::string toString();
};

void callBackFunc(int event, int x, int y, int flags, void* userdata);

class Tool {	
	Active active;
	bool displayOriginal;	

	void buildGUI(int* canny, int* accumulator);
	void buildGUI(
		int* lowHue, int* highHue,
		int* lowSat, int* highSat,
		int* lowVal, int* highVal);
	void buildGUI();
	bool keyPress(int key, int* measureLength = nullptr);
	cv::Point getPointofObject(cv::Mat image);
	cv::Mat thresholdImage(
		cv::Mat image,
		int lowHue, int highHue,
		int lowSat, int highSat,
		int lowVal, int highVal);
	void updateDisplay(cv::Mat original, cv::Mat thresholded);
	void displayStats();		
	cv::RotatedRect detectTray(cv::vector<cv::RotatedRect> rotatedRects, CameraType type);
	cv::vector<Tablet> detectCircles(cv::Mat image, cv::Mat imgLines, cv::Rect validArea, CameraType type);	
	void detectTablet(Tablet* tablet, cv::Mat image, CameraType type);
	bool isDetectedTablet(Tablet* tablet, cv::Point point, Colour colour);	
	std::string tabletToString(Tablet tablet, CameraType type);	
	bool tabletsChange(cv::vector<Tablet> a, cv::vector<Tablet> b);
	std::string isValidProduct(cv::RotatedRect tray, cv::vector<Tablet> tablets);
	void newData();

public:
	int oriLowHue, oriHighHue,
		oriLowSat, oriHighSat,
		oriLowVal, oriHighVal;
	cv::Rect oriRect;

	char trayAddress[16],
		stockAddress[16];

	int trayLowHue, trayHighHue,
		trayLowSat, trayHighSat,
		trayLowVal, trayHighVal;
	cv::Point trayPoint;	

	cv::Point measurePoint;
	int measureTrayLength, // pixels/cm
		measureStockLength; // pixels/cm	

	int stockCanny,
		stockAccumulator;

	int stockBlueLowHue, stockBlueHighHue,
		stockBlueLowSat, stockBlueHighSat,
		stockBlueLowVal, stockBlueHighVal,
		stockGreenLowHue, stockGreenHighHue,
		stockGreenLowSat, stockGreenHighSat,
		stockGreenLowVal, stockGreenHighVal,
		stockRedLowHue, stockRedHighHue,
		stockRedLowSat, stockRedHighSat,
		stockRedLowVal, stockRedHighVal,
		stockBlackLowHue, stockBlackHighHue,
		stockBlackLowSat, stockBlackHighSat,
		stockBlackLowVal, stockBlackHighVal,
		stockWhiteLowHue, stockWhiteHighHue,
		stockWhiteLowSat, stockWhiteHighSat,
		stockWhiteLowVal, stockWhiteHighVal;
	cv::Point stockPoint;

	int trayCanny,
		trayAccumulator;
	
	// Not Used
	int stockLowHue, stockHighHue,
		stockLowSat, stockHighSat,
		stockLowVal, stockHighVal;

	cv::Rect stockValidArea;

	char productAddress[16];
	int measureProductLength; // pixels/cm
	int productLowHue, productHighHue,
		productLowSat, productHighSat,
		productLowVal, productHighVal;
	cv::Point productPoint;	

	int productBlueLowHue, productBlueHighHue,
		productBlueLowSat, productBlueHighSat,
		productBlueLowVal, productBlueHighVal,
		productGreenLowHue, productGreenHighHue,
		productGreenLowSat, productGreenHighSat,
		productGreenLowVal, productGreenHighVal,
		productRedLowHue, productRedHighHue,
		productRedLowSat, productRedHighSat,
		productRedLowVal, productRedHighVal,
		productBlackLowHue, productBlackHighHue,
		productBlackLowSat, productBlackHighSat,
		productBlackLowVal, productBlackHighVal,
		productWhiteLowHue, productWhiteHighHue,
		productWhiteLowSat, productWhiteHighSat,
		productWhiteLowVal, productWhiteHighVal;

	Tool();
	Tool(std::string profile);
	cv::Mat initImage(cv::Mat image, int type);
	void offset(cv::Point src, cv::Point ref, int* x, int* y, int* d);
	float length(float pixels, CameraType type);	
	bool validTray(cv::RotatedRect tray, CameraType type);
	cv::vector<Tablet> Tool::detectCircles(cv::Mat image, cv::Rect validArea, CameraType type);
	void detectTablets(cv::vector<Tablet>* tablets, cv::Mat image, CameraType type);

	void calibrateOri(cv::Mat image);
	void calibrateTray(cv::Mat image);
	void calibrateProductTray(cv::Mat image);
	void calibrateProduct(cv::Mat image);
	void calibrateProductBlue(cv::Mat image);
	void calibrateProductGreen(cv::Mat image);
	void calibrateProductRed(cv::Mat image);
	void calibrateProductBlack(cv::Mat image);
	void calibrateProductWhite(cv::Mat image);
	void calibrateStockArea(cv::Mat image);
	void calibrateStock(cv::Mat image);
	void calibrateStockBlue(cv::Mat image);
	void calibrateStockGreen(cv::Mat image);
	void calibrateStockRed(cv::Mat image);
	void calibrateStockBlack(cv::Mat image);
	void calibrateStockWhite(cv::Mat image);
	void calibrateMeasurement(cv::Mat image, CameraType type);
	void changeDisplay();
	void writeFile(std::string profile);
	void readFile(std::string profile);	
	void leftClickEvent(int x, int y, int flags);
	void changeAddress(CameraType type, std::string address);
};

class Tray {
public:
	float width,
		height,
		angle,
		offsetX,
		offsetY;
	cv::Rect boundingRect;
	bool valid;

	Tray();
	Tray(cv::RotatedRect tray, cv::Point point, CameraType type, Tool tool);	
	std::string toString();
};

#endif