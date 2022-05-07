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

void loadVideo(std::string path)
{
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

void dilateOrErodeImage(std::string path, bool dilateImg)
{
    cv::Mat imgBlur, imgCanny, imgOutput;

    cv::Mat img = cv::imread(path);

    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(1,1));

    cv::GaussianBlur(img, imgBlur, cv::Size(3,3), 5, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    if (dilateImg)
    {
        dilate(imgCanny, imgOutput, kernel);
    }
    else
    {
        erode(imgCanny, imgOutput, kernel);
    }
    
    imshow("Output Image", imgOutput);
    cv::waitKey(0); 
}

void reSizeImage(std::string path, float scaleX, float scaleY) 
{
    cv::Mat img = cv::imread(path);
    cv::Mat imgResize;
    
    resize(img, imgResize, cv::Size(), scaleX, scaleY);

    imshow("Original Image", img);
    imshow("Resize Image", imgResize);
    cv::waitKey(0); 
}

void cropImage(std::string path, int _x, int _y, int _width, int _height) 
{
    cv::Mat img = cv::imread(path);
    cv::Mat imgCrop;
    
    cv::Rect roi(_x, _y, _width, _height);
    imgCrop = img(roi);

    imshow("Original Image", img);
    imshow("Crop Image", imgCrop);
    cv::waitKey(0); 
}

void getContours(cv::Mat imgDilate, cv::Mat img2Draw)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    
    findContours(imgDilate, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRectangle(contours.size());
    std::string objType;
    int objectCorner;
    float aspectRatio;
    
    for(int i = 0; i < contours.size(); i++)
    {
        int shape_area = cv::contourArea(contours[i]);

        // std::cout << shape_area << std::endl;
        // Filter noise
        if (shape_area > 1000)
        {
            float perimeter = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], perimeter * 0.02, true);
            drawContours(img2Draw, conPoly, i, cv::Scalar(200, 200), 2);
            std::cout << conPoly[i].size() << std::endl;
            boundRectangle[i] = cv::boundingRect(conPoly[i]);
            
            objectCorner = (int) conPoly[i].size();
            if(objectCorner == 4){
                aspectRatio = (float) boundRectangle[i].width / (float) boundRectangle[i].height;
                if(aspectRatio < 1.05 && aspectRatio > 0.95)
                {
                    objType = "Square";
                }
                else 
                {
                    objType = "Rectangle";
                }    
                rectangle(img2Draw, boundRectangle[i].tl(), boundRectangle[i].br(), cv::Scalar(0, 255, 0), 3);
                putText(img2Draw, objType, {boundRectangle[i].x, boundRectangle[i].y}, cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0, 69, 255), 2);

            }
            
        }
    }
}

int main(int, char**) 
{
    // loadImage("assets/goat.jpg");
    // loadVideo("assets/goat.avi");
    // convertToGray("assets/goat.jpg");
    // blurImage("assets/goat.jpg");
    // cannyEdgeDetector("assets/goat.jpg");
    // dilateOrErodeImage("assets/goat.jpg", false);
    // reSizeImage("assets/goat.jpg", 0.5, 0.7);
    // cropImage("assets/goat.jpg", 1, 1, 50, 50); 

    // Shape
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(250, 100, 250));
    circle (img, cv::Point (256, 256), 155, cv::Scalar(0, 69, 255), cv::FILLED);
    rectangle(img, cv::Point(130, 226), cv::Point(382, 286), cv::Scalar(255, 255, 255), cv::FILLED);
    line(img, cv::Point(130, 296), cv::Point(382, 296), cv::Scalar(255, 255, 255), 2);
    putText(img, "Hi Yasna!", cv::Point(207, 262), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0, 69, 255), 2);

    // imshow("Original Image", img);
    // cv::waitKey(0); 

    float card_width = 250;
    float card_height = 350;
    cv::Mat matrix , imgWarp;
    std::string cards_path = "../assets/cards.jpg";
    cv::Mat cards_img = cv::imread(cards_path);

    cv::Point2f src[4] = {{247, 188}, {397, 179}, {255, 356}, {411, 345}};
    cv::Point2f dst[4] = {{0.0f, 0.0f}, {card_width, 0.0f}, {0.0f, card_height}, {card_width, card_height}};

    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(cards_img, imgWarp, matrix,cv::Point(card_width, card_height));

    for (int i = 0; i < 4; i++)
    {
        circle (cards_img, src[i], 15, cv::Scalar(0, 69, 255), cv::FILLED);
    }
    // imshow("Original Image", cards_img);
    // imshow("Warp Image", imgWarp);
    // cv::waitKey(0); 

    cv::Mat imgHSV, mask;
    int hmin = 0;
    int smin = 110;
    int vmin = 153;
    int hmax = 19;
    int smax = 240;
    int vmax = 255;

    cvtColor(cards_img, imgHSV, cv::COLOR_BGR2HSV);

    cv::Scalar lower(hmin, smin, vmin);
    cv::Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, mask);

    // imshow("Original Image", cards_img);
    // imshow("HSV Image", imgHSV);
    // imshow("Mask Image", mask);
    // cv::waitKey(0); 

    /*
    cv::namedWindow("Trackbars", (740, 500));
    cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179); 
    cv::createTrackbar("Hue Max", "Trackbars", &hmin, 179); 
    cv::createTrackbar("Sat Min", "Trackbars", &hmin, 255); 
    cv::createTrackbar("Sat Max", "Trackbars", &hmin, 255); 
    cv::createTrackbar("Val Min", "Trackbars", &hmin, 255); 
    cv::createTrackbar("Val Max", "Trackbars", &hmin, 255); 
    */

    /*
    while (true)
    {
       cv::Scalar lower(hmin, smin, vmin);
       cv::Scalar upper(hmax, smax, vmax);
       inRange(imgHSV, lower, upper, mask);

       imshow("Original Image", cards_img);
       imshow("HSV Image", imgHSV);
       imshow("Mask Image", mask);
       cv::waitKey(1); 
    }
    */

    std::string shapes_path = "../assets/shapes.jpg";
    cv::Mat shapes_img = cv::imread(shapes_path);
    // imshow("Shapes Image", shapes_img);
    // cv::waitKey(0); 

    cv::Mat imgGray;
    cv::Mat imgBlur;
    cv::Mat imgCanny;
    cv::Mat imgDilate;
    cv::Mat imgErode;

    
    cvtColor(shapes_img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray, imgBlur, cv::Size(3,3), 5, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(1,1));
    dilate(imgCanny, imgDilate, kernel);
    /*
    imshow("Shapes  Image", imgDilate);
    cv::waitKey(0);   
    */
    /*
    getContours(imgDilate, shapes_img);
    imshow("Shapes  Image", shapes_img);
    cv::waitKey(0);  
    */

    return 0;
}