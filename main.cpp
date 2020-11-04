#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	// ------------------------- Exercise 1 -------------------------
	int threshold1 = 10;
	int threshold2 = 60;
	// Canny边缘检测
	Mat src = imread("C:\\Users\\STAR ZHANG\\Pictures\\cat.jpg");
	// 转换为灰度图
	Mat gray,dst;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	Canny(gray, dst, threshold1, threshold2);
	imshow("[原图]",src);
	imshow("[Canny边缘检测]",dst);
	waitKey(0);
	return 0;

}