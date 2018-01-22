#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<vector>
#include</home/pi/wiringPi/wiringPi/wiringSerial.h>
#include</home/pi/wiringPi/wiringPi/wiringPi.h>
#include</home/pi/wiringPi/wiringPi/wiringSerial.c>
#include<string>
		


using namespace std;
using namespace cv;

int main() {
    	VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera.
      	vector<Vec3f> circles;
	//int triggerTime = 2;
    	while(true) {
		Mat frame;
		stream1.read(frame);

    		Mat hsv;
    		cvtColor(frame, hsv, COLOR_BGR2HSV);

    		Mat mask;
    		//inRange(hsv, Scalar(120,120,50), Scalar(180,255,150), mask);//bgr 53.96,221
		inRange(frame, Scalar(20,50,180), Scalar(100,140,255), mask);

     		Mat res;
      		bitwise_and(frame, frame, res, mask);

      		Mat blur;
      		GaussianBlur( res, blur, Size(9, 9), 2, 2 );

		Mat frame1;
		stream1.read(frame1);
      		
		Mat gray;
      		cvtColor(blur, gray, COLOR_BGR2GRAY);

		stream1.read(frame1);
      		
		HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows/10, 30, 15, 0, 0 );
 		for(size_t i = 0; i<circles.size(); i++) {
       			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        		int radius = cvRound(circles[i][2]);
			if(radius >=75){
				int fd = serialOpen("dev/ttyACM0", 9600);
				serialPuts(fd, "test string");
				
			}
        		circle( frame, center, 3, Scalar(255,0,0), -1, 8, 0 );
        		circle( frame, center, radius, Scalar(0,255,0), 3, 8, 0 );
      		}
		
		stream1.read(frame1);
      		
		stream1.read(frame1);
		stream1.read(frame1);
		//stream1.read(frame1);
		//stream1.read(frame1);
		imshow("Mask", mask);
     		//imshow("res", res);
      		//imshow("gray", gray);
      		//imshow("blur", blur);
      		imshow("frame", frame);	
		//stream1.read(frame1);
     		if(waitKey(1) >= 0)
		    	break;
    	}

    	return 0;
}
