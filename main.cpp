#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>
using namespace cv;
using namespace std;

#define _median		0
#define _blur	    1
#define _Guaussian	2

int kSize = 3;
int _Size = 1;
unsigned char mode = _median;

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

void Buffing()
{
	VideoCapture cap(0);

	double scale = 1;

	//0 - 180
	//肤色
	double i_minH = 0;
	double i_maxH = 20;
	//0 - 255
	double i_minS = 43;
	double i_maxS = 255;
	//0 - 255
	double i_minV = 55;
	double i_maxV = 255;

	//GUI
	char name[50];
	sprintf_s(name,"卷积核大小:%d", _Size * 2 + 1);
	namedWindow("[简易磨皮程序]", WINDOW_GUI_NORMAL);
	createTrackbar("滤波算法", "[简易磨皮程序]",(int *)&mode,_Guaussian);
	createTrackbar(name, "[简易磨皮程序]", &_Size, 25);

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;
		Mat buffer;
		Mat res;

		// ----- 图像处理部分 -----
		cap >> frame;
		//根据原图尺寸缩放
		Size ResImgSiz = Size(frame.cols * scale, frame.rows * scale); 

		Mat rFrame = Mat(ResImgSiz,frame.type());
		//将缩放后的图像存放在rFrame中
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);
		//RGB转HSV
		cvtColor(rFrame,hsvMat,COLOR_BGR2HSV);

		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV),detectMat);

		//滤波
		switch (mode)
		{

			case _median:
			{
				medianBlur(rFrame, buffer, _Size*2+1);
			}break;
			case _blur:
			{
				blur(rFrame,buffer,Size(_Size*2+1,_Size*2+1));
			}break;
			case _Guaussian:
			{
				GaussianBlur(rFrame,buffer,Size(_Size * 2 + 1,_Size * 2 + 1),0,0);
			}break;
			default:
				break;
		}

		//掩膜
		buffer.copyTo(res,detectMat);

		// ----- 显示部分 -----
		imshow("whie: in the range",detectMat);
		imshow("frame", rFrame); 
		imshow("[简易磨皮程序]", res);
	
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
	//Sobel_Detect();

	// ------------------------- Exercise 5 -------------------------
	// 磨皮程序
	Buffing();

	waitKey(0);
	return 0;
}