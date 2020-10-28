#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int structElementSize = 2;

int main()
{
	// ------------------------- Exercise 1 -------------------------
	// 中值滤波
	VideoCapture cap(0);
	while (1)
	{
		Mat src,dst;
		cap >> src;
		medianBlur(src,dst,7);
		imshow("[原图]",src);
		imshow("[中值滤波后]", dst);
		waitKey(30);
	}



	waitKey(0);
	return 0;
}