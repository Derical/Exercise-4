#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int kSize = 3;

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
	VideoCapture cap(0);
	Mat src, dst;
	while (1)
	{
		cap >> src;
		GaussianBlur(src,dst,Size(kSize*2+1,kSize*2+1),0,0);
		imshow("[原图]",src);
		imshow("[高斯滤波后]", dst);
		waitKey(30);
	}

	waitKey(0);
	return 0;
}