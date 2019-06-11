#include <iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
Scalar lowerBound(100 ,50,50);
Scalar upperBound(130,255,225);

int main()
{
	VideoCapture cam = VideoCapture(0);
	Mat frame;
	Mat imgHSV;
	Mat mask;		
	vector<vector<Point>> contours;

	Mat maskOpen;
	Mat maskClose;
	Mat kernelOpen(cv::Size(5, 5), CV_64FC1, Scalar(1));
	Mat kernelClose(cv::Size(20, 20), CV_64FC1, Scalar(1));

	while (1) {
		cam>>frame;
		resize(frame, frame, Size(340, 220));
		cvtColor(frame, imgHSV, COLOR_BGR2HSV);
		inRange(imgHSV, lowerBound, upperBound, mask);
		morphologyEx(mask, maskOpen, MORPH_OPEN, kernelOpen);
		morphologyEx(maskOpen, maskClose, MORPH_CLOSE, kernelClose);
		findContours(maskClose, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		drawContours(frame, contours, -1, Scalar(255, 0, 0), 3);
		for (int i = 0; i < size(contours); i++) {
			Rect rec = boundingRect(contours[i]);
			rectangle(frame, rec, Scalar(0, 0, 255));
		}

		if(size(contours)==2){
			Rect rec1 = boundingRect(contours[0]);
			Rect rec2 = boundingRect(contours[1]);

			rectangle(frame, rec1, (255, 0, 0), 2);
			rectangle(frame, rec2, (255, 0, 0), 2);

			double cx1 = (double)rec1.x + rec1.width / 2;
			double cy1 = (double)rec1.y + rec1.height / 2;
			double cx2 = (double)rec2.x + rec2.width / 2;
			double cy2 = (double)rec2.y + rec2.height / 2;

			double cx = (cx1 + cx2) / 2;
			double cy = (cy1 + cy2) / 2;

			line(frame,Point(cx1, cy1), Point(cx2, cy2), Scalar(255, 0, 0), 2);
			circle(frame, Point(cx, cy), 2, Scalar(0, 0, 255), 2);
		} 

		if (size(contours) == 1) {

		}

		imshow("maskOpen", maskOpen);
		imshow("maskClose", maskClose);
		imshow("mask", mask);
		imshow("frame", frame);	
		waitKey(10);
	}
	
}

