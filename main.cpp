#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int kSize = 3;

void Sobel_Detect()
{
	VideoCapture cap(0);
	Mat src, xdst,ydst,gray;
	while (true)
	{
		cap >> src;
		cvtColor(src,gray,COLOR_BGR2GRAY);
		cv::Sobel(gray, xdst, CV_8UC1, 1, 0, 3);
		cv::Sobel(gray, ydst, CV_8UC1, 0, 1, 3);
		imshow("[x方向sobel边缘检测]", xdst);
		imshow("[y方向sobel边缘检测]", ydst);
		waitKey(30);
	}
}

int main()
{
	// ------------------------- Exercise 1 -------------------------
	// 中值滤波
	//VideoCapture cap(0);
	//while (1)
	//{
	//	Mat src,dst;
	//	cap >> src;
	//	medianBlur(src,dst,7);
	//	imshow("[原图]",src);
	//	imshow("[中值滤波后]", dst);
	//	waitKey(30);
	//}

	// ------------------------- Exercise 2 -------------------------
	//均值滤波
	//VideoCapture cap(0);
	//while (1)
	//{
	//	Mat src, dst;
	//	cap >> src;
	//	blur(src,dst,Size(kSize*2+1,kSize*2+1),Point(-1,-1));
	//	imshow("[原图]", src);
	//	imshow("[均值滤波后]",dst);
	//	waitKey(30);
	//}

	// ------------------------- Exercise 3 -------------------------
	// 高斯平滑卷积
	//VideoCapture cap(0);
	//Mat src, dst;
	//while (1)
	//{
	//	cap >> src;
	//	GaussianBlur(src,dst,Size(kSize*2+1,kSize*2+1),0,0);
	//	imshow("[原图]",src);
	//	imshow("[高斯滤波后]", dst);
	//	waitKey(30);
	//}

	// ------------------------- Exercise 4 -------------------------
	// Sobel边缘检测
	Sobel_Detect();

	waitKey(0);
	return 0;
}