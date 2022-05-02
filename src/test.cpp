#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

#include "iostream"

void loadImage(std::string path) 
{
    cv::Mat img = cv::imread(path);
    imshow("Image", img);
    cv::waitKey(0); 
}

void loadVideo(std::string path){

    cv::VideoCapture cap(path);
    cv::Mat img;

    while (true){
        cap.read(img);
        imshow("Video", img);
        cv::waitKey(25); 

    }
}

void convertToGray(std::string path) 
{
    cv::Mat img = cv::imread(path);
    cv::Mat imgGray;
    cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    imshow("Gray Image", imgGray);
    cv::waitKey(0); 
}

void blurImage(std::string path) 
{
    cv::Mat img = cv::imread(path);
    cv::Mat imgBlur;
    /*
    void cv::GaussianBlur ( 	
        InputArray  	src,
		OutputArray  	dst,
		Size  	ksize,
		double  	sigmaX,
		double  	sigmaY = 0,
		int  	borderType = BORDER_DEFAULT 
	) 

    ksize ==> Gaussian kernel size. ksize.width and ksize.height can differ but they both must be positive and odd. 
    Or, they can be zero's and then they are computed from sigma.

    sigmaX ==> Gaussian kernel standard deviation in X direction.

    sigmaY ==> Gaussian kernel standard deviation in Y direction;

    If sigmaY is zero, it is set to be equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height; 
    To fully control the result regardless of possible future modifications of all this semantics, it is recommended to specify all of ksize, sigmaX, and sigmaY.

    borderType	pixel extrapolation method.	
    */
    cv::GaussianBlur(img, imgBlur, cv::Size(7,7), 5, 0);
    imshow("Blur Image", imgBlur);
    cv::waitKey(0); 
}

void cannyEdgeDetector(std::string path) 
{
    cv::Mat img = cv::imread(path);
    cv::Mat imgBlur, imgCanny;
    cv::GaussianBlur(img, imgBlur, cv::Size(3,3), 5, 0);
    /*
    void cv::Canny( 
        detected_edges, 
        detected_edges, 
        lowThreshold, 
        high threshold    
    )
    detected_edges ==> Source image, grayscale
    detected_edges ==> Output of the detector (can be the same as the input)
    lowThreshold ==> The value entered by the user moving the Trackbar
    highThreshold ==> Set in the program as three times the lower threshold
    */
    Canny(imgBlur, imgCanny, 25, 75);
    imshow("Canny Image", imgCanny);
    cv::waitKey(0); 
}

int main(int, char**) 
{
   // loadImage("assets/goat.jpg");
   // loadVideo("assets/goat.avi");
   // convertToGray("assets/goat.jpg");
   // blurImage("assets/goat.jpg");
   // cannyEdgeDetector("assets/goat.jpg");
   return 0;
}