#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
#include <stdio.h>

using namespace std;
using namespace cv;
 

struct position
{
    bool isFind;
    double x;
    double y;
    int id;
};

class RedBallFinder
{
    public:
        RedBallFinder();
        ~RedBallFinder();
        position findBall(Mat frame);
    private:
        position ballPosition;
};

int main( int argc, char** argv ){  

  position ballPos;
  RedBallFinder ball_finder = RedBallFinder();
  VideoCapture cap(0); //here video from webcam - 0 or "path to video with red balls"
  //cap.set(CAP_PROP_FRAME_WIDTH, 1280);
  //cap.set(CAP_PROP_FRAME_HEIGHT, 720);
   Mat frame;
  for ( ;; ){    
   
    cap >> frame; 
    if (frame.empty())
      break;
    ballPos = ball_finder.findBall(frame);
    namedWindow("RedBall");
    imshow("RedBall", frame); 
    
    if (ballPos.isFind) {
      cout << " x: " << ballPos.x << " y: " << ballPos.y << endl;
    }

    if(waitKey(1)==27)break;//quit on ESC button
  }

  cap.release();
  destroyAllWindows(); 
  return 0;
}

RedBallFinder::RedBallFinder()
{
    ballPosition.x = 0;
	ballPosition.y = 0;
    ballPosition.isFind = false;
}

RedBallFinder::~RedBallFinder(){

};

position RedBallFinder::findBall(Mat frame) {
    Mat blurred;
    Mat mask;
    Mat mask_eroded;
    Mat mask_dilated;
    Mat HSV;
    Mat erod; 
    Mat dill;

    ballPosition.isFind = false;
    
    GaussianBlur(frame,blurred,Size(11, 11),0);

    cvtColor(blurred, HSV, COLOR_BGR2HSV);
    inRange(HSV, Scalar(0,140,50), Scalar(15,255,255),mask); //0-15 - how red is the ball

    // imshow("mask", mask);
    // waitKey(0);

    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(10,10));    
    cv::erode(mask,mask_eroded,element,Point(-1, -1), 2);

    //imshow("Eroded", mask_eroded);
    //waitKey(0);      

    dilate(mask_eroded,mask_dilated,element,Point(-1, -1), 2);    

    // imshow("Dilated", mask_dilated);
    // waitKey(0);    
    
    vector<vector<Point>> contours;
    findContours(mask_dilated,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

    vector<vector<Point> > contours_poly( contours.size() );
    vector<Point2f>centers( contours.size() );
    vector<float>radius( contours.size() );
    
    int idx = -1, max_area=0;
    for( size_t i = 0; i < contours.size(); i++ ){
        approxPolyDP( contours[i], contours_poly[i], 3, true );
        minEnclosingCircle( contours_poly[i], centers[i], radius[i] );
        int area = (int)contourArea(contours_poly[i]);     
        if (area > max_area){
            idx = (int)i;
            max_area = area;
        }
    }

     //ball is detected
    if (idx>-1){        
        Point2f center = centers[idx];
        circle( frame, center, (int)radius[idx], Scalar(0,255,0), 1);
        circle( frame, center, 1, Scalar(150,150,0), -1);

        ballPosition.isFind = true;
        ballPosition.x = center.x;
        ballPosition.y = center.y;
    }
        // imshow("Ball", frame);
        // waitKey(0);
        // destroyAllWindows();  
    
    return ballPosition;
}


